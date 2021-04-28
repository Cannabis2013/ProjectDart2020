#include "scoredartscontroller.h"

void ScoreDartsController::start()
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

void ScoreDartsController::stop()
{
    setCurrentStatus(ControllerState::Stopped);
    emit controllerIsStopped();
}

void ScoreDartsController::handleAndProcessUserInput(const QByteArray& json)
{
    auto jsonObject = QJsonDocument::fromJson(json).object();
    auto score = jsonObject.value("Score").toInt();
    // Check for status
    if(isBusy()) return;
    // Calculate score
    auto setIndex = indexController()->setIndex();
    auto currentScore = scoreController()->userScore(setIndex);;
    auto accumulatedScore = scoreController()->calculateAccumulatedScoreCandidate(setIndex,score);
    // Evaluate input according to point domain and aggregated sum domain
    auto domain = scoreEvaluator()->validateInput(accumulatedScore);
    processDomain(domain,score,point,modKeyCode,currentScore,accumulatedScore);
}

void ScoreDartsController::handleRequestForCurrentTournamentMetaData()
{
    auto tournament = this->tournament();
    emit sendCurrentTournamentId(tournament);
}

void ScoreDartsController::assembleSingleAttemptFtpScores()
{
    auto count = scoreController()->playersCount();
    QJsonObject jsonObject;
    QJsonArray playerScoreEntities;
    for (int i = 0; i < count; ++i) {
        QJsonObject obj;
        auto playerName = scoreController()->userNameAtIndex(i);
        auto score =scoreController()->userScore(i);
        obj["playerName"] = playerName;
        obj["playerScore"] = score;
        playerScoreEntities.append(obj);
    };
    jsonObject["entities"] = playerScoreEntities;
    auto document = QJsonDocument(jsonObject);
    auto jsonString = document.toJson(QJsonDocument::Compact);
    emit sendSingleAttemptFtpScores(jsonString);
}

void ScoreDartsController::handleRequestFtpPlayerScores()
{
    auto tournamentId = tournament();
    emit requestFtpMultiAttemptScores(tournamentId);
}

void ScoreDartsController::handleScoreAddedToDataContext(const QByteArray &json)
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
    emit scoreAddedAndPersisted(newJson);
}

void ScoreDartsController::handleScoreHintUpdated(const QByteArray &json)
{
    auto jsonObject = QJsonDocument::fromJson(json).object();
    auto score = jsonObject.value("scoreValue").toInt();
    auto point = jsonObject.value("point").toInt();
    auto playerId = jsonObject.value("playerId").toString();
    auto keyCode = jsonObject.value("modKeyCode").toInt();
    if(this->status() == ControllerState::UndoState)
    {
        scoreController()->addPlayerScore(playerId,score);
        auto newScore = scoreController()->userScore(playerId);
        auto playerName = scoreController()->userNameFromId(playerId);
        QJsonObject json = {
            {"playerName",playerName},
            {"playerPoint",point},
            {"playerScore",newScore}
        };
        auto data = QJsonDocument(json).toJson(QJsonDocument::Compact);
        emit scoreRemoved(data);
    }
    else if(this->status() == ControllerState::RedoState)
    {
        scoreController()->subtractPlayerScore(playerId,score);
        auto newScore = scoreController()->userScore(playerId);
        auto playerName = scoreController()->userNameFromId(playerId);
        QJsonObject obj = {
            {"playerName",playerName},
            {"playerPoint",point},
            {"playerScore",newScore},
            {"keyCode",keyCode}
        };
        auto data = QJsonDocument(obj).toJson(QJsonDocument::Compact);
        emit scoreAddedAndPersisted(data);
    }
}

void ScoreDartsController::handleRequestPersistCurrentState()
{
    emit requestPersistModelState();
}

ScoreCalculatorInterface *ScoreDartsController::scoreCalculator() const
{
    return _scoreCalculatorService;
}

ScoreDartsController *ScoreDartsController::setScoreCalculator(ScoreCalculatorInterface *service)
{
    _scoreCalculatorService = service;
    return this;
}

void ScoreDartsController::handleResetTournament()
{
    _currentStatus = ControllerState::resetState;
    _indexController->reset();
    _scoreController->resetScores();
    auto tournamentId = tournament();
    emit requestResetTournament(tournamentId);
}

void ScoreDartsController::sendCurrentTurnValues()
{
    auto canUndo = indexController()->canUndo();
    auto canRedo = indexController()->canRedo();
    auto roundIndex = indexController()->roundIndex();
    auto currentUserName = currentActiveUser();
    auto setIndex = indexController()->setIndex();
    auto score = scoreController()->userScore(setIndex);;
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

QString ScoreDartsController::currentActiveUser()
{
    auto index = indexController()->setIndex();
    auto playerName = scoreController()->userNameAtIndex(index);
    return playerName;
}

QUuid ScoreDartsController::currentActivePlayerId()
{
    auto index = indexController()->setIndex();
    auto playerID = scoreController()->userIdAtIndex(index);
    return playerID;
}

QUuid ScoreDartsController::tournament()
{
    return _tournament;
}

int ScoreDartsController::status()
{
    return _currentStatus;
}

int ScoreDartsController::lastPlayerIndex()
{
    auto playerCount = scoreController()->playersCount();
    auto lastIndex = playerCount - 1;
    return lastIndex;
}


QUuid ScoreDartsController::undoTurn()
{
    if(status() == ControllerState::WinnerDeclared)
        return QUuid();
    _currentStatus = ControllerState::UndoState;
    indexController()->undo();
    auto roundIndex = indexController()->roundIndex();
    auto throwIndex = indexController()->attempt();
    emit requestSetModelHint(tournament(),
                             currentActivePlayerId(),
                             roundIndex,
                             throwIndex,
                             ModelDisplayHint::HiddenHint);
    auto playerId = currentActivePlayerId();
    return playerId;
}

QUuid ScoreDartsController::redoTurn()
{
    setCurrentStatus(ControllerState::RedoState);
    auto activeUser = currentActivePlayerId();
    auto roundIndex = indexController()->roundIndex();
    auto throwIndex = indexController()->attempt();
    indexController()->redo();
    emit requestSetModelHint(tournament(),
                             activeUser,
                             roundIndex,
                             throwIndex,
                             ModelDisplayHint::DisplayHint);
    auto index = indexController()->setIndex();
    auto playerId = scoreController()->userIdAtIndex(index);
    return playerId;
}

void ScoreDartsController::addPoint(const int& score,
                                  const int& accumulatedScore,
                                  const int& keyCode)
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
    obj["modKeyCode"] = keyCode;
    auto json = QJsonDocument(obj).toJson();
    emit requestAddDartsScore (json);
}

void ScoreDartsController::handleRequestFromUI()
{
    if(status() == ControllerState::Initialized)
    {
        emit controllerIsInitialized();
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
        emit controllerIsInitialized();
    }
}

void ScoreDartsController::nextTurn()
{
    indexController()->next();
    setCurrentStatus(ControllerState::AwaitsInput);
    sendCurrentTurnValues();
}

void ScoreDartsController::declareWinner()
{
    auto index = indexController()->setIndex();
    auto currentPlayerId = scoreController()->userIdAtIndex(index);
    scoreController()->setWinner(currentPlayerId);
    setCurrentStatus(ControllerState::WinnerDeclared);
}

int ScoreDartsController::currentStatus() const
{
    return _currentStatus;
}

void ScoreDartsController::initializeController(const QByteArray& json)
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
    emit controllerIsInitialized();
}

bool ScoreDartsController::isBusy()
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

void ScoreDartsController::processDomain(const int &domain, const int &score, const int &modKeyCode, const int &currentScore, const int &accumulatedScore)
{
    switch (domain)
    {
        // In case user enters scores above 180
    case InputOutOfRange : sendCurrentTurnValues();break;
        case PointDomain : addPoint(point,score,accumulatedScore,modKeyCode);break;
        case CriticalDomain : addPoint(point,score,accumulatedScore,modKeyCode);break;
        case TargetDomain : {
            declareWinner();
            addPoint(point,score,accumulatedScore,modKeyCode);
            break;
        }
        case OutsideDomain : addPoint(0,0,currentScore,modKeyCode);break;
    }
}

ScoreController *ScoreDartsController::scoreController() const
{
    return _scoreController;
}

ScoreDartsController* ScoreDartsController::setScoreController(ScoreController* scoreController)
{
    _scoreController = scoreController;
    return this;
}


IndexControllerInterface *ScoreDartsController::indexController() const
{
    return _indexController;
}

ScoreDartsController* ScoreDartsController::setIndexController(IndexControllerInterface *indexController)
{
    _indexController = indexController;
    return this;
}

IScoreValidator *ScoreDartsController::scoreEvaluator() const
{
    return _scoreEvaluator;
}

ScoreDartsController *ScoreDartsController::setInputValidator(IScoreValidator *scoreEvaluator)
{
    _scoreEvaluator = scoreEvaluator;
    return this;
}

void ScoreDartsController::setCurrentStatus(int currentStatus)
{
    _currentStatus = currentStatus;
}

ScoreDartsController *ScoreDartsController::createInstance(const QUuid &tournament)
{
    return new ScoreDartsController(tournament);
}

FTPLogisticControllerInterface<QString> *ScoreDartsController::pointLogisticInterface() const
{
    return _pointLogisticInterface;
}

ScoreDartsController *ScoreDartsController::setLogisticInterface(FTPLogisticControllerInterface<QString> *pointLogisticInterface)
{
    _pointLogisticInterface = pointLogisticInterface;
    return this;
}

void ScoreDartsController::beginInitialize()
{
    auto tournamentId = tournament();
    emit requestFtpIndexesAndScores(tournamentId);
}
