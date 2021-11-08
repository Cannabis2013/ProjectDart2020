#include "dpcontroller.h"
DPController::DPController(const DCBMeta &meta):
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
    setStatusCodes(new DCStatusCodes);
    setMetaInfo(new DCMetaInfo(_metaInfo.tournamentId,_metaInfo.keyPoint,_metaInfo.inputHint));
    setMetaBuilder(new DCMetaModelBuilder);
}
void DPController::setScoresServices()
{
    setScoreBuilder(new DCCreateScoreModels);
    setScoresModels(new DCScoreModels);
    setCreateCandidateScores(new DCUpdateInputDetails);
}
void DPController::setJsonServices()
{
    setJsonResponseBuilder(createJsonBuilder());
}
void DPController::setStatisticsServices()
{
    setPlayerStatsManager(new DCPlayerStatsManager);
    setUpdateMiddleVal(new DPCCalcMidVal);
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
