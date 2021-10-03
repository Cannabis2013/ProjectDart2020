#include "dartscontroller.h"
using namespace DCContext;
void DartsController::start()
{
    sendCurrentTurnValues();
}

void DartsController::stop()
{
    emit controllerIsStopped();
}

void DartsController::handleUserInput(const QByteArray& json)
{
    auto input = createInputModel()->createModel(json,inputKeys(),tournamentId()->id(),
                                                 playerService()->currentPlayerId(),playerService()->currentPlayerName());
    auto scoreCandidate = getScoreFromInput()->getScore(input);
    input->setScore(scoreCandidate);
    auto setIndex = indexService()->setIndex();
    auto accumulatedScore = getTotalScore()->scoreCandidate(setIndex,scoreCandidate,scoresService());
    inputEvaluator()->validateInput(accumulatedScore,inputKeyCodes(),input);
}

void DartsController::handleRequestForCurrentTournamentMetaData()
{
    auto tournament = tournamentId()->id();
    emit sendCurrentTournamentId(tournament);
}

void DartsController::createDartsScores()
{
    auto dartsScoreModels = createInputModels()->createModels(scoresService(),createInputModel());
    auto arr = createEmptyJsonObject()->emptyJsonArray();
    inputsToJson()->setJsonValues(arr,dartsScoreModels,inputKeys());
    emit sendDartsScores(createByteArray()->byteArray(arr));
}

void DartsController::getOrderedInputsWithTotalScores()
{
    emit requestOrderedInputs(tournamentId()->id());
}

void DartsController::handleUserInputAdded(const QByteArray &json)
{
    if(metaStatus()->get() == statusCodes()->winnerFound())
        createAndSendWinnerValues();
    else
        updateTotalScore(json);
}

void DartsController::handleResetTournament()
{
    resetIndexes()->reset(indexService());
    resetScoreModels()->reset(scoresService(),initialScore()->score());
    metaStatus()->set(statusCodes()->initialized());
    emit requestResetTournament(tournamentId()->id());
}

void DartsController::sendCurrentTurnValues()
{
    auto model = createTurnValues()->turnValues(indexService(),scoresService(),suggestFinishes());
    auto obj = createEmptyJsonObject()->emptyJsonObject();
    turnValuesToJson()->setJsonValues(obj,model,turnValKeys());
    emit awaitsInput(createByteArray()->byteArray(obj));
}

int DartsController::lastPlayerIndex()
{
    auto playerCount = scoresService()->scoreModels().count();
    auto lastIndex = playerCount - 1;
    return lastIndex;
}

void DartsController::undoTurn()
{
    undoIndex()->undo(indexService(),scoresService());
    auto roundIndex = indexService()->roundIndex();
    auto attemptIndex = indexService()->attemptIndex();
    auto currentPlayerId = playerService()->currentPlayerId();
    emit hideInput(tournamentId()->id(),currentPlayerId,roundIndex,attemptIndex);
}

void DartsController::redoTurn()
{
    auto activeUser = playerService()->currentPlayerId();
    auto roundIndex = indexService()->roundIndex();
    auto attemptIndex = indexService()->attemptIndex();
    emit revealInput(tournamentId()->id(), activeUser, roundIndex,attemptIndex);
}

void DartsController::persistInput(DCContext::IDCInputModel *inputModel)
{
    auto indexes = indexesBuilder()->createIndexes(indexService());
    auto jsonObject = createEmptyJsonObject()->emptyJsonObject();
    inputsToJson()->setJsonValues(jsonObject,inputModel,inputKeys());
    indexesToJson()->toJson(jsonObject,indexes,indexKeys());
    emit requestAddDartsScore(createByteArray()->byteArray(jsonObject));
}

void DartsController::handleRequestFromUI()
{
    if(metaStatus()->get() == statusCodes()->winnerFound())
        createAndSendWinnerValues();
    else
        emit controllerInitializedAndReady();
}

void DartsController::nextTurn()
{
    indexIterator()->next(indexService(),scoresService());
    sendCurrentTurnValues();
}

void DartsController::declareWinnerAndPersistInput(IDCInputModel *inputModel)
{
    winnerService()->setWinner(inputModel->playerId(), inputModel->playerName());
    metaStatus()->set(statusCodes()->winnerFound());
    persistInput(inputModel);
}

void DartsController::connectInputEvaluator()
{
    if(inputEvaluator() == nullptr)
        throw "InputEvaluator service is null";
    connect(inputEvaluator(),&AbstractEvaluateDCInput::playerHitPointDomain,
            this,&DartsController::persistInput);
    connect(inputEvaluator(),&AbstractEvaluateDCInput::playerHitTargetDomain,
            this,&DartsController::declareWinnerAndPersistInput);
    connect(inputEvaluator(),&AbstractEvaluateDCInput::playerOutOfRange,
            this,&DartsController::nullifyAndPersistInput);
}

void DartsController::initializeControllerIndexes(const QByteArray& json)
{
    auto indexes = indexesBuilder()->createIndexes(json);
    initializeIndexes()->initialize(indexes,indexService());
    emit requestTournamentAssignedPlayerDetails(tournamentId()->id());
}

void DartsController::beginInitialize()
{
    connectInputEvaluator();
    emit requestDartsTournamentIndexes(tournamentId()->id());
}

void DartsController::undoSuccess(const QByteArray& json)
{
    QScopedPointer inputModel(createInputModel()->createModel(json,inputKeys()));
    QScopedPointer turnValues(createTurnValues()->turnValues(indexService(),scoresService(),suggestFinishes()));
    auto scoreModel = addScoreService()->addPlayerScore(inputModel.get(), scoresService());
    inputModel->setTotalScore(scoreModel.totalScore);
    auto jsonObject = createEmptyJsonObject()->emptyJsonObject();
    inputsToJson()->setJsonValues(jsonObject,inputModel.get(),inputKeys());
    turnValuesToJson()->setJsonValues(jsonObject,turnValues.get(),turnValKeys());
    emit scoreRemoved(createByteArray()->byteArray(jsonObject));
}

void DartsController::redoSuccess(const QByteArray& json)
{
    QScopedPointer<DCContext::IDCInputModel> inputModel(createInputModel()->createModel(json,inputKeys()));
    auto candidateScore = subtractScore()->subtractScore(inputModel.get(),scoresService());
    inputModel->setTotalScore(candidateScore.totalScore);
    indexRedo()->redo(indexService(),scoresService());
    QScopedPointer turnValues(createTurnValues()->turnValues(indexService(),scoresService(),suggestFinishes()));
    auto jsonObject = createEmptyJsonObject()->emptyJsonObject();
    inputsToJson()->setJsonValues(jsonObject,inputModel.get(),inputKeys());
    turnValuesToJson()->setJsonValues(jsonObject, turnValues.get(),turnValKeys());
    emit scoreAddedSuccess(createByteArray()->byteArray(jsonObject));
}

void DartsController::updateTotalScore(const QByteArray &json)
{
    QScopedPointer inputModel(createInputModel()->createModel(json,inputKeys()));
    auto candidateScore = createCandidatesScore()->getCandidate(inputModel.get(),scoresService());
    scoresService()->scoreModels().replace(indexService()->setIndex(),candidateScore);
    inputModel->setTotalScore(candidateScore.totalScore);
    nextTurn();
    QScopedPointer turnValues(createTurnValues()->turnValues(indexService(),scoresService(),suggestFinishes()));
    auto jsonObject= createEmptyJsonObject()->emptyJsonObject();
    inputsToJson()->setJsonValues(jsonObject,inputModel.get(),inputKeys());
    turnValuesToJson()->setJsonValues(jsonObject,turnValues.get(),turnValKeys());
    emit scoreAddedSuccess(createByteArray()->byteArray(jsonObject));
}

void DartsController::nullifyAndPersistInput(DCContext::IDCInputModel *input)
{
    input->setScore(0);
    persistInput(input);
}

void DartsController::createAndSendWinnerValues()
{
    auto jsonObject = createEmptyJsonObject()->emptyJsonObject();
    jsonObject[inputKeys()->playerId()] = winnerService()->winnerId().toString(QUuid::WithoutBraces);
    jsonObject[inputKeys()->playerName()] = winnerService()->winnerName();
    jsonObject[inputKeys()->tournamentId()] = tournamentId()->id().toString(QUuid::WithoutBraces);
    emit winnerDeclared(createByteArray()->byteArray(jsonObject));
}

void DartsController::initializePlayerDetails(const QByteArray &json)
{
    auto dartsPlayerModels = createPlayersFromJson()->createModels(json,playerKeys(),playerBuilder());
    auto scoreModels = createScores()->createScoreModels(dartsPlayerModels,initialScore()->score());
    scoresService()->scoreModels().append(scoreModels);
    emit requestScores(tournamentId()->id());
}

void DartsController::initializeScores(const QByteArray &json)
{
    auto dartsScores = createInputModels()->createModels(json,inputKeys(),createInputModel());
    auto candidatesScoreModels = createCandidatesScore()->getScoreCandidates(dartsScores,scoresService());
    updateScoreModels()->update(candidatesScoreModels,scoresService());
    emit requestWinnerDetails(tournamentId()->id());
}

void DartsController::initializeWinnerDetails(const QByteArray &json)
{
    auto winnerModel = winnerModelFromJson()->toWinnerModel(json,winnerKeys(),playerBuilder());
    winnerService()->setWinner(winnerModel->playerId(),winnerModel->playerName());
    auto status = determineStatusById()->status(winnerModel->playerId(),statusCodes());
    metaStatus()->set(status);
    emit initialized(inputHint()->hint(),displayHint()->hint());
}

void DartsController::handleOrderedInputs(const QByteArray &json)
{
    auto modifiedJson = json;
    addTotalScoresToJson()->addTotalScoreToInputs(modifiedJson,initialScore()->score(),inputKeys());
    addPlayerNamesToJson()->addPlayerNamesToJson(modifiedJson,scoresService(),inputKeys());
    emit sendOrderedInputs(modifiedJson);
}
