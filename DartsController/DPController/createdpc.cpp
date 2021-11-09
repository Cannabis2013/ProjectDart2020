#include "createdpc.h"
AbstractDartsController *CreateDPC::create(const DCBMeta &meta)
{
    auto dc = new DartsController;
    dc->setStatusCodes(new DCStatusCodes);
    dc->setMetaInfo(new DCMetaInfo(meta.tournamentId,meta.initialRemainingScore,meta.inputHint));
    dc->setMetaBuilder(new DCMetaModelBuilder);
    dc->setScoreBuilder(new DCCreateScoreModels);
    dc->setScoresModels(new DCScoreModels);
    dc->setCreateCandidateScores(new DCUpdateInputDetails);
    dc->setJsonResponseBuilder(createJsonBuilder());
    dc->setPlayerStatsManager(new DCPlayerStatsManager);
    dc->setUpdateMiddleVal(new DPCCalcMidVal);
    dc->setUpdateScoreRange(new DCUpdateScoreRange);
    dc->setUpdatePlayerStats(new DCUpdatePlayerStat);
    dc->setSuggestFinishes(DCInputFinishes::createInstance(DCCreateFinishes::createInstance(),
                                                       DCLogisticDb::createInstance()));
    dc->setPlayerController(new DPCPlayerController);
    dc->setPlayerBuilderService(new DCPlayerBuilder);
    dc->setInputBuilder(new DPCInputBuilder);
    dc->setInputEvaluator(DPCInputEvaluator::createInstance());
    dc->setGetScoreFromInput(new GetScoreFromDPCInput);
    dc->setIndexService(new DPCIndexController);
    dc->setIndexBuilder(new DCInputIndexBuilder);
    dc->setReqIndexBuilder(new DPCReqIndexBuilder);
    dc->setTurnValuesBuilder(new DPCTurnValuesBuilder);
    dc->setJsonResponseBuilder(createJsonBuilder());
    return dc;
}

AbstractDCJsonBuilder *CreateDPC::createJsonBuilder()
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
