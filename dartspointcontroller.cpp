#include "dartspointcontroller.h"

using namespace DartsPointControllerContext;

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
    auto dartsPointModel = _pointModelBuilderService->buildControllerPointByJson(json);
    auto dartsPointModelWithScore = _calculateScoreByPointInput->calculateScoreFromDartsPoint(dartsPointModel);
    auto setIndex = _indexController->setIndex();
    auto accumulatedScore = _playerPointsService->calculateAccumulatedScoreCandidate(setIndex,dartsPointModelWithScore->score());
    auto domain = _inputEvaluator->validateInput(accumulatedScore,
                                                  dartsPointModel->modKeyCode(),
                                                  dartsPointModel->point());
    processDomain(domain,dartsPointModel->point(),dartsPointModelWithScore->score(),dartsPointModel->modKeyCode());
}

void DartsPointController::handleRequestForCurrentTournamentMetaData()
{
    auto tournament = this->tournament();
    emit sendCurrentTournamentId(tournament);
}

void DartsPointController::handleRequestDartsPoints()
{
    auto tournamentId = tournament();
    emit requestDartsPointsOrderedByIndexes(tournamentId);
}

void DartsPointController::handlePointAddedToDataContext(const QByteArray &json)
{
    auto dartsPointModel = _pointModelBuilderService->buildControllerPointByJson(json);
    auto dartsPointModelWithScore = _calculateScoreByPointInput->calculateScoreFromDartsPoint(dartsPointModel);
    // Subtract score value from current user score
    _playerPointsService->subtractPlayerScore(dartsPointModelWithScore);
    // Sync totalturns with the current turn index
    _indexController->syncIndex();
    auto scoreValue = _playerPointsService->playerScore(dartsPointModel->playerId());
    _controllerModelsService->addPlayerNameToModel(dartsPointModel,currentUserName());
    _controllerModelsService->addAccumulatedScoreToModel(dartsPointModel,scoreValue);
    emit pointAddedAndPersisted(dartsPointModel->toJson());
}

void DartsPointController::handleResetTournament()
{
    _currentStatus = ControllerState::resetState;
    _indexController->reset();
    _playerPointsService->resetScores();
    auto tournamentId = tournament();
    emit requestResetTournament(tournamentId);
}

void DartsPointController::sendCurrentTurnValues()
{
    auto turnValues = _dartsTurnValuesBuilderService->buildTurnValues(_indexController,
                                                                      _playerPointsService,
                                                                      _pointLogisticInterface);
    emit isReadyAndAwaitsInput(turnValues->toJson());
}

QString DartsPointController::currentUserName()
{
    auto index = _indexController->setIndex();
    auto playerName = _playerPointsService->playerNameByIndex(index);
    return playerName;
}

QUuid DartsPointController::currentPlayerId()
{
    auto index = _indexController->setIndex();
    auto playerID = _playerPointsService->playerIdAtIndex(index);
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
    auto playerCount = _playerPointsService->playersCount();
    auto lastIndex = playerCount - 1;
    return lastIndex;
}


QUuid DartsPointController::undoTurn()
{
    if(status() == ControllerState::WinnerDeclared)
        return QUuid();
    _currentStatus = ControllerState::UndoState;
    _indexController->undo();
    auto roundIndex = _indexController->roundIndex();
    auto attemptIndex = _indexController->attemptIndex();
    emit hideDartsPoint(tournament(),currentPlayerId(),roundIndex,attemptIndex);
    return currentPlayerId();
}

QUuid DartsPointController::redoTurn()
{
    setCurrentStatus(ControllerState::RedoState);
    auto activeUser = currentPlayerId();
    auto roundIndex = _indexController->roundIndex();
    auto attemptIndex = _indexController->attemptIndex();
    _indexController->redo();
    emit revealDartsPoint(tournament(),activeUser,roundIndex,attemptIndex);
    auto index = _indexController->setIndex();
    return _playerPointsService->playerIdAtIndex(index);
}

void DartsPointController::addPoint(const int& point,
                                    const int &score,
                                    const int& keyCode)
{
    setStateIfNoWinnerDetermined();
    auto pointModel = _pointModelBuilderService->buildControllerPointByInputValues(point,score,keyCode);
    updatePlayerPointModel(pointModel);
    auto indexes = _dartsIndexesBuilderService->buildControllerIndexesByIndexService(_indexController);
    auto json = createJson(indexes,pointModel);
    emit requestAddDartsPoint(json);
}

void DartsPointController::handleRequestFromUI()
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
        auto winnerName = _playerPointsService->winnerUserName();
        auto json = _dartsJsonService->assembleJsonWinnerName(winnerName);
        emit winnerDeclared(json);
    }
    else if(status() == ControllerState::resetState)
    {
        setCurrentStatus(ControllerState::Initialized);
        emit controllerInitializedAndReady();
    }
}

void DartsPointController::nextTurn()
{
    _indexController->next();
    setCurrentStatus(ControllerState::AwaitsInput);
    sendCurrentTurnValues();
}

void DartsPointController::declareWinner()
{
    auto index = _indexController->setIndex();
    auto currentPlayerId = _playerPointsService->playerIdAtIndex(index);
    _playerPointsService->setWinner(currentPlayerId);
    setCurrentStatus(ControllerState::WinnerDeclared);
}

void DartsPointController::handleOrderedDartsPoint(const QByteArray &json)
{
    auto models = _getOrderedDartsPointsByJson->getOrderedDartsPointsFromJson(json);
    _addTotalScoresServices->addTotalScoreToInputs(models,_playerPointsService->initialScore());
    auto inputModelsJson = _dartsPointsToJson->toJson(models);
    emit sendDartsPoints(inputModelsJson);
}

int DartsPointController::currentStatus() const
{
    return _currentStatus;
}

void DartsPointController::initializeControllerIndexes(const QByteArray& json)
{
    auto indexes = _dartsIndexesBuilderService->buildControllerIndexesByJson(json);
    _indexController->setIndexes(indexes);
    emit requestTournamentAssignedPlayerDetails(tournament());
}

void DartsPointController::processDomain(const int& domain,
                                         const int& point,
                                         const int &score,
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

void DartsPointController::setCurrentStatus(int currentStatus)
{
    _currentStatus = currentStatus;
}

void DartsPointController::beginInitialize()
{
    auto tournamentId = tournament();
    emit requestDartsTournamentIndexes(tournamentId);
}

void DartsPointController::undoSuccess(const QByteArray& json)
{
    auto dartsPointModel = _pointModelBuilderService->buildControllerPointByJson(json);
    auto dartsPointModelWithScore = _calculateScoreByPointInput->calculateScoreFromDartsPoint(dartsPointModel);
    _playerPointsService->addPlayerScore(dartsPointModelWithScore);
    auto newScore = _playerPointsService->playerScore(dartsPointModel->playerId());
    auto playerName = _playerPointsService->playerNameById(dartsPointModel->playerId());
    _controllerModelsService->addPlayerNameToModel(dartsPointModel,playerName);
    _controllerModelsService->addAccumulatedScoreToModel(dartsPointModel,newScore);
    emit pointRemoved(dartsPointModel->toJson());
}

void DartsPointController::redoSuccess(const QByteArray& json)
{
    auto dartsPointModel = _pointModelBuilderService->buildControllerPointByJson(json);
    auto dartsPointModelWithScore = _calculateScoreByPointInput->calculateScoreFromDartsPoint(dartsPointModel);
    _playerPointsService->subtractPlayerScore(dartsPointModelWithScore);
    auto newScore = _playerPointsService->playerScore(dartsPointModelWithScore->playerId());
    auto playerName = _playerPointsService->playerNameById(dartsPointModelWithScore->playerId());
    _controllerModelsService->addPlayerNameToModel(dartsPointModelWithScore,playerName);
    _controllerModelsService->addAccumulatedScoreToModel(dartsPointModelWithScore,newScore);
    emit pointAddedAndPersisted(dartsPointModelWithScore->toJson());
}

DartsPointController::DartsPointController(const QUuid &tournament, const int &displayHint)
{
    _tournament = tournament;
    _displayHint = displayHint;
}

void DartsPointController::updatePlayerPointModel(const IControllerPoint *pointModel)
{
    _controllerModelsService->addPlayerIdToModel(pointModel,currentPlayerId());
    _controllerModelsService->addPlayerNameToModel(pointModel,currentUserName());
    _controllerModelsService->addTournamentIdToModel(pointModel,tournament());
}

QByteArray DartsPointController::createJson(const IDartsPointControllerIndexes *indexes, const IControllerPoint *pointModel)
{
    auto indexesJson = _dartsJsonService->convertDartsIndexesToJson(indexes);
    auto pointModelJson = _dartsJsonService->convertDartsModelToJson(pointModel);
    auto json = _combineDartsIndexesAndDartsPoint->combineJson(indexesJson,pointModelJson);
    return json;
}

void DartsPointController::setStateIfNoWinnerDetermined()
{
    if(currentStatus() != ControllerState::WinnerDeclared)
        setCurrentStatus(ControllerState::AddScoreState);
}


void DartsPointController::initializeControllerPlayerDetails(const QByteArray& json)
{
    auto playerModels = _playerModelBuilderService->buildPlayerModelsByJson(json);
    _indexController->setPlayersCount(playerModels.count());
    _playerPointsService->addPlayerEntitiesByModels(playerModels);
    emit requestTournamentDartsPoints(tournament());
}

void DartsPointController::initializeControllerDartsPoints(const QByteArray& json)
{
    auto points = _pointModelBuilderService->buildControllerPointsByJson(json);
    _calculateScoreByPointInput->addCalculatedScoreToDartsPoints(points);
    _playerPointsService->subtractPlayerScoresByModels(points);
    emit requestTournamentWinnerIdAndName(tournament());
}

void DartsPointController::initializeControllerWinnerIdAndName(const QByteArray& json)
{
    auto winnerId = _dartsJsonService->getWinnerIdByJson(json);
    _playerPointsService->setWinner(winnerId);
    if(_playerPointsService->winnerId() != QUuid())
        setCurrentStatus(ControllerState::WinnerDeclared);
    else
        setCurrentStatus(ControllerState::Initialized);
    emit controllerInitialized(_displayHint);
}
