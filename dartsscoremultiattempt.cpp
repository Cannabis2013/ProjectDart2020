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
    auto jsonIndexObject = jsonObject["indexes"].toObject();
    auto totalTurns = jsonIndexObject["totalTurns"].toInt();
    auto turns = jsonIndexObject["turns"].toInt();
    auto roundIndex = jsonIndexObject["roundIndex"].toInt();
    auto setIndex = jsonIndexObject["setIndex"].toInt();
    auto attemptIndex = jsonIndexObject["attemptIndex"].toInt();
    indexController()->setIndexes(totalTurns,turns,
                                  roundIndex,setIndex,
                                  attemptIndex);
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
    scoreController()->addPlayerScore(model->playerId,model->score);
    auto newScore = scoreController()->playerScore(model->playerId);
    auto playerName = scoreController()->playerNameById(model->playerId);
    auto data = _jsonService->assembleJsonDartsScore(playerName,newScore);
    emit scoreRemoved(data);
}

void DartsScoreMultiAttempt::redoSuccess(const QByteArray& json)
{
    auto model = _jsonService->assembleExtendedInputModelFromJson(json);
    scoreController()->subtractPlayerScore(model->playerId,model->score);
    auto newScore = scoreController()->playerScore(model->playerId);
    auto playerName = scoreController()->playerNameById(model->playerId);
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
    emit dartsMultiAttemptScoreControllerIsInitialized();
}
