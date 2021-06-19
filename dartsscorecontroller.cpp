#include "dartsscorecontroller.h"

using namespace DartsScoreControllerContext;

void DartsScoreController::start()
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

void DartsScoreController::stop()
{
    setCurrentStatus(ControllerState::Stopped);
    emit controllerIsStopped();
}

void DartsScoreController::handleAndProcessUserInput(const QByteArray& json)
{
    auto score = _dartsJsonExtractorService->getPlayerScoreByJson(json);
    auto setIndex = _indexService->setIndex();
    auto accumulatedScore = _scoreController->calculateAccumulatedScoreCandidate(setIndex,score);
    auto domain = _inputEvaluator->validateInput(accumulatedScore);
    processDomain(domain,score);
}

void DartsScoreController::handleRequestForCurrentTournamentMetaData()
{
    auto tournament = this->tournament();
    emit sendCurrentTournamentId(tournament);
}

void DartsScoreController::assembleMultiAttemptDartsScores()
{
    auto dartsScoreModels = _dartsScoreBuilderService->buildModelsByModelsService(_scoreController);
    auto json = _dartsJsonBuilderService->buildJsonByDartsScoreModels(dartsScoreModels);
    emit sendMultiAttemptDartsScores(json);
}

void DartsScoreController::handleRequestDartsScores()
{
    auto tournamentId = tournament();
    emit requestDartsScores(tournamentId);
}

void DartsScoreController::handleScoreAddedToDataContext(const QByteArray &json)
{
    auto dartsScore = _dartsScoreBuilderService->buildModelByJson(json);
    auto totalScore = _scoreController->subtractPlayerScoreByModel(dartsScore);
    _indexService->syncIndex();
    _addAccumulatedScoreToModel->service(dartsScore,totalScore);
    emit scoreAddedSuccess(dartsScore->toJson());
}

void DartsScoreController::handleResetTournament()
{
    _currentStatus = ControllerState::resetState;
    _indexService->reset();
    _scoreController->resetScores();
    auto tournamentId = tournament();
    emit requestResetTournament(tournamentId);
}

void DartsScoreController::sendCurrentTurnValues()
{
    auto model = _turnValuesBuilderService->service(_indexService,_scoreController,_scoreLogisticInterface);
    emit isReadyAndAwaitsInput(model->toJson());
}

QString DartsScoreController::currentActiveUser()
{
    auto index = _indexService->setIndex();
    auto playerName = _scoreController->playerNameByIndex(index);
    return playerName;
}

QUuid DartsScoreController::currentActivePlayerId()
{
    auto index = _indexService->setIndex();
    auto playerID = _scoreController->playerIdAtIndex(index);
    return playerID;
}

QUuid DartsScoreController::tournament()
{
    return _tournament;
}

int DartsScoreController::status()
{
    return _currentStatus;
}

int DartsScoreController::lastPlayerIndex()
{
    auto playerCount = _scoreController->playersCount();
    auto lastIndex = playerCount - 1;
    return lastIndex;
}


QUuid DartsScoreController::undoTurn()
{
    if(status() == ControllerState::WinnerDeclared)
        return QUuid();
    _currentStatus = ControllerState::UndoState;
    _indexService->undo();
    auto roundIndex = _indexService->roundIndex();
    emit hideDartsScore(tournament(),
                        currentActivePlayerId(),
                        roundIndex);
    auto playerId = currentActivePlayerId();
    return playerId;
}

QUuid DartsScoreController::redoTurn()
{
    setCurrentStatus(ControllerState::RedoState);
    auto activeUser = currentActivePlayerId();
    auto roundIndex = _indexService->roundIndex();
    _indexService->redo();
    emit revealDartsScore(tournament(),
                          activeUser,
                          roundIndex);
    auto index = _indexService->setIndex();
    auto playerId = _scoreController->playerIdAtIndex(index);
    return playerId;
}

void DartsScoreController::addScore(const int& score)
{
    if(currentStatus() != ControllerState::WinnerDeclared)
        setCurrentStatus(ControllerState::AddScoreState);
    auto indexes = _dartsIndexesBuilderService->buildControllerIndexesByIndexService(_indexService);
    auto scoreModel = _dartsScoreBuilderService->buildModelByValues(score,
                                                                    currentActivePlayerId(),
                                                                    currentActiveUser(),
                                                                    tournament());
    auto json = _dartsJsonBuilderService->buildJsonAddScoreValues(indexes,scoreModel);
    emit requestAddDartsScore(json);
}

void DartsScoreController::handleRequestFromUI()
{
    if(status() == ControllerState::Initialized)
    {
        emit controllerInitializedAndReady();
    }
    else if(status() == ControllerState::AddScoreState)
    {
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
        auto json = _dartsJsonBuilderService->assembleJsonWinnerName(tournament(),
                                                         _scoreController->winnerId());
        emit winnerDeclared(json);
    }
    else if(status() == ControllerState::resetState)
    {
        setCurrentStatus(ControllerState::Initialized);
        emit controllerInitializedAndReady();
    }
}

void DartsScoreController::nextTurn()
{
    _indexService->next();
    setCurrentStatus(ControllerState::AwaitsInput);
    sendCurrentTurnValues();
}

void DartsScoreController::declareWinner()
{
    auto index = _indexService->setIndex();
    auto currentPlayerId = _scoreController->playerIdAtIndex(index);
    _scoreController->setWinner(currentPlayerId);
    setCurrentStatus(ControllerState::WinnerDeclared);
}

int DartsScoreController::currentStatus() const
{
    return _currentStatus;
}

void DartsScoreController::initializeControllerIndexes(const QByteArray& json)
{
    auto indexes = _dartsIndexesBuilderService->buildControllerIndexesByJson(json);
    _indexService->setIndexes(indexes);
    emit requestTournamentAssignedPlayerDetails(tournament());
}

bool DartsScoreController::isBusy()
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

void DartsScoreController::processDomain(const int &domain,
                                         const int &score)
{
    switch (domain)
    {
        case InputOutOfRange : sendCurrentTurnValues();break;
        case PointDomain : addScore(score);break;
        case CriticalDomain : addScore(score);break;
        case TargetDomain : {
            declareWinner();
            addScore(score);
            break;
        }
        case OutsideDomain : addScore(0);break;
    }
}

void DartsScoreController::setCurrentStatus(int currentStatus)
{
    _currentStatus = currentStatus;
}

DartsScoreController *DartsScoreController::createInstance(const QUuid &tournament, const int &displayHint)
{
    return new DartsScoreController(tournament,displayHint);
}

IDartsLogisticsService<QString> *DartsScoreController::pointLogisticInterface() const
{
    return _scoreLogisticInterface;
}

void DartsScoreController::beginInitialize()
{
    auto tournamentId = tournament();
    emit requestDartsTournamentIndexes(tournamentId);
}

void DartsScoreController::undoSuccess(const QByteArray& json)
{
    auto dartsScoreModel = _dartsScoreBuilderService->buildModelByJson(json);
    auto newScore = _scoreController->addPlayerScore(dartsScoreModel->playerId(),dartsScoreModel->score());
    _addAccumulatedScoreToModel->service(dartsScoreModel,newScore);
    emit scoreRemoved(dartsScoreModel->toJson());
}

void DartsScoreController::redoSuccess(const QByteArray& json)
{
    auto dartsScoreModel = _dartsScoreBuilderService->buildModelByJson(json);
    auto newScore = _scoreController->subtractPlayerScoreByModel(dartsScoreModel);
    _addAccumulatedScoreToModel->service(dartsScoreModel,newScore);
    emit scoreAddedSuccess(dartsScoreModel->toJson());
}

DartsScoreController::DartsScoreController(const QUuid &tournament, const int &displayHint)
{
    _tournament = tournament;
    _displayHint = displayHint;
}

void DartsScoreController::initializeControllerPlayerDetails(const QByteArray &json)
{
    auto dartsPlayerModels = _playerBuilderService->buildPlayerModelsByJson(json);
    _indexService->setPlayersCount(dartsPlayerModels.count());
    _scoreController->addPlayerEntities(dartsPlayerModels);
    emit requestTournamentDartsScores(tournament());
}

void DartsScoreController::initializeControllerDartsScores(const QByteArray &json)
{
    auto dartsScores= _dartsScoreBuilderService->buildModelsByJson(json);
    _scoreController->subtractPlayerScoreByModels(dartsScores);
    emit requestTournamentWinnerIdAndName(tournament());
}

void DartsScoreController::initializeControllerWinnerIdAndName(const QByteArray &json)
{
    auto dartsPlayer = _playerBuilderService->buildPlayerModelByJson(json);
    _scoreController->setWinner(dartsPlayer->playerId());
    auto status = _determineControllerStateByWinnerId->service(dartsPlayer->playerId());
    setCurrentStatus(status);
    emit controllerInitialized(_displayHint);
}
