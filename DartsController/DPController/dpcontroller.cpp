#include "dpcontroller.h"
DPController::DPController(const DCBuilding::IDCMetaInfo *meta):
    _metaInfo(meta)
{
    setMetaServices();
    setScoresServices();
    setJsonServices();
    setPlayerServices();
    setInputServices();
    setIndexServices();
    setStatisticsServices();
    setFinishesServices();
    setTurnValuesServices();
}
void DPController::setMetaServices()
{
    setDetermineStatusById(new DetermineStatusById);
    setControllerStatus(new DCMetaStatus);
    setStatusCodes(new DCStatusCodes);
    setDisplayHint(DCHint::createInstance(_metaInfo->displayHint()));
    setInputHint(DCHint::createInstance(_metaInfo->inputHint()));
    setTournamentId(DCTournamentId::createInstance(_metaInfo->tournamentId()));
    setInitialScore(DCInitialScore::createInstance(_metaInfo->keyPoint()));
    setSetMetaJsonValues(new DCMetaJsonBuilder);
}
void DPController::setScoresServices()
{
    setGetTotalScoreService(new DCGetScoreCand);
    setResetScoreModels(new DCResetScoreModels);
    setCreateScoreModelsService(new DCCreateScoreModels);
    setUpdateScoreModels(new DCUpdateScoreModels);
    setSubtractScore(new DCSubtractScore);
    setScoresService(new DCScoresService);
    setCreateCandidateTuples(new DCCreateCandidateModels);
    setWinnerService(new DCWinnerService);
    setAddScoreService(new DCAddScore);
}
void DPController::setJsonServices()
{
    setInputJsonContext(new DPCInputsToJson);
    setTurnValuesToJsonService(new DCTurnValuesToJson);
    setIndexesToJsonService(new DPCIndexesToJson);
    setCreateByteArray(new DCCreateByteArray);
    setCreateEmptyJsonObject(new DCCreateEmptyJsonObject);
    setAddTotalScoresToJson(new AddTotalScoreToDartsInputsAsJson);
}
void DPController::setStatisticsServices()
{
    setCalcInputAvg(new DCAverageCalc);
}
void DPController::setFinishesServices()
{
    setSuggestFinishes(DCInputFinishes::createInstance(DCCreateFinishes::createInstance(),
                                                       DCLogisticDb::createInstance()));
}
void DPController::setPlayerServices()
{
    setPlayerAllowanceContext(new DPCPlayerAllowancesContext);
    setAddPlayerNamesToJson(new AddPlayerNamestoDartsInputsAsJson);
    setPlayerBuilderService(new DCPlayerBuilder);
    setPlayerService(new DCPlayerService(indexService(),scoresService()));
    setWinnerModelFromJson(new DCGetWInnerModelsFromJson);
    setCreatePlayersFromJson(new DCCreatePlayersFromJson);
    setWinnerKeys(new DCWinnerKeys);
    setPlayerKeys(new DCPlayerKeys);
}
void DPController::setInputServices()
{
    setInputBuilder(new DPCInputBuilder);
    setInputKeyCodes(new DCInputKeyCodes);
    setInputEvaluator(DPCInputValidator::createInstance());
    setGetScoreFromInput(new GetScoreFromDPCInput);
}
void DPController::setIndexServices()
{
    setIndexService(new DPCIndexController);
    setResetIndexes(new DCResetIndexes);
    setInitializeIndexes(new DCInitializeIndexes);
    setIndexIterator(new DCIndexIterator);
    setUndoIndex(new DCIndexUndo);
    setRedoIndex(new DCIndexRedo);
    setIndexKeys(new DCIndexesJsonKeys);
    setIndexesBuilder(new DCIndexesBuilder);
}
void DPController::setTurnValuesServices()
{
    setTurnValKeys(new DCTurnValJsonKeys);
    setTurnValuesBuilder(new CreateDPCTurnValues);
}
