#include "createdsc.h"
AbstractDCJsonBuilder *CreateDSC::createJsonBuilder()
{
    auto builder = new DCJsonBuilder;
    builder->setInputJsonBuilder(new DCInputJsonBuilder);
    builder->setScoreModelJsonBuilder(new DCScoreJsonBuilder);
    builder->setIndexesJsonBuilder(new DCIndexJsonBuilder);
    builder->setReqIndexJsonBuilder(new DCReqIndexJsonBuilder);
    builder->setMetaJsonBuilder(new DCMetaInfoJsonBuilder);
    builder->setPlayerStatsJsonBuilder(new DCPlayerStatsJsonBuilder);
    builder->setTurnValuesJsonBuilder(new DCTurnValuesJsonBuilder);
    return builder;
}

AbstractDartsController *CreateDSC::create(const DCBMeta &meta)
{
    auto dc = new DartsController;
    dc->setTurnValuesBuilder(new DSCValuesBuilder);
    dc->setSuggestFinishes(DCInputFinishes::createInstance(DCCreateFinishes::createInstance(),DCLogisticDb::createInstance()));
    dc->setIndexService(new DSCIndexController);
    dc->setIndexBuilder(new DCInputIndexBuilder);
    dc->setReqIndexBuilder(new DSCReqIndexBuilder);
    dc->setCreateCandidateScores(new DCUpdateInputDetails);
    dc->setScoresModels(new DCScoreModels);
    dc->setScoreBuilder(new DCCreateScoreModels);
    dc->setStatusCodes(new DCStatusCodes);
    dc->setMetaInfo(new DCMetaInfo(meta.tournamentId,meta.initialRemainingScore,meta.inputHint));
    dc->setMetaBuilder(new DCMetaModelBuilder);
    dc->setJsonResponseBuilder(createJsonBuilder());
    dc->setGetScoreFromInput(new GetScoreFromDSCInput);
    dc->setInputEvaluator(DSCInputEvaluator::createInstance());
    dc->setInputBuilder(new DSCInputBuilder);
    dc->setPlayerStatsManager(new DCPlayerStatsManager);
    dc->setUpdateMiddleVal(new DSCCalcMidVal);
    dc->setUpdateScoreRange(new DCUpdateScoreRange);
    dc->setUpdatePlayerStats(new DCUpdatePlayerStat);
    dc->setPlayerController(new DSCPlayerController);
    dc->setPlayerBuilderService(new DCPlayerBuilder);
    dc->setJsonResponseBuilder(createJsonBuilder());
    return dc;
}
