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
    setMetaBuilder(new DCMetaModelBuilder(indexController(),scoreController()));
}
void DPController::setScoresServices()
{
    setGetTotalScoreService(new DCGetScoreCand);
    setResetScoreModels(new DCResetScoreModels);
    setScoreBuilder(new DCCreateScoreModels);
    setUpdateScoreModels(new DCUpdateScoreModels);
    setScoresService(new DCScoresService);
    setCreateCandidateScores(new DCUpdateInputDetails);
    setWinnerService(new DCWinnerService);
}
void DPController::setJsonServices()
{
    setAddTotalScoresToJson(new AddTotalScoreToDartsInputsAsJson);
    setJsonResponseBuilder(createJsonBuilder());
}
void DPController::setStatisticsServices()
{
    setStatsBuilder(new DPCScoreStats);
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
    setIndexesBuilder(new DCInputIndexBuilder);
    setReqIndexBuilder(new DPCReqIndexBuilder);
}
void DPController::setTurnValuesServices()
{
    setTurnValuesBuilder(new CreateDPCTurnValues);
}
AbstractDCJsonBuilder *DPController::createJsonBuilder()
{
    auto builder = new DCJsonBuilder;
    builder->setInputJsonBuilder(new DCInputJsonBuilder);
    builder->setIndexesJsonBuilder(new DCIndexJsonBuilder);
    builder->setMetaJsonBuilder(new DCMetaInfoJsonBuilder);
    builder->setTurnValuesJsonBuilder(new DCTurnValuesJsonBuilder);
    builder->setScoreModelJsonBuilder(new DCScoreJsonBuilder);
    builder->setPlayerStatsJsonBuilder(new DCPlayerStatsJsonBuilder);
    return builder;
}
