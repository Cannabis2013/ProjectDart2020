#include "dartsscoremultiattempt.h"

void DartsScoreMultiAttempt::start()
{
    if(_currentStatus != ControllerState::Initialized &&
            _currentStatus != ControllerState::Stopped)
    {
        emit controllerIsNotInitialized();
        return;
    }
    setCurrentStatus(ControllerState::AwaitsInput);
    sendCurrentTurnValues();
}

void DartsScoreMultiAttempt::stop()
{
    setCurrentStatus(ControllerState::Stopped);
    emit controllerIsStopped();
}

void DartsScoreMultiAttempt::handleAndProcessUserInput(const QByteArray& json)
{
    auto jsonObject = QJsonDocument::fromJson(json).object();
    auto score = jsonObject.value("Score").toInt();
    // Check for status
    if(isBusy()) return;
    // Calculate score
    auto setIndex = indexController()->setIndex();
    auto currentScore = scoreController()->playerScore(setIndex);;
    auto accumulatedScore = scoreController()->calculateAccumulatedScoreCandidate(setIndex,score);
    // Evaluate input according to point domain and aggregated sum domain
    auto domain = scoreEvaluator()->validateInput(accumulatedScore);
    processDomain(domain,score,currentScore,accumulatedScore);
}

void DartsScoreMultiAttempt::handleRequestForCurrentTournamentMetaData()
{
    auto tournament = this->tournament();
    emit sendCurrentTournamentId(tournament);
}

void DartsScoreMultiAttempt::assembleSingleAttemptDartsScores()
{
    auto count = scoreController()->playersCount();
    QJsonObject jsonObject;
    QJsonArray playerScoreEntities;
    for (int i = 0; i < count; ++i) {
        QJsonObject obj;
        auto playerName = scoreController()->playerNameByIndex(i);
        auto score =scoreController()->playerScore(i);
        obj["playerName"] = playerName;
        obj["playerScore"] = score;
        playerScoreEntities.append(obj);
    };
    jsonObject["entities"] = playerScoreEntities;
    auto document = QJsonDocument(jsonObject);
    auto jsonString = document.toJson(QJsonDocument::Compact);
    emit sendSingleAttemptDartsScores(jsonString);
}

void DartsScoreMultiAttempt::handleRequestDartsScores()
{
    auto tournamentId = tournament();
    emit requestDartsScores(tournamentId);
}

void DartsScoreMultiAttempt::handleScoreAddedToDataContext(const QByteArray &json)
{
    auto obj = QJsonDocument::fromJson(json).object();
    auto score = obj.value("scoreValue").toInt();
    auto currentPlayerStringId = obj.value("playerId").toString();
    auto currentPlayerId = QUuid::fromString(currentPlayerStringId);
    // Subtract score value from current user score
    scoreController()->subtractPlayerScore(currentPlayerId,score);
    // Sync totalturns with the current turn index
    indexController()->syncIndex();
    auto newJson = QJsonDocument(obj).toJson(QJsonDocument::Compact);
    emit scoreAddedSuccess(newJson);
}

ScoreCalculatorInterface *DartsScoreMultiAttempt::scoreCalculator() const
{
    return _scoreCalculatorService;
}

DartsScoreMultiAttempt *DartsScoreMultiAttempt::setScoreCalculator(ScoreCalculatorInterface *service)
{
    _scoreCalculatorService = service;
    return this;
}

void DartsScoreMultiAttempt::handleResetTournament()
{
    _currentStatus = ControllerState::resetState;
    _indexController->reset();
    _scoreController->resetScores();
    auto tournamentId = tournament();
    emit requestResetTournament(tournamentId);
}

void DartsScoreMultiAttempt::sendCurrentTurnValues()
{
    auto canUndo = indexController()->canUndo();
    auto canRedo = indexController()->canRedo();
    auto roundIndex = indexController()->roundIndex();
    auto currentUserName = currentActiveUser();
    auto setIndex = indexController()->setIndex();
    auto score = scoreController()->playerScore(setIndex);;
    auto attemptIndex = indexController()->attempt() + 1;
    QString targetRow = "Logistic controller not injected!";
    if(_pointLogisticInterface != nullptr)
        targetRow = pointLogisticInterface()->suggestTargetRow(score,attemptIndex);
    QJsonObject jsonObject = {
        {"canUndo", canUndo},
        {"canRedo",canRedo},
        {"roundIndex",roundIndex},
        {"currentUserName",currentUserName},
        {"targetRow",targetRow}
    };
    auto data = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact);
    emit isReadyAndAwaitsInput(data);
}

QString DartsScoreMultiAttempt::currentActiveUser()
{
    auto index = indexController()->setIndex();
    auto playerName = scoreController()->playerNameByIndex(index);
    return playerName;
}

QUuid DartsScoreMultiAttempt::currentActivePlayerId()
{
    auto index = indexController()->setIndex();
    auto playerID = scoreController()->playerIdAtIndex(index);
    return playerID;
}

QUuid DartsScoreMultiAttempt::tournament()
{
    return _tournament;
}

int DartsScoreMultiAttempt::status()
{
    return _currentStatus;
}

int DartsScoreMultiAttempt::lastPlayerIndex()
{
    auto playerCount = scoreController()->playersCount();
    auto lastIndex = playerCount - 1;
    return lastIndex;
}


QUuid DartsScoreMultiAttempt::undoTurn()
{
    if(status() == ControllerState::WinnerDeclared)
        return QUuid();
    _currentStatus = ControllerState::UndoState;
    indexController()->undo();
    auto roundIndex = indexController()->roundIndex();
    emit hideDartsScore(tournament(),
                        currentActivePlayerId(),
                        roundIndex);
    auto playerId = currentActivePlayerId();
    return playerId;
}

QUuid DartsScoreMultiAttempt::redoTurn()
{
    setCurrentStatus(ControllerState::RedoState);
    auto activeUser = currentActivePlayerId();
    auto roundIndex = indexController()->roundIndex();
    indexController()->redo();
    emit revealDartsScore(tournament(),
                             activeUser,
                             roundIndex);
    auto index = indexController()->setIndex();
    auto playerId = scoreController()->playerIdAtIndex(index);
    return playerId;
}

void DartsScoreMultiAttempt::addPoint(const int& score,
                                  const int& accumulatedScore)
{
    // Set controller state, unless winner declared
    if(currentStatus() != ControllerState::WinnerDeclared)
        setCurrentStatus(ControllerState::AddScoreState);
    auto currentPlayerId = currentActivePlayerId().toString(QUuid::WithoutBraces);
    QJsonObject obj;
    obj["tournamentId"] = tournament().toString(QUuid::WithoutBraces);
    obj["roundIndex"] = indexController()->roundIndex();
    obj["setIndex"] = indexController()->setIndex();
    obj["attempt"] = indexController()->attempt();
    obj["winnerId"] = status() == ControllerState::WinnerDeclared ? currentPlayerId : "";
    obj["playerId"] = currentPlayerId;
    obj["scoreValue"] = score;
    obj["accumulatedScoreValue"] = accumulatedScore;
    auto json = QJsonDocument(obj).toJson();
    emit requestAddDartsScore(json);
}

void DartsScoreMultiAttempt::handleRequestFromUI()
{
    if(status() == ControllerState::Initialized)
    {
        emit dartsSingleScoreControllerIsInitialized();
    }
    else if(status() == ControllerState::AddScoreState)
    {
        /*
         * - Increment indexes
         * - Notify datacontext to create models if necessary
         * - Datacontext responds with a signal which is handled in 'handleReplyFromDataContext' slot
         * - Otherwise, it just emits a signal with current round values
         */
        nextTurn();
    }
    else if(status() == ControllerState::UndoState)
    {
        setCurrentStatus(ControllerState::AwaitsInput);
        sendCurrentTurnValues();
    }
    else if(status() == ControllerState::RedoState)
    {
        setCurrentStatus(ControllerState::AwaitsInput);
        sendCurrentTurnValues();
    }
    else if(status() == ControllerState::WinnerDeclared)
    {
        auto winnerName = scoreController()->winnerUserName();
        QJsonObject jsonObject = {{"winner",winnerName}};
        auto json = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact);
        emit winnerDeclared(json);
    }
    else if(status() == ControllerState::resetState)
    {
        setCurrentStatus(ControllerState::Initialized);
        emit dartsSingleScoreControllerIsInitialized();
    }
}

void DartsScoreMultiAttempt::nextTurn()
{
    indexController()->next();
    setCurrentStatus(ControllerState::AwaitsInput);
    sendCurrentTurnValues();
}

void DartsScoreMultiAttempt::declareWinner()
{
    auto index = indexController()->setIndex();
    auto currentPlayerId = scoreController()->playerIdAtIndex(index);
    scoreController()->setWinner(currentPlayerId);
    setCurrentStatus(ControllerState::WinnerDeclared);
}

int DartsScoreMultiAttempt::currentStatus() const
{
    return _currentStatus;
}

void DartsScoreMultiAttempt::initializeControllerIndexes(const QByteArray& json)
{
    auto jsonObject = QJsonDocument::fromJson(json).object();
    auto jsonIndexObject = jsonObject["indexes"].toObject();
    auto totalTurns = jsonIndexObject["totalTurns"].toInt();
    auto turns = jsonIndexObject["turns"].toInt();
    auto roundIndex = jsonIndexObject["roundIndex"].toInt();
    auto setIndex = jsonIndexObject["setIndex"].toInt();
    auto attemptIndex = jsonIndexObject["attemptIndex"].toInt();
    indexController()->setIndexes(totalTurns,turns,
                                  roundIndex,setIndex,
                                  attemptIndex);
    auto tournamentWinnerStringId = jsonObject.value("tournamentWinnerId").toString();
    auto tournamentWinnerId = tournamentWinnerStringId != "" ?
                QUuid::fromString(tournamentWinnerStringId) : QUuid();
    scoreController()->setWinner(tournamentWinnerId);
    auto playerData = jsonObject.value("playerEntities").toArray();
    indexController()->setPlayersCount(playerData.count());
    for (const auto &jsonVal : playerData) {
        auto obj = jsonVal.toObject();
        auto playerStringId = obj["playerId"].toString();
        auto playerId = QUuid::fromString(playerStringId);
        auto playerName = obj["playerName"].toString();
        scoreController()->addPlayerEntity(playerId,playerName);
    }
    auto scoreData = jsonObject.value("scoreEntities").toArray();
    for (const auto &jsonVal : scoreData) {
        auto obj = jsonVal.toObject();
        auto playerStringId = obj.value("playerId").toString();
        auto playerId = QUuid::fromString(playerStringId);
        auto score = obj.value("score").toInt();
        scoreController()->subtractPlayerScore(playerId,score);
    }
    if(scoreController()->winnerId() != QUuid())
        setCurrentStatus(ControllerState::WinnerDeclared);
    else
        setCurrentStatus(ControllerState::Initialized);
    emit dartsSingleScoreControllerIsInitialized();
}

bool DartsScoreMultiAttempt::isBusy()
{
    if(status() == Stopped ||
            status() == WinnerDeclared)
    {
        emit controllerIsStopped();
        return true;
    }
    if(status() == ControllerState::AddScoreState)
    {
        return true;
    }
    return false;
}

void DartsScoreMultiAttempt::processDomain(const int &domain,
                                         const int &score,
                                         const int &currentScore,
                                         const int &accumulatedScore)
{
    switch (domain)
    {
        // In case user enters scores above 180
    case InputOutOfRange : sendCurrentTurnValues();break;
        case PointDomain : addPoint(score,accumulatedScore);break;
        case CriticalDomain : addPoint(score,accumulatedScore);break;
        case TargetDomain : {
            declareWinner();
            addPoint(score,accumulatedScore);
            break;
        }
        case OutsideDomain : addPoint(0,currentScore);break;
    }
}

IPlayerScoreService *DartsScoreMultiAttempt::scoreController() const
{
    return _scoreController;
}

DartsScoreMultiAttempt* DartsScoreMultiAttempt::setScoreController(IPlayerScoreService *scoreController)
{
    _scoreController = scoreController;
    return this;
}


IndexControllerInterface *DartsScoreMultiAttempt::indexController() const
{
    return _indexController;
}

DartsScoreMultiAttempt* DartsScoreMultiAttempt::setIndexController(IndexControllerInterface *indexController)
{
    _indexController = indexController;
    return this;
}

IScoreValidator *DartsScoreMultiAttempt::scoreEvaluator() const
{
    return _scoreEvaluator;
}

DartsScoreMultiAttempt *DartsScoreMultiAttempt::setInputValidator(IScoreValidator *scoreEvaluator)
{
    _scoreEvaluator = scoreEvaluator;
    return this;
}

void DartsScoreMultiAttempt::setCurrentStatus(int currentStatus)
{
    _currentStatus = currentStatus;
}

DartsScoreMultiAttempt *DartsScoreMultiAttempt::createInstance(const QUuid &tournament)
{
    return new DartsScoreMultiAttempt(tournament);
}

FTPLogisticControllerInterface<QString> *DartsScoreMultiAttempt::pointLogisticInterface() const
{
    return _pointLogisticInterface;
}

DartsScoreMultiAttempt *DartsScoreMultiAttempt::setLogisticInterface(FTPLogisticControllerInterface<QString> *pointLogisticInterface)
{
    _pointLogisticInterface = pointLogisticInterface;
    return this;
}

void DartsScoreMultiAttempt::beginInitialize()
{
    auto tournamentId = tournament();
    emit requestDartsTournamentIndexes(tournamentId);
}


void DartsScoreMultiAttempt::undoSuccess(const QByteArray& json)
{
    auto jsonObject = QJsonDocument::fromJson(json).object();
    auto score = jsonObject.value("scoreValue").toInt();
    auto playerId = jsonObject.value("playerId").toString();
    scoreController()->addPlayerScore(playerId,score);
    auto newScore = scoreController()->playerScore(playerId);
    auto playerName = scoreController()->playerNameById(playerId);
    QJsonObject responseJson = {
        {"playerName",playerName},
        {"playerScore",newScore}
    };
    auto data = QJsonDocument(responseJson).toJson(QJsonDocument::Compact);
    emit scoreRemoved(data);
}

void DartsScoreMultiAttempt::redoSuccess(const QByteArray& json)
{
    auto jsonObject = QJsonDocument::fromJson(json).object();
    auto score = jsonObject.value("scoreValue").toInt();
    auto playerId = jsonObject.value("playerId").toString();
    scoreController()->subtractPlayerScore(playerId,score);
    auto newScore = scoreController()->playerScore(playerId);
    auto playerName = scoreController()->playerNameById(playerId);
    QJsonObject obj = {
        {"playerName",playerName},
        {"playerScore",newScore}
    };
    auto data = QJsonDocument(obj).toJson(QJsonDocument::Compact);
    emit scoreAddedSuccess(data);
}

void DartsScoreMultiAttempt::initializeControllerPlayerDetails(const QByteArray &)
{
}

void DartsScoreMultiAttempt::initializeControllerDartsScores(const QByteArray &)
{
}

void DartsScoreMultiAttempt::initializeControllerWinnerIdAndName(const QByteArray &)
{
}
