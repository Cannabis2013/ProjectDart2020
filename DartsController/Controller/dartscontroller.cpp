#include "dartscontroller.h"
using namespace DCContext;
void DartsController::start()
{
    controllerStatus()->set(statusCodes()->awaitsInput());
    sendCurrentTurnValues();
}

void DartsController::stop()
{
    emit controllerIsStopped();
}

void DartsController::handleUserInput(const QByteArray& json)
{
    auto input = createInputModel()->createModel(json,inputKeys());
    input->setPlayerId(playerService()->currentPlayerId());
    input->setPlayerName(playerService()->currentPlayerName());
    input->setScore(getScoreFromInput()->getScore(input));
    auto accumulatedScore = getTotalScore()->scoreCandidate(indexService()->setIndex(),input->score(),scoresService());
    inputEvaluator()->validateInput(accumulatedScore,inputKeyCodes(),input,playerAllowanceContext());
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
    inputJsonContext()->setJsonValues(arr,dartsScoreModels,inputKeys());
    emit sendDartsScores(createByteArray()->byteArray(arr));
}

void DartsController::getOrderedInputsWithTotalScores()
{
    emit requestOrderedInputs(tournamentId()->id());
}

void DartsController::handleUserInputAdded(const QByteArray &json)
{
    QScopedPointer input(createInputModel()->createModel(json,inputKeys()));
    updateTotalScore(input.get());
    indexIterator()->next(indexService(),scoresService());
    auto jsonResponse = assembleJsonResponse(input.get(),indexesBuilder()->createIndexes(indexService()));
    emit sendCurrentIndexes(jsonResponse);
}

void DartsController::handleIndexesUpdated(const QByteArray &json)
{
    QScopedPointer input(createInputModel()->createModel(json,inputKeys()));
    QScopedPointer turnValues(createTurnValues()->turnValues(indexService(),scoresService(),suggestFinishes()));
    auto average = calcInputAvg()->average(input.get(),indexService(),initialScore());
    auto jsonResponse = assembleJsonResponse(input.get(),turnValues.get(),average);
    emit scoreAddedSuccess(jsonResponse);
}

void DartsController::handleResetTournament()
{
    resetIndexes()->reset(indexService());
    resetScoreModels()->reset(scoresService(),initialScore()->score());
    controllerStatus()->set(statusCodes()->initialized());
    if(playerAllowanceContext() != nullptr)
        playerAllowanceContext()->reset();
    emit requestResetTournament(tournamentId()->id());
}

void DartsController::sendCurrentTurnValues()
{
    auto model = createTurnValues()->turnValues(indexService(),scoresService(),suggestFinishes());
    auto obj = createEmptyJsonObject()->emptyJsonObject();
    turnValuesToJson()->setJsonValues(obj,model,turnValKeys());
    emit awaitsInput(createByteArray()->byteArray(obj));
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
    QScopedPointer indexes(indexesBuilder()->createIndexes(indexService()));
    auto jsonResponse = assembleJsonResponse(inputModel,indexes.get());
    emit requestAddDartsScore(jsonResponse);
}

void DartsController::handleRequestFromUI()
{
    if(controllerStatus()->get() == statusCodes()->winnerFound())
        createAndSendWinnerValues();
    else if(controllerStatus()->get() == statusCodes()->awaitsInput())
        sendCurrentTurnValues();
    else
        emit controllerInitializedAndReady();
}

void DartsController::declareWinner(IDCInputModel *input)
{
    winnerService()->setWinner(input->playerId(), input->playerName());
    controllerStatus()->set(statusCodes()->winnerFound());
    QScopedPointer indexes(indexesBuilder()->createIndexes(indexService()));
    auto jsonResponse = assembleJsonResponse(input,indexes.get());
    emit requestAddDartsScore(jsonResponse);
}

QByteArray DartsController::assembleJsonResponse(DCContext::IDCInputModel *input,
                                                 const DCContext::DCTurnValues *turnValues,
                                                 const int &average)
{
    auto jsonObject= createEmptyJsonObject()->emptyJsonObject();
    inputJsonContext()->setJsonValues(jsonObject,input,inputKeys());
    jsonObject[inputAvgKeys()->average()] = average;
    turnValuesToJson()->setJsonValues(jsonObject,turnValues,turnValKeys());
    return createByteArray()->byteArray(jsonObject);
}

QByteArray DartsController::assembleJsonResponse(DCContext::IDCInputModel *input, const DCContext::IDCIndexes *indexes)
{
    auto jsonObject = createEmptyJsonObject()->emptyJsonObject();
    jsonObject[TOURNAMENT_ID_JSON_KEY] = tournamentId()->id().toString(QUuid::WithoutBraces);
    inputJsonContext()->setJsonValues(jsonObject,input,inputKeys());
    indexesToJson()->toJson(jsonObject,indexes,indexKeys());
    return createByteArray()->byteArray(jsonObject);
}

QByteArray DartsController::assembleJsonResponse(const DCContext::IDCIndexes *indexes)
{
    auto jsonObject = createEmptyJsonObject()->emptyJsonObject();
    jsonObject[TOURNAMENT_ID_JSON_KEY] = tournamentId()->id().toString(QUuid::WithoutBraces);
    indexesToJson()->toJson(jsonObject,indexes,indexKeys());
    return createByteArray()->byteArray(jsonObject);
}

void DartsController::connectInputEvaluator()
{
    if(inputEvaluator() == nullptr)
        throw "InputEvaluator service is null";
    connect(inputEvaluator(),&AbstractEvaluateDCInput::playerHitPointDomain,
            this,&DartsController::persistInput);
    connect(inputEvaluator(),&AbstractEvaluateDCInput::playerHitTargetDomain,
            this,&DartsController::declareWinner);
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
    inputJsonContext()->setJsonValues(jsonObject,inputModel.get(),inputKeys());
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
    inputJsonContext()->setJsonValues(jsonObject,inputModel.get(),inputKeys());
    turnValuesToJson()->setJsonValues(jsonObject, turnValues.get(),turnValKeys());
    emit scoreAddedSuccess(createByteArray()->byteArray(jsonObject));
}

void DartsController::updateTotalScore(IDCInputModel *input)
{
    auto candidateScore = createCandidatesScore()->getCandidate(input,scoresService());
    scoresService()->scoreModels().replace(indexService()->setIndex(),candidateScore);
    input->setTotalScore(candidateScore.totalScore);
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
    jsonObject[TOURNAMENT_ID_JSON_KEY] = tournamentId()->id().toString(QUuid::WithoutBraces);
    emit winnerDeclared(createByteArray()->byteArray(jsonObject));
}

void DartsController::initializePlayerDetails(const QByteArray &json)
{
    auto dartsPlayerModels = createPlayersFromJson()->createModels(json,playerKeys(),playerBuilder());
    auto scoreModels = createScores()->createScoreModels(dartsPlayerModels,initialScore()->score());
    if(playerAllowanceContext() != nullptr)
        playerAllowanceContext()->appendPlayerId(dartsPlayerModels);
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
    auto winnerModel = winnerModelFromJson()->toWinnerModel(json,playerKeys(),playerBuilder());
    winnerService()->setWinner(winnerModel->playerId(),winnerModel->playerName());
    auto status = determineStatusById()->status(winnerModel->playerId(),statusCodes());
    controllerStatus()->set(status);
    emit initialized(inputHint()->hint(),displayHint()->hint());
}

void DartsController::handleOrderedInputs(const QByteArray &json)
{
    auto modifiedJson = json;
    addTotalScoresToJson()->addTotalScoreToInputs(modifiedJson,initialScore()->score(),inputKeys());
    addPlayerNamesToJson()->addPlayerNamesToJson(modifiedJson,scoresService(),inputKeys());
    emit sendOrderedInputs(modifiedJson);
}
