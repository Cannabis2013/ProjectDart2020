#include "pointdartscontroller.h"

void PointDartsController ::start()
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

void PointDartsController::stop()
{
    setCurrentStatus(ControllerState::Stopped);
    emit controllerIsStopped();
}

void PointDartsController::handleAndProcessUserInput(const QByteArray& json)
{
    auto jsonObject = QJsonDocument::fromJson(json).object();
    auto point = jsonObject.value("Point").toInt();
    auto modKeyCode = jsonObject.value("ModKeyCode").toInt();
    // Check for status
    if(isBusy()) return;
    // Calculate score
    auto score = scoreCalculator()->calculateScoreFromDartsPoint(point,modKeyCode);
    auto setIndex = indexController()->setIndex();
    auto currentScore = scoreController()->userScore(setIndex);;
    auto accumulatedScore = scoreController()->calculateAccumulatedScoreCandidate(setIndex,score);
    // Evaluate input according to point domain and aggregated sum domain
    auto domain = scoreEvaluator()->validateInput(accumulatedScore,modKeyCode,point);
    /*
     * - Check domain value
     * - Add or nullify point
     */
    processDomain(domain,score,point,modKeyCode,currentScore,accumulatedScore);
}

void PointDartsController::handleRequestForCurrentTournamentMetaData()
{
    auto tournament = this->tournament();
    emit sendCurrentTournamentId(tournament);
}

void PointDartsController::assembleSingleAttemptDartsPoints()
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
    emit sendSingleAttemptDartsPoints(jsonString);
}

void PointDartsController::handleRequestDartsPoints()
{
    auto tournamentId = tournament();
    emit requestDartsPoints(tournamentId);
}

void PointDartsController::handleScoreAddedToDataContext(const QByteArray &json)
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
    emit pointAddedAndPersisted(newJson);
}

void PointDartsController::handleRequestPersistCurrentState()
{
    emit requestPersistModelState();
}

ScoreCalculatorInterface *PointDartsController::scoreCalculator() const
{
    return _scoreCalculatorService;
}

PointDartsController *PointDartsController::setScoreCalculator(ScoreCalculatorInterface *service)
{
    _scoreCalculatorService = service;
    return this;
}

void PointDartsController::handleResetTournament()
{
    _currentStatus = ControllerState::resetState;
    _indexController->reset();
    _scoreController->resetScores();
    auto tournamentId = tournament();
    emit requestResetTournament(tournamentId);
}

void PointDartsController::sendCurrentTurnValues()
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

QString PointDartsController::currentActiveUser()
{
    auto index = indexController()->setIndex();
    auto playerName = scoreController()->userNameAtIndex(index);
    return playerName;
}

QUuid PointDartsController::currentActivePlayerId()
{
    auto index = indexController()->setIndex();
    auto playerID = scoreController()->userIdAtIndex(index);
    return playerID;
}

QUuid PointDartsController::tournament()
{
    return _tournament;
}

int PointDartsController::status()
{
    return _currentStatus;
}

int PointDartsController::lastPlayerIndex()
{
    auto playerCount = scoreController()->playersCount();
    auto lastIndex = playerCount - 1;
    return lastIndex;
}


QUuid PointDartsController::undoTurn()
{
    if(status() == ControllerState::WinnerDeclared)
        return QUuid();
    _currentStatus = ControllerState::UndoState;
    indexController()->undo();
    auto roundIndex = indexController()->roundIndex();
    auto throwIndex = indexController()->attempt();
    emit hideDartsPoint(tournament(),
                             currentActivePlayerId(),
                             roundIndex,
                             throwIndex);
    auto playerId = currentActivePlayerId();
    return playerId;
}

QUuid PointDartsController::redoTurn()
{
    setCurrentStatus(ControllerState::RedoState);
    auto activeUser = currentActivePlayerId();
    auto roundIndex = indexController()->roundIndex();
    auto throwIndex = indexController()->attempt();
    indexController()->redo();
    emit revealDartsInputPoint(tournament(),
                               activeUser,
                               roundIndex,
                               throwIndex);
    auto index = indexController()->setIndex();
    auto playerId = scoreController()->userIdAtIndex(index);
    return playerId;
}

void PointDartsController::addPoint(const int& point,
                                  const int& score,
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
    obj["point"] = point;
    obj["scoreValue"] = score;
    obj["accumulatedScoreValue"] = accumulatedScore;
    obj["modKeyCode"] = keyCode;
    auto json = QJsonDocument(obj).toJson();
    emit requestAddDartsPoint (json);
}

void PointDartsController::handleRequestFromUI()
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

void PointDartsController::nextTurn()
{
    indexController()->next();
    setCurrentStatus(ControllerState::AwaitsInput);
    sendCurrentTurnValues();
}

void PointDartsController::declareWinner()
{
    auto index = indexController()->setIndex();
    auto currentPlayerId = scoreController()->userIdAtIndex(index);
    scoreController()->setWinner(currentPlayerId);
    setCurrentStatus(ControllerState::WinnerDeclared);
}

int PointDartsController::currentStatus() const
{
    return _currentStatus;
}

void PointDartsController::initializeController(const QByteArray& json)
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
        auto point = obj.value("point").toInt();
        auto modKeyCode = obj.value("modKeyCode").toInt();
        auto calculatedScore = scoreCalculator()->calculateScoreFromDartsPoint(point,modKeyCode);
        scoreController()->subtractPlayerScore(playerId,calculatedScore);
    }
    if(scoreController()->winnerId() != QUuid())
        setCurrentStatus(ControllerState::WinnerDeclared);
    else
        setCurrentStatus(ControllerState::Initialized);
    emit controllerIsInitialized();
}

bool PointDartsController::isBusy()
{
    if(status() == Stopped ||
            status() == WinnerDeclared)
    {
        emit controllerIsStopped();
        return true;
    }
    else if(status() == ControllerState::AddScoreState)
    {
        return true;
    }
    return false;
}

void PointDartsController::processDomain(const int& domain,
                                       const int& score,
                                       const int& point,
                                       const int& modKeyCode,
                                       const int& currentScore,
                                       const int& accumulatedScore)
{
    switch (domain)
    {
        // In case user enters scores above 180
        case OutOfRange : sendCurrentTurnValues();break;
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

ScoreController *PointDartsController::scoreController() const
{
    return _scoreController;
}

PointDartsController* PointDartsController::setScoreController(ScoreController* scoreController)
{
    _scoreController = scoreController;
    return this;
}


IndexControllerInterface *PointDartsController::indexController() const
{
    return _indexController;
}

PointDartsController* PointDartsController::setIndexController(IndexControllerInterface *indexController)
{
    _indexController = indexController;
    return this;
}

IPointValidator *PointDartsController::scoreEvaluator() const
{
    return _scoreEvaluator;
}

PointDartsController *PointDartsController::setInputValidator(IPointValidator *scoreEvaluator)
{
    _scoreEvaluator = scoreEvaluator;
    return this;
}

void PointDartsController::setCurrentStatus(int currentStatus)
{
    _currentStatus = currentStatus;
}

PointDartsController *PointDartsController::createInstance(const QUuid &tournament)
{
    return new PointDartsController(tournament);
}

FTPLogisticControllerInterface<QString> *PointDartsController::pointLogisticInterface() const
{
    return _pointLogisticInterface;
}

PointDartsController *PointDartsController::setLogisticInterface(FTPLogisticControllerInterface<QString> *pointLogisticInterface)
{
    _pointLogisticInterface = pointLogisticInterface;
    return this;
}

void PointDartsController::beginInitialize()
{
    auto tournamentId = tournament();
    emit requestDartsIndexesAndPoints(tournamentId);
}


void PointDartsController::undoSuccess(const QByteArray& json)
{
    auto jsonObject = QJsonDocument::fromJson(json).object();
    auto modKeyCode = jsonObject.value("modKeyCode").toInt();
    auto point = jsonObject.value("point").toInt();
    auto score = scoreCalculator()->calculateScoreFromDartsPoint(point,modKeyCode);
    auto playerId = jsonObject.value("playerId").toString();
    scoreController()->addPlayerScore(playerId,score);
    auto newScore = scoreController()->userScore(playerId);
    auto playerName = scoreController()->userNameFromId(playerId);
    QJsonObject responseJson = {
        {"playerName",playerName},
        {"playerPoint",point},
        {"playerScore",newScore}
    };
    auto data = QJsonDocument(responseJson).toJson(QJsonDocument::Compact);
    emit pointRemoved(data);
}

void PointDartsController::redoSuccess(const QByteArray& json)
{
    auto jsonObject = QJsonDocument::fromJson(json).object();
    auto keyCode = jsonObject.value("modKeyCode").toInt();
    auto point = jsonObject.value("point").toInt();
    auto playerId = jsonObject.value("playerId").toString();
    auto score = scoreCalculator()->calculateScoreFromDartsPoint(point,keyCode);
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
    emit pointAddedAndPersisted(data);
}
