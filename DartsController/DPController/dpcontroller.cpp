#include "dpcontroller.h"

DPController::DPController(const DCBuilding::DCMeta &meta):
    _metaInfo(meta)
{
    setIndexServices();
    setScoresServices();
    setMetaServices();
    setJsonServices();
    setPlayerServices();
    setInputServices();
    setStatisticsServices();
    setFinishesServices();
    setTurnValuesServices();
}
void DPController::setMetaServices()
{
    setDetermineStatusById(new DetermineStatusById);
    setControllerStatus(new DCMetaStatus);
    setStatusCodes(new DCStatusCodes);
    setDisplayHint(DCHint::createInstance(_metaInfo.displayHint));
    setInputHint(DCHint::createInstance(_metaInfo.inputHint));
    setTournamentId(DCTournamentId::createInstance(_metaInfo.tournamentId));
    setInitialScore(DCInitialScore::createInstance(_metaInfo.keyPoint));
    setSetMetaJsonValues(new DCMetaJsonBuilder);
    setMetaBuilder(new DCMetaModelBuilder(indexService(),scoresService()));
}
void DPController::setScoresServices()
{
    setGetTotalScoreService(new DCGetScoreCand);
    setResetScoreModels(new DCResetScoreModels);
    setScoreBuilder(new DCCreateScoreModels);
    setUpdateScoreModels(new DCUpdateScoreModels);
    setSubtractScore(new DCSubtractScore);
    setScoresService(new DCScoresService);
    setCreateCandidateScores(new DCCreateCandidateModels);
    setWinnerService(new DCWinnerService);
    setAddScoreService(new DCAddScore);
}
void DPController::setJsonServices()
{
    setAddTotalScoresToJson(new AddTotalScoreToDartsInputsAsJson);
    setJsonResponseBuilder(createJsonBuilder());
}
void DPController::setStatisticsServices()
{
    setStatsBuilder(new DPCStatsBuilder);
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
    setPlayerService(new DCPlayerService);
    setWinnerModelFromJson(new DCGetWInnerModelsFromJson);
    setWinnerKeys(new DCWinnerKeys);
    setPlayerKeys(new DCPlayerKeys);
}
void DPController::setInputServices()
{
    setInputBuilder(new DPCInputBuilder);
    setInputEvaluator(DPCInputEvaluator::createInstance());
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
    setTurnValuesBuilder(new CreateDPCTurnValues);
}
AbstractDCJsonBuilder *DPController::createJsonBuilder()
{
    auto builder = new DCJsonBuilder;
    builder->setInputJsonBuilder(new DCInputJsonBuilder);
    builder->setInputStatJsonBuilder(new DCStatsJsonBuilder);
    builder->setIndexesJsonBuilder(new DCIndexesJsonBuilder);
    builder->setMetaJsonBuilder(new DCMetaInfoJsonBuilder);
    builder->setTurnValuesJsonBuilder(new DCTurnValuesJsonBuilder);
    return builder;
}
