#include "dartsscorecontroller.h"

using namespace DartsScoreControllerContext;

void DartsScoreController::start()
{
    sendCurrentTurnValues();
}

void DartsScoreController::stop()
{
    emit controllerIsStopped();
}

void DartsScoreController::handleAndProcessUserInput(const QByteArray& json)
{
    auto score = _extractJson->getIntegerValueByKey(json,"score");
    auto setIndex = _indexService->setIndex();
    auto accumulatedScore = _inputService->calculateAccumulatedScoreCandidate(setIndex,score);
    auto domain = _inputEvaluator->validateInput(accumulatedScore);
    processDomain(domain,score);
}

void DartsScoreController::handleRequestForCurrentTournamentMetaData()
{
    auto tournament = this->tournament();
    emit sendCurrentTournamentId(tournament);
}

void DartsScoreController::assembleOrderedDartsScores()
{
    auto dartsScoreModels = _dartsScoreBuilder->createScoreModels(_inputService);
    auto json = _dartsJsonBuilderService->createJsonByDartsScoreModels(dartsScoreModels);
    emit sendMultiAttemptDartsScores(json);
}

void DartsScoreController::handleRequestDartsScores()
{
    auto tournamentId = tournament();
    emit requestDartsScores(tournamentId);
}

void DartsScoreController::handleScoreAddedToDataContext(const QByteArray &json)
{
    if(_status == WinnerDeclared)
        assembleAndSendWinnerValues();
    else
        assembleAndSendTurnValues(json);
}

void DartsScoreController::handleResetTournament()
{
    _indexService->reset();
    _inputService->resetScores();
    auto tournamentId = tournament();
    emit requestResetTournament(tournamentId);
}

void DartsScoreController::sendCurrentTurnValues()
{
    auto model = _turnValuesBuilder->createTurnValues(_indexService,_inputService,_scoreLogisticInterface);
    emit awaitsInput(model->toJson());
}

QString DartsScoreController::currentPlayerName()
{
    auto index = _indexService->setIndex();
    auto playerName = _inputService->playerNameByIndex(index);
    return playerName;
}

QUuid DartsScoreController::currentPlayerId()
{
    auto index = _indexService->setIndex();
    auto playerID = _inputService->playerIdAtIndex(index);
    return playerID;
}

QUuid DartsScoreController::tournament()
{
    return _tournamentId;
}

int DartsScoreController::status()
{
    return _status;
}

int DartsScoreController::lastPlayerIndex()
{
    auto playerCount = _inputService->playersCount();
    auto lastIndex = playerCount - 1;
    return lastIndex;
}


QUuid DartsScoreController::undoTurn()
{
    if(status() == ControllerState::WinnerDeclared)
        return QUuid();
    _indexService->undo();
    auto roundIndex = _indexService->roundIndex();
    emit hideDartsScore(tournament(),
                        currentPlayerId(),
                        roundIndex);
    auto playerId = currentPlayerId();
    return playerId;
}

QUuid DartsScoreController::redoTurn()
{
    auto activeUser = currentPlayerId();
    auto roundIndex = _indexService->roundIndex();
    emit revealDartsScore(tournament(),
                          activeUser,
                          roundIndex);
    auto index = _indexService->setIndex();
    auto playerId = _inputService->playerIdAtIndex(index);
    return playerId;
}

void DartsScoreController::addScore(const int& score)
{
    auto indexes = _dartsIndexesBuilderService->buildControllerIndexesByIndexService(_indexService);
    auto scoreModel = _dartsScoreBuilder->createScoreModel(score);
    auto playerModel = _playerBuilderService->createPlayerModelByValues(currentPlayerId(),currentPlayerName());
    auto json = createJsonResponse(scoreModel,indexes,playerModel);
    emit requestAddDartsScore(json);
}

void DartsScoreController::handleRequestFromUI()
{
    if(_status == ControllerState::WinnerDeclared)
        assembleAndSendWinnerValues();
    else
        emit controllerInitializedAndReady();
}

void DartsScoreController::nextTurn()
{
    _indexService->next();
    sendCurrentTurnValues();
}

void DartsScoreController::declareWinner()
{
    auto index = _indexService->setIndex();
    auto currentPlayerId = _inputService->playerIdAtIndex(index);
    _inputService->setWinner(currentPlayerId);
    setCurrentStatus(ControllerState::WinnerDeclared);
}

int DartsScoreController::currentStatus() const
{
    return _status;
}

void DartsScoreController::initializeControllerIndexes(const QByteArray& json)
{
    auto indexes = _dartsIndexesBuilderService->buildControllerIndexesByJson(json);
    _indexService->setIndexes(indexes);
    emit requestTournamentAssignedPlayerDetails(tournament());
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
    _status = currentStatus;
}

DartsScoreController *DartsScoreController::createInstance(const QUuid &tournament, const int &displayHint)
{
    return new DartsScoreController(tournament,displayHint);
}

IDartsInputSuggestion<QString> *DartsScoreController::pointLogisticInterface() const
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
    auto scoreModel = _dartsScoreBuilder->createScoreModel(json);
    auto currentScore = _inputService->addPlayerScore(scoreModel->playerId(),scoreModel->score());
    _addTotalScoreToModel->addScoretoModel(scoreModel,currentScore);
    auto turnValues = _turnValuesBuilder->createTurnValues(_indexService,_inputService,_scoreLogisticInterface);
    QByteArray jsonResponse = createJsonResponse(scoreModel,turnValues);
    emit scoreRemoved(jsonResponse);
}

void DartsScoreController::redoSuccess(const QByteArray& json)
{
    auto scoreModel = _dartsScoreBuilder->createScoreModel(json);
    subtractAndAddScoreToModel(scoreModel);
    _indexService->redo();
    auto turnValues = _turnValuesBuilder->createTurnValues(_indexService,_inputService,
                                                           _scoreLogisticInterface);
    QByteArray jsonResponse = createJsonResponse(scoreModel,turnValues);
    emit scoreAddedSuccess(jsonResponse);
}

DartsScoreController::DartsScoreController(const QUuid &tournament, const int &displayHint)
{
    _tournamentId = tournament;
    _displayHint = displayHint;
}

void DartsScoreController::assembleAndSendTurnValues(const QByteArray &json)
{
    auto dartsScore = _dartsScoreBuilder->createScoreModel(json);
    auto totalScore = _inputService->subtractPlayerScoreByModel(dartsScore);
    _addTotalScoreToModel->addScoretoModel(dartsScore,totalScore);
    nextTurn();
    auto turnValues = _turnValuesBuilder->createTurnValues(_indexService,_inputService,
                                                           _scoreLogisticInterface);
    QByteArray jsonResponse = createJsonResponse(dartsScore,turnValues);
    emit scoreAddedSuccess(jsonResponse);
}

void DartsScoreController::assembleAndSendWinnerValues()
{
    auto winnerName = _inputService->winnerUserName();
    auto winnerId = _inputService->winnerId();
    auto json = createJsonResponse(winnerId,winnerName);
    emit winnerDeclared(json);
}

void DartsScoreController::subtractAndAddScoreToModel(const ControllerScore *scoreModel)
{
    auto newScore = _inputService->subtractPlayerScoreByModel(scoreModel);
    _addTotalScoreToModel->addScoretoModel(scoreModel,newScore);
}

QByteArray DartsScoreController::createJsonResponse(const QUuid &winnerId,const QString &winnerName)
{
    QByteArray json;
    auto winnerIdJson = _dartsJsonBuilder->createJsonByKey(winnerId,"winnerId");
    auto winnerNameJson = _dartsJsonBuilder->createJsonByKey(winnerName,"winnerName");
    auto tournamentJson = _dartsJsonBuilder->createJsonByKey(_tournamentId,"tournamentId");
    _jsonMergeService->mergeIntoJson(json,winnerIdJson);
    _jsonMergeService->mergeIntoJson(json,winnerNameJson);
    _jsonMergeService->mergeIntoJson(json,tournamentJson);
    return json;
}

QByteArray DartsScoreController::createJsonResponse(const ControllerScore *scoreModel, const DartsScoreTurnValues *turnValues)
{
    QByteArray jsonResponse;
    _jsonMergeService->mergeIntoJson(jsonResponse,scoreModel->toJson());
    _jsonMergeService->mergeIntoJson(jsonResponse,turnValues->toJson());
    return jsonResponse;
}

QByteArray DartsScoreController::createJsonResponse(const ControllerScore *scoreModel,
                                                    const ControllerIndexes *indexes,
                                                    const DartsPlayer* playerModel)
{
    auto tournamentJson = _dartsJsonBuilder->createJsonByKey(_tournamentId,"tournamentId");
    QByteArray json;
    _jsonMergeService->mergeIntoJson(json,scoreModel->toJson());
    _jsonMergeService->mergeIntoJson(json,indexes->toJson());
    _jsonMergeService->mergeIntoJson(json,playerModel->toJson());
    _jsonMergeService->mergeIntoJson(json,tournamentJson);
    return json;
}

void DartsScoreController::initializeControllerPlayerDetails(const QByteArray &json)
{
    auto dartsPlayerModels = _playerBuilderService->buildPlayerModelsByJson(json);
    _indexService->setPlayersCount(dartsPlayerModels.count());
    _inputService->addPlayerEntities(dartsPlayerModels);
    emit requestTournamentDartsScores(tournament());
}

void DartsScoreController::initializeControllerDartsScores(const QByteArray &json)
{
    auto dartsScores= _dartsScoreBuilder->createScoreModels(json);
    _inputService->subtractPlayerScoreByModels(dartsScores);
    emit requestTournamentWinnerIdAndName(tournament());
}

void DartsScoreController::initializeControllerWinnerIdAndName(const QByteArray &json)
{
    auto dartsPlayer = _playerBuilderService->buildPlayerModelByJson(json);
    _inputService->setWinner(dartsPlayer->playerId());
    auto status = _determineControllerStateByWinnerId->service(dartsPlayer->playerId());
    setCurrentStatus(status);
    emit controllerInitialized(_displayHint);
}
