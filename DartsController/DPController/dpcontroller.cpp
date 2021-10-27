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
    setMetaBuilder(new DCMetaModelBuilder);
}
void DPController::setScoresServices()
{
    setGetTotalScoreService(new DCGetScoreCand);
    setScoreBuilder(new DCCreateScoreModels);
    setUpdateScoresService(new DCUpdateScoreModels);
    setScoresModels(new DCScoreModels);
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
    setPlayerStatsManager(new DCPlayerStatsManager);
    setUpdateMiddleVal(new DPCUpdateMidVal);
    setUpdateScoreRange(new DCUpdateScoreRange);
    setUpdatePlayerStats(new DCUpdatePlayerStat);
}
void DPController::setFinishesServices()
{
    setSuggestFinishes(DCInputFinishes::createInstance(DCCreateFinishes::createInstance(),
                                                       DCLogisticDb::createInstance()));
}
void DPController::setPlayerServices()
{
    setPlayerController(new DPCPlayerController);
    setAddPlayerNamesToJson(new AddPlayerNamestoDartsInputsAsJson);
    setPlayerBuilderService(new DCPlayerBuilder);
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
    setIndexKeys(new DCIndexesJsonKeys);
    setIndexBuilder(new DCInputIndexBuilder);
    setReqIndexBuilder(new DPCReqIndexBuilder);
}
void DPController::setTurnValuesServices()
{
    setTurnValuesBuilder(new DPCTurnValuesBuilder);
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
    builder->setReqIndexJsonBuilder(new DCReqIndexJsonBuilder);
    return builder;
}
