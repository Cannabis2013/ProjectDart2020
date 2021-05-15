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
    auto score = jsonObject.value("score").toInt();
    // Check for status
    if(isBusy()) return;
    // Calculate score
    auto setIndex = _indexController->setIndex();
    auto accumulatedScore = _scoreController->calculateAccumulatedScoreCandidate(setIndex,score);
    // Evaluate input according to point domain and aggregated sum domain
    auto domain = _scoreEvaluator->validateInput(accumulatedScore);
    processDomain(domain,score);
}

void DartsScoreMultiAttempt::handleRequestForCurrentTournamentMetaData()
{
    auto tournament = this->tournament();
    emit sendCurrentTournamentId(tournament);
}

void DartsScoreMultiAttempt::assembleSingleAttemptDartsScores()
{
    auto json = _jsonService->assembleJsonDartsMultiAttemptScores(_scoreController);
    emit sendMultiAttemptDartsScores(json);
}

void DartsScoreMultiAttempt::handleRequestDartsScores()
{
    auto tournamentId = tournament();
    emit requestDartsScores(tournamentId);
}

void DartsScoreMultiAttempt::handleScoreAddedToDataContext(const QByteArray &json)
{

    auto obj = QJsonDocument::fromJson(json).object();
    auto score = obj.value("score").toInt();
    auto currentPlayerStringId = obj.value("playerId").toString();
    auto currentPlayerId = QUuid::fromString(currentPlayerStringId);
    // Subtract score value from current user score
    auto totalScore = _scoreController->subtractPlayerScore(currentPlayerId,score);
    auto playerName = _scoreController->playerNameById(currentPlayerId);
    // Sync totalturns with the current turn index
    _indexController->syncIndex();
    auto newJson = _jsonService->assembleJsonFromParameters(playerName,totalScore);;
    emit scoreAddedSuccess(newJson);
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
    auto canUndo = _indexController->canUndo();
    auto canRedo = _indexController->canRedo();
    auto roundIndex = _indexController->roundIndex();
    auto currentUserName = currentActiveUser();
    auto setIndex = _indexController->setIndex();
    auto score = _scoreController->playerScore(setIndex);
    QString targetRow = "Logistic controller not injected!";
    if(_pointLogisticInterface != nullptr)
        targetRow = pointLogisticInterface()->suggestTargetRow(score,1);
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
    auto index = _indexController->setIndex();
    auto playerName = _scoreController->playerNameByIndex(index);
    return playerName;
}

QUuid DartsScoreMultiAttempt::currentActivePlayerId()
{
    auto index = _indexController->setIndex();
    auto playerID = _scoreController->playerIdAtIndex(index);
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
    auto playerCount = _scoreController->playersCount();
    auto lastIndex = playerCount - 1;
    return lastIndex;
}


QUuid DartsScoreMultiAttempt::undoTurn()
{
    if(status() == ControllerState::WinnerDeclared)
        return QUuid();
    _currentStatus = ControllerState::UndoState;
    _indexController->undo();
    auto roundIndex = _indexController->roundIndex();
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
    auto roundIndex = _indexController->roundIndex();
    _indexController->redo();
    emit revealDartsScore(tournament(),
                             activeUser,
                             roundIndex);
    auto index = _indexController->setIndex();
    auto playerId = _scoreController->playerIdAtIndex(index);
    return playerId;
}

void DartsScoreMultiAttempt::addPoint(const int& score)
{
    // Set controller state, unless winner declared
    if(currentStatus() != ControllerState::WinnerDeclared)
        setCurrentStatus(ControllerState::AddScoreState);
    auto currentPlayerId = currentActivePlayerId().toString(QUuid::WithoutBraces);
    QJsonObject obj;
    obj["tournamentId"] = tournament().toString(QUuid::WithoutBraces);
    obj["roundIndex"] = _indexController->roundIndex();
    obj["setIndex"] = _indexController->setIndex();
    obj["winnerId"] = status() == ControllerState::WinnerDeclared ? currentPlayerId : "";
    obj["playerId"] = currentPlayerId;
    obj["score"] = score;
    auto json = QJsonDocument(obj).toJson();
    emit requestAddDartsScore(json);
}

void DartsScoreMultiAttempt::handleRequestFromUI()
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
        auto winnerName = _scoreController->winnerUserName();
        QJsonObject jsonObject = {{"winner",winnerName}};
        auto json = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact);
        emit winnerDeclared(json);
    }
    else if(status() == ControllerState::resetState)
    {
        setCurrentStatus(ControllerState::Initialized);
        emit controllerIsInitializedAndReady();
    }
}

void DartsScoreMultiAttempt::nextTurn()
{
    _indexController->next();
    setCurrentStatus(ControllerState::AwaitsInput);
    sendCurrentTurnValues();
}

void DartsScoreMultiAttempt::declareWinner()
{
    auto index = _indexController->setIndex();
    auto currentPlayerId = _scoreController->playerIdAtIndex(index);
    _scoreController->setWinner(currentPlayerId);
    setCurrentStatus(ControllerState::WinnerDeclared);
}

DartsScoreMultiAttempt *DartsScoreMultiAttempt::setJsonService(IDartsMultiAttemptJsonService *jsonService)
{
    _jsonService = jsonService;
    return this;
}

int DartsScoreMultiAttempt::currentStatus() const
{
    return _currentStatus;
}

void DartsScoreMultiAttempt::initializeControllerIndexes(const QByteArray& json)
{
    auto jsonObject = QJsonDocument::fromJson(json).object();
    auto totalTurns = jsonObject["totalTurns"].toInt();
    auto turns = jsonObject["turnIndex"].toInt();
    auto roundIndex = jsonObject["roundIndex"].toInt();
    auto setIndex = jsonObject["setIndex"].toInt();
    _indexController->setIndexes(totalTurns,turns,
                                  roundIndex,setIndex);
    emit requestTournamentAssignedPlayerDetails(tournament());
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
                                         const int &score)
{
    switch (domain)
    {
        // In case user enters scores above 180
    case InputOutOfRange : sendCurrentTurnValues();break;
        case PointDomain : addPoint(score);break;
        case CriticalDomain : addPoint(score);break;
        case TargetDomain : {
            declareWinner();
            addPoint(score);
            break;
        }
        case OutsideDomain : addPoint(0);break;
    }
}

DartsScoreMultiAttempt* DartsScoreMultiAttempt::setScoreController(IPlayerScoreService *scoreController)
{
    _scoreController = scoreController;
    return this;
}

DartsScoreMultiAttempt* DartsScoreMultiAttempt::setIndexController(IDartsMultiAttemptIndexService *indexController)
{
    _indexController = indexController;
    return this;
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

IDartsLogisticsService<QString> *DartsScoreMultiAttempt::pointLogisticInterface() const
{
    return _pointLogisticInterface;
}

DartsScoreMultiAttempt *DartsScoreMultiAttempt::setLogisticInterface(IDartsLogisticsService<QString> *pointLogisticInterface)
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
    auto model = _jsonService->assembleExtendedInputModelFromJson(json);
    _scoreController->addPlayerScore(model->playerId,model->score);
    auto newScore = _scoreController->playerScore(model->playerId);
    auto playerName = _scoreController->playerNameById(model->playerId);
    auto data = _jsonService->assembleJsonDartsScore(playerName,newScore);
    emit scoreRemoved(data);
}

void DartsScoreMultiAttempt::redoSuccess(const QByteArray& json)
{
    auto model = _jsonService->assembleExtendedInputModelFromJson(json);
    _scoreController->subtractPlayerScore(model->playerId,model->score);
    auto newScore = _scoreController->playerScore(model->playerId);
    auto playerName = _scoreController->playerNameById(model->playerId);
    auto data = _jsonService->assembleJsonDartsScore(playerName,newScore);
    emit scoreAddedSuccess(data);
}

void DartsScoreMultiAttempt::initializeControllerPlayerDetails(const QByteArray &json)
{
    auto playerStructs = _jsonService->assemblePlayerDetailsStructsFromJson(json);
    _indexController->setPlayersCount(playerStructs.count());
    for (const auto &playerStruct : playerStructs)
        _scoreController->addPlayerEntity(playerStruct->playerId,playerStruct->playerName);
    emit requestTournamentDartsScores(tournament());
}

void DartsScoreMultiAttempt::initializeControllerDartsScores(const QByteArray &json)
{
    auto extendedPointStructs = _jsonService->
            assembleExtendedInputModelsFromJson(json);
    for (const auto &extendedPointStruct : extendedPointStructs) {
        _scoreController->subtractPlayerScore(extendedPointStruct->playerId,
                                              extendedPointStruct->score);
    }
    emit requestTournamentWinnerIdAndName(tournament());
}

void DartsScoreMultiAttempt::initializeControllerWinnerIdAndName(const QByteArray &json)
{
    auto winnerStruct = _jsonService->assembleWinnerStructFromJson(json);
    _scoreController->setWinner(winnerStruct->playerId);
    if(_scoreController->winnerId() != QUuid())
        setCurrentStatus(ControllerState::WinnerDeclared);
    else
        setCurrentStatus(ControllerState::Initialized);
    emit controllerIsInitialized();
}
