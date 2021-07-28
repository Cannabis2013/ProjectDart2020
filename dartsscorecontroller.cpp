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
    auto tournament = _metaData->tournamentId();
    emit sendCurrentTournamentId(tournament);
}

void DartsScoreController::createOrderedDartsScores()
{
    auto dartsScoreModels = _dartsScoreBuilder->createScoreModels(_inputService);
    auto json = _dartsJsonBuilderService->createJsonByDartsScoreModels(dartsScoreModels);
    emit sendMultiAttemptDartsScores(json);
}

void DartsScoreController::handleRequestDartsScores()
{
    auto tournamentId = _metaData->tournamentId();
    emit requestDartsScores(tournamentId);
}

void DartsScoreController::handleScoreAddedToDataContext(const QByteArray &json)
{
    if(_metaData->status() == WinnerDeclared)
        createAndSendWinnerValues();
    else
        createAndSendTurnValues(json);
}

void DartsScoreController::handleResetTournament()
{
    _indexService->reset();
    _inputService->resetScores();
    auto tournamentId = _metaData->tournamentId();
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

int DartsScoreController::lastPlayerIndex()
{
    auto playerCount = _inputService->playersCount();
    auto lastIndex = playerCount - 1;
    return lastIndex;
}


QUuid DartsScoreController::undoTurn()
{
    if(_metaData->status() == ControllerState::WinnerDeclared)
        return QUuid();
    _indexService->undo();
    auto roundIndex = _indexService->roundIndex();
    emit hideDartsScore(_metaData->tournamentId(),
                        currentPlayerId(),
                        roundIndex);
    auto playerId = currentPlayerId();
    return playerId;
}

QUuid DartsScoreController::redoTurn()
{
    auto activeUser = currentPlayerId();
    auto roundIndex = _indexService->roundIndex();
    emit revealDartsScore(_metaData->tournamentId(),
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
    if(_metaData->status() == ControllerState::WinnerDeclared)
        createAndSendWinnerValues();
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
    _metaData->setStatus(ControllerState::WinnerDeclared);
}

void DartsScoreController::initializeControllerIndexes(const QByteArray& json)
{
    auto indexes = _dartsIndexesBuilderService->buildControllerIndexesByJson(json);
    _indexService->setIndexes(indexes);
    emit requestTournamentAssignedPlayerDetails(_metaData->tournamentId());
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

DartsScoreController *DartsScoreController::createInstance()
{
    return new DartsScoreController();
}

IDartsInputSuggestion<QString> *DartsScoreController::pointLogisticInterface() const
{
    return _scoreLogisticInterface;
}

void DartsScoreController::beginInitialize()
{
    emit requestDartsTournamentIndexes(_metaData->tournamentId());
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

void DartsScoreController::createAndSendTurnValues(const QByteArray &json)
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

void DartsScoreController::createAndSendWinnerValues()
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

    auto json = _jsonMergeService->createJsonFromList({_dartsJsonBuilder->createJson(winnerId,"winnerId"),
                                                       _dartsJsonBuilder->createJson(winnerName,"winnerName"),
                                                       _dartsJsonBuilder->createJson(_metaData->tournamentId(),"tournamentId")});
    return json;
}

QByteArray DartsScoreController::createJsonResponse(const ControllerScore *scoreModel,
                                                    const DartsScoreTurnValues *turnValues)
{
    auto jsonResponse = _jsonMergeService->createJsonFromList({scoreModel->toJson(),turnValues->toJson()});
    return jsonResponse;
}

QByteArray DartsScoreController::createJsonResponse(const ControllerScore *scoreModel,
                                                    const ControllerIndexes *indexes,
                                                    const DartsPlayer* playerModel)
{
    QByteArray json = _jsonMergeService->createJsonFromList({_dartsJsonBuilder->createJson(_metaData->tournamentId(),"tournamentId"),
                                                             scoreModel->toJson(),indexes->toJson(),playerModel->toJson()});
    return json;
}

void DartsScoreController::initializeControllerPlayerDetails(const QByteArray &json)
{
    auto dartsPlayerModels = _playerBuilderService->createModels(json);
    _indexService->setPlayersCount(dartsPlayerModels.count());
    _inputService->addPlayerEntities(dartsPlayerModels);
    emit requestTournamentDartsScores(_metaData->tournamentId());
}

void DartsScoreController::initializeControllerDartsScores(const QByteArray &json)
{
    auto dartsScores= _dartsScoreBuilder->createScoreModels(json);
    _inputService->subtractPlayerScoreByModels(dartsScores);
    emit requestTournamentWinnerIdAndName(_metaData->tournamentId());
}

void DartsScoreController::initializeControllerWinnerIdAndName(const QByteArray &json)
{
    auto dartsPlayer = _playerBuilderService->createModel(json);
    _inputService->setWinner(dartsPlayer->playerId());
    auto status = _determineControllerStateByWinnerId->service(dartsPlayer->playerId());
    _metaData->setStatus(status);
    emit controllerInitialized(_metaData->displayHint());
}
