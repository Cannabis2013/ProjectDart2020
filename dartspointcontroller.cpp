#include "dartspointcontroller.h"

void DartsPointController ::start()
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

void DartsPointController::stop()
{
    setCurrentStatus(ControllerState::Stopped);
    emit controllerIsStopped();
}

void DartsPointController::handleAndProcessUserInput(const QByteArray& json)
{
    auto jsonObject = QJsonDocument::fromJson(json).object();
    auto point = jsonObject.value("point").toInt();
    auto modKeyCode = jsonObject.value("modKeyCode").toInt();
    // Check for status
    if(isBusy()) return;
    // Calculate score
    auto score = scoreCalculator()->calculateScoreFromDartsPoint(point,modKeyCode);
    auto setIndex = indexController()->setIndex();
    auto accumulatedScore = scoreController()->calculateAccumulatedScoreCandidate(setIndex,score);
    // Evaluate input according to point domain and aggregated sum domain
    auto domain = scoreEvaluator()->validateInput(accumulatedScore,modKeyCode,point);
    /*
     * - Check domain value
     * - Add or nullify point
     */
    processDomain(domain,score,point,modKeyCode);
}

void DartsPointController::handleRequestForCurrentTournamentMetaData()
{
    auto tournament = this->tournament();
    emit sendCurrentTournamentId(tournament);
}

void DartsPointController::assembleSingleAttemptDartsPoints()
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

void DartsPointController::handleRequestDartsPoints()
{
    auto tournamentId = tournament();
    emit requestDartsPoints(tournamentId);
}

void DartsPointController::handlePointAddedToDataContext(const QByteArray &json)
{
    auto jsonObject = QJsonDocument::fromJson(json).object();
    auto score = jsonObject.value("scoreValue").toInt();
    auto currentPlayerStringId = jsonObject.value("playerId").toString();
    auto currentPlayerId = QUuid::fromString(currentPlayerStringId);
    // Subtract score value from current user score
    scoreController()->subtractPlayerScore(currentPlayerId,score);
    // Sync totalturns with the current turn index
    indexController()->syncIndex();
    jsonObject["scoreValue"] = scoreController()->userScore(currentPlayerId);
    auto newJson = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact);
    emit pointAddedAndPersisted(newJson);
}

ScoreCalculatorInterface *DartsPointController::scoreCalculator() const
{
    return _scoreCalculatorService;
}

DartsPointController *DartsPointController::setScoreCalculator(ScoreCalculatorInterface *service)
{
    _scoreCalculatorService = service;
    return this;
}

void DartsPointController::handleResetTournament()
{
    _currentStatus = ControllerState::resetState;
    _indexController->reset();
    _scoreController->resetScores();
    auto tournamentId = tournament();
    emit requestResetTournament(tournamentId);
}

void DartsPointController::sendCurrentTurnValues()
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

QString DartsPointController::currentActiveUser()
{
    auto index = indexController()->setIndex();
    auto playerName = scoreController()->userNameAtIndex(index);
    return playerName;
}

QUuid DartsPointController::currentActivePlayerId()
{
    auto index = indexController()->setIndex();
    auto playerID = scoreController()->userIdAtIndex(index);
    return playerID;
}

QUuid DartsPointController::tournament()
{
    return _tournament;
}

int DartsPointController::status()
{
    return _currentStatus;
}

int DartsPointController::lastPlayerIndex()
{
    auto playerCount = scoreController()->playersCount();
    auto lastIndex = playerCount - 1;
    return lastIndex;
}


QUuid DartsPointController::undoTurn()
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

QUuid DartsPointController::redoTurn()
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

void DartsPointController::addPoint(const int& point,
                                  const int& score,
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
    obj["modKeyCode"] = keyCode;
    auto json = QJsonDocument(obj).toJson();
    emit requestAddDartsPoint (json);
}

void DartsPointController::handleRequestFromUI()
{
    if(status() == ControllerState::Initialized)
    {
        emit controllerIsInitializedAndReady();
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

void DartsPointController::nextTurn()
{
    indexController()->next();
    setCurrentStatus(ControllerState::AwaitsInput);
    sendCurrentTurnValues();
}

void DartsPointController::declareWinner()
{
    auto index = indexController()->setIndex();
    auto currentPlayerId = scoreController()->userIdAtIndex(index);
    scoreController()->setWinner(currentPlayerId);
    setCurrentStatus(ControllerState::WinnerDeclared);
}

int DartsPointController::currentStatus() const
{
    return _currentStatus;
}

void DartsPointController::initializeControllerIndexes(const QByteArray& json)
{
    auto jsonObject = QJsonDocument::fromJson(json).object();
    auto totalTurns = jsonObject.value("totalTurns").toInt();
    auto turns = jsonObject.value("turns").toInt();
    auto roundIndex = jsonObject.value("roundIndex").toInt();
    auto setIndex = jsonObject.value("setIndex").toInt();
    auto attemptIndex = jsonObject.value("attemptIndex").toInt();
    indexController()->setIndexes(totalTurns,turns,
                                  roundIndex,setIndex,
                                  attemptIndex);
    emit requestTournamentAssignedPlayerDetails(tournament());
}

bool DartsPointController::isBusy()
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

void DartsPointController::processDomain(const int& domain,
                                       const int& score,
                                       const int& point,
                                       const int& modKeyCode)
{
    switch (domain)
    {
        // In case user enters scores above 180
        case OutOfRange : sendCurrentTurnValues();break;
        case PointDomain : addPoint(point,score,modKeyCode);break;
        case CriticalDomain : addPoint(point,score,modKeyCode);break;
        case TargetDomain : {
            declareWinner();
            addPoint(point,score,modKeyCode);
            break;
        }
        case OutsideDomain : addPoint(0,0,modKeyCode);break;
    }
}

ScoreController *DartsPointController::scoreController() const
{
    return _scoreController;
}

DartsPointController* DartsPointController::setScoreController(ScoreController* scoreController)
{
    _scoreController = scoreController;
    return this;
}


IndexControllerInterface *DartsPointController::indexController() const
{
    return _indexController;
}

DartsPointController* DartsPointController::setIndexController(IndexControllerInterface *indexController)
{
    _indexController = indexController;
    return this;
}

IPointValidator *DartsPointController::scoreEvaluator() const
{
    return _scoreEvaluator;
}

DartsPointController *DartsPointController::setInputValidator(IPointValidator *scoreEvaluator)
{
    _scoreEvaluator = scoreEvaluator;
    return this;
}

void DartsPointController::setCurrentStatus(int currentStatus)
{
    _currentStatus = currentStatus;
}

DartsPointController *DartsPointController::createInstance(const QUuid &tournament)
{
    return new DartsPointController(tournament);
}

FTPLogisticControllerInterface<QString> *DartsPointController::pointLogisticInterface() const
{
    return _pointLogisticInterface;
}

DartsPointController *DartsPointController::setLogisticInterface(FTPLogisticControllerInterface<QString> *pointLogisticInterface)
{
    _pointLogisticInterface = pointLogisticInterface;
    return this;
}

void DartsPointController::beginInitialize()
{
    auto tournamentId = tournament();
    emit requestDartsTournamentIndexes(tournamentId);
}


void DartsPointController::undoSuccess(const QByteArray& json)
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

void DartsPointController::redoSuccess(const QByteArray& json)
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


void DartsPointController::initializeControllerPlayerDetails(const QByteArray& json)
{
    auto document = QJsonDocument::fromJson(json);
    auto playerData = document.array();
    indexController()->setPlayersCount(playerData.count());
    for (const auto &jsonVal : playerData) {
        auto obj = jsonVal.toObject();
        auto playerStringId = obj["playerId"].toString();
        auto playerId = QUuid::fromString(playerStringId);
        auto playerName = obj["playerName"].toString();
        scoreController()->addPlayerEntity(playerId,playerName);
    }
    emit requestTournamentDartsPoints(tournament());
}

void DartsPointController::initializeControllerDartsPoints(const QByteArray& json)
{
    auto document = QJsonDocument::fromJson(json);
    auto scoreData = document.array();
    for (const auto &jsonVal : scoreData) {
        auto obj = jsonVal.toObject();
        auto playerStringId = obj.value("playerId").toString();
        auto playerId = QUuid::fromString(playerStringId);
        auto point = obj.value("point").toInt();
        auto modKeyCode = obj.value("modKeyCode").toInt();
        auto calculatedScore = scoreCalculator()->calculateScoreFromDartsPoint(point,modKeyCode);
        scoreController()->subtractPlayerScore(playerId,calculatedScore);
    }
    emit requestTournamentWinnerIdAndName(tournament());
}

void DartsPointController::initializeControllerWinnerIdAndName(const QByteArray& json)
{
    auto document = QJsonDocument::fromJson(json);
    auto jsonObject = document.object();
    auto tournamentWinnerStringId = jsonObject.value("playerId").toString();
    auto tournamentWinnerId = QUuid::fromString(tournamentWinnerStringId);
    scoreController()->setWinner(tournamentWinnerId);
    if(scoreController()->winnerId() != QUuid())
        setCurrentStatus(ControllerState::WinnerDeclared);
    else
        setCurrentStatus(ControllerState::Initialized);
    emit controllerIsInitialized();
}
