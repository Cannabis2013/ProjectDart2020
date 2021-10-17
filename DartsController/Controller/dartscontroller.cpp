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
    auto input = inputBuilder()->buildInput(json);
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
    auto dartsScoreModels = inputBuilder()->buildInputs(scoresService());
    auto arr = createEmptyJsonObject()->emptyJsonArray();
    setJsonInputValues()->setValues(arr,dartsScoreModels);
    emit sendDartsScores(createByteArray()->byteArray(arr));
}

void DartsController::getOrderedInputsWithTotalScores()
{
    emit requestOrderedInputs(tournamentId()->id());
}

void DartsController::handleUserInputAdded(const QByteArray &json)
{
    QScopedPointer input(inputBuilder()->buildInput(json));
    updateTotalScore(input.get());
    auto average = calcInputAvg()->average(input.get(),indexService(),initialScore());
    indexIterator()->next(indexService(),scoresService());
    auto jsonResponse = assembleJsonResponse(input.get(),indexesBuilder()->buildIndexes(indexService()),average);
    emit sendCurrentIndexes(jsonResponse);
}

void DartsController::handleIndexesUpdated(const QByteArray &json)
{
    QScopedPointer input(inputBuilder()->buildInput(json));
    QScopedPointer turnValues(createTurnValues()->turnValues(indexService(),scoresService(),suggestFinishes()));
    auto jsonResponse = assembleJsonResponse(input.get(),turnValues.get());
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
    auto jsonResponse = assembleJsonResponse(indexesBuilder()->buildIndexes(indexService()));
    emit hideInput(jsonResponse);
}

void DartsController::redoTurn()
{
    auto jsonResponse = assembleJsonResponse(indexesBuilder()->buildIndexes(indexService()));
    emit revealInput(jsonResponse);
}

void DartsController::persistInput(IDCInput *inputModel)
{
    QScopedPointer indexes(indexesBuilder()->buildIndexes(indexService()));
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

void DartsController::declareWinner(IDCInput *input)
{
    winnerService()->setWinner(input->playerId(), input->playerName());
    controllerStatus()->set(statusCodes()->winnerFound());
    QScopedPointer indexes(indexesBuilder()->buildIndexes(indexService()));
    auto jsonResponse = assembleJsonResponse(input,indexes.get());
    emit requestAddDartsScore(jsonResponse);
}

QByteArray DartsController::assembleJsonResponse(IDCInput *input, const DCContext::DCTurnValues *turnValues)
{
    auto jsonObject= createEmptyJsonObject()->emptyJsonObject();
    setMetaJsonValues()->setValues(jsonObject,tournamentId(),playerService(),winnerService());
    setJsonInputValues()->setValues(jsonObject,input);
    turnValuesToJson()->setJsonValues(jsonObject,turnValues,turnValKeys());
    return createByteArray()->byteArray(jsonObject);
}

QByteArray DartsController::assembleJsonResponse(IDCInput *input, const DCContext::IDCIndexes *indexes, const int &average)
{
    auto jsonObject = createEmptyJsonObject()->emptyJsonObject();
    setMetaJsonValues()->setValues(jsonObject,tournamentId(),playerService(),winnerService());
    setJsonInputValues()->setValues(jsonObject,input);
    setIndexesJsonValues()->setValues(jsonObject,indexes,indexKeys());
    jsonObject["scoreAverage"] = average;
    return createByteArray()->byteArray(jsonObject);
}

QByteArray DartsController::assembleJsonResponse(IDCInput *input, const DCContext::IDCIndexes *indexes)
{
    auto jsonObject = createEmptyJsonObject()->emptyJsonObject();
    setMetaJsonValues()->setValues(jsonObject,tournamentId(),playerService(),winnerService());
    setJsonInputValues()->setValues(jsonObject,input);
    setIndexesJsonValues()->setValues(jsonObject,indexes,indexKeys());
    return createByteArray()->byteArray(jsonObject);
}

QByteArray DartsController::assembleJsonResponse(const DCContext::IDCIndexes *indexes)
{
    auto jsonObject = createEmptyJsonObject()->emptyJsonObject();
    setMetaJsonValues()->setValues(jsonObject,tournamentId(),playerService(),winnerService());
    setIndexesJsonValues()->setValues(jsonObject,indexes,indexKeys());
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
    auto indexes = indexesBuilder()->buildIndexes(json);
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
    QScopedPointer inputModel(inputBuilder()->buildInput(json));
    QScopedPointer turnValues(createTurnValues()->turnValues(indexService(),scoresService(),suggestFinishes()));
    auto scoreModel = addScoreService()->addPlayerScore(inputModel.get(), scoresService());
    inputModel->setTotalScore(scoreModel.totalScore);
    auto jsonObject = createEmptyJsonObject()->emptyJsonObject();
    setJsonInputValues()->setValues(jsonObject,inputModel.get());
    turnValuesToJson()->setJsonValues(jsonObject,turnValues.get(),turnValKeys());
    emit scoreRemoved(createByteArray()->byteArray(jsonObject));
}

void DartsController::redoSuccess(const QByteArray& json)
{
    QScopedPointer<IDCInput> inputModel(inputBuilder()->buildInput(json));
    auto candidateScore = subtractScore()->subtractScore(inputModel.get(),scoresService());
    inputModel->setTotalScore(candidateScore.totalScore);
    indexRedo()->redo(indexService(),scoresService());
    QScopedPointer turnValues(createTurnValues()->turnValues(indexService(),scoresService(),suggestFinishes()));
    auto jsonObject = createEmptyJsonObject()->emptyJsonObject();
    setJsonInputValues()->setValues(jsonObject,inputModel.get());
    turnValuesToJson()->setJsonValues(jsonObject, turnValues.get(),turnValKeys());
    emit scoreAddedSuccess(createByteArray()->byteArray(jsonObject));
}

void DartsController::updateTotalScore(IDCInput *input)
{
    auto candidateScore = createCandidatesScore()->getCandidate(input,scoresService());
    scoresService()->scoreModels().replace(indexService()->setIndex(),candidateScore);
    input->setTotalScore(candidateScore.totalScore);
}

void DartsController::nullifyAndPersistInput(IDCInput *input)
{
    input->setScore(0);
    persistInput(input);
}

void DartsController::createAndSendWinnerValues()
{
    auto jsonObject = createEmptyJsonObject()->emptyJsonObject();
    setMetaJsonValues()->setValues(jsonObject,tournamentId(),playerService(),winnerService());
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
    auto dartsScores = inputBuilder()->buildInputs(json);
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
    addTotalScoresToJson()->addTotalScoreToInputs(modifiedJson,initialScore()->score());
    addPlayerNamesToJson()->addPlayerNamesToJson(modifiedJson,scoresService());
    emit sendOrderedInputs(modifiedJson);
}
