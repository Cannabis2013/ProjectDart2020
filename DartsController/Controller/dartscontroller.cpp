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
    auto domain = inputEvaluator()->validateInput(accumulatedScore,inputKeyCodes(),input->modKeyCode(),input->point());
    processDomain(domain,input);
}

void DartsController::handleRequestForCurrentTournamentMetaData()
{
    auto tournament = tournamentId()->id();
    emit sendCurrentTournamentId(tournament);
}

void DartsController::createDartsScores()
{
    auto dartsScoreModels = createInputModels()->createModels(scoresService(),createInputModel());
    auto obj = inputsToJson()->createJson(dartsScoreModels,inputKeys());
    emit sendDartsScores(createByteArray()->byteArray(obj));
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
    emit awaitsInput(createByteArray()->byteArray(turnValuesToJson()->create(model)));
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

void DartsController::addInput(DCContext::IDCInputModel *inputModel)
{
    auto indexes = indexesBuilder()->createIndexes(indexService());
    auto jsonResponse = createEmptyJsonObject()->jsonObject();
    jsonResponse[responseKeys()->inputKey()] = inputsToJson()->createJson(inputModel,inputKeys());
    jsonResponse[responseKeys()->indexesKey()] = indexesToJson()->toJson(indexes);
    emit requestAddDartsScore(createByteArray()->byteArray(jsonResponse));
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

void DartsController::declareWinner()
{
    auto currentPlayerId = playerService()->currentPlayerId();
    auto currentPlayerName = playerService()->currentPlayerName();
    winnerService()->setWinner(currentPlayerId, currentPlayerName);
    metaStatus()->set(statusCodes()->winnerFound());
}

void DartsController::initializeControllerIndexes(const QByteArray& json)
{
    auto indexes = indexesBuilder()->createIndexes(json);
    initializeIndexes()->initialize(indexes,indexService());
    emit requestTournamentAssignedPlayerDetails(tournamentId()->id());
}

void DartsController::processDomain(const int &domain, DCContext::IDCInputModel *inputModel)
{
    switch (domain)
    {
        case InputOutOfRange : sendCurrentTurnValues();break;
        case PointDomain : addInput(inputModel);break;
        case CriticalDomain : addInput(inputModel);break;
        case TargetDomain : {
            declareWinner();
            addInput(inputModel);
            break;
        }
        case OutsideDomain : {
            inputModel->setScore(0);
            addInput(inputModel);
            break;
        }
    }
}

void DartsController::beginInitialize()
{
    emit requestDartsTournamentIndexes(tournamentId()->id());
}

void DartsController::undoSuccess(const QByteArray& json)
{
    QScopedPointer inputModel(createInputModel()->createModel(json,inputKeys()));
    QScopedPointer turnValues(createTurnValues()->turnValues(indexService(),scoresService(),suggestFinishes()));
    auto scoreModel = addScoreService()->addPlayerScore(inputModel.get(), scoresService());
    inputModel->setPlayerName(getPlayerName()->playerName(inputModel->playerId(),scoresService()));
    inputModel->setTotalScore(scoreModel.totalScore);
    auto jsonResponse = createEmptyJsonObject()->jsonObject();
    jsonResponse[responseKeys()->inputKey()] = inputsToJson()->createJson(inputModel.get(),inputKeys());
    jsonResponse[responseKeys()->turnValuesKey()] = turnValuesToJson()->create(turnValues.get());
    emit scoreRemoved(createByteArray()->byteArray(jsonResponse));
}

void DartsController::redoSuccess(const QByteArray& json)
{
    QScopedPointer<DCContext::IDCInputModel> inputModel(createInputModel()->createModel(json,inputKeys()));
    inputModel->setPlayerName(getPlayerName()->playerName(inputModel->playerId(),scoresService()));
    auto candidateScore= subtractScore()->subtractScore(inputModel.get(),scoresService());
    inputModel->setTotalScore(candidateScore.totalScore);
    indexRedo()->redo(indexService(),scoresService());
    QScopedPointer turnValues(createTurnValues()->turnValues(indexService(),scoresService(),suggestFinishes()));
    auto jsonResponspe = createEmptyJsonObject()->jsonObject();
    jsonResponspe[responseKeys()->inputKey()] = inputsToJson()->createJson(inputModel.get(),inputKeys());
    jsonResponspe[responseKeys()->turnValuesKey()] = turnValuesToJson()->create(turnValues.get());
    emit scoreAddedSuccess(createByteArray()->byteArray(jsonResponspe));
}

void DartsController::updateTotalScore(const QByteArray &json)
{
    QScopedPointer inputModel(createInputModel()->createModel(json,inputKeys()));
    auto candidateScore = createCandidatesScore()->getCandidate(inputModel.get(),scoresService());
    scoresService()->scoreModels().replace(indexService()->setIndex(),candidateScore);
    inputModel->setTotalScore(candidateScore.totalScore);
    nextTurn();
    QScopedPointer turnValues(createTurnValues()->turnValues(indexService(),scoresService(),suggestFinishes()));
    auto jsonResponspe = createEmptyJsonObject()->jsonObject();
    jsonResponspe[responseKeys()->inputKey()] = inputsToJson()->createJson(inputModel.get(),inputKeys());
    jsonResponspe[responseKeys()->turnValuesKey()] = turnValuesToJson()->create(turnValues.get());
    emit scoreAddedSuccess(createByteArray()->byteArray(jsonResponspe));
}

void DartsController::createAndSendWinnerValues()
{
    auto jsonObject = createEmptyJsonObject()->jsonObject();
    jsonObject["winnerName"] = winnerService()->winnerName();
    jsonObject["winnerId"] = winnerService()->winnerId().toString(QUuid::WithoutBraces);
    jsonObject["tournamentId"] = tournamentId()->id().toString(QUuid::WithoutBraces);
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
