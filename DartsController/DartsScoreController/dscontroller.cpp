#include "dscontroller.h"
DSController::DSController(const DCBMeta &meta)
{
    setTurnValuesBuilder(new DSCValuesBuilder);
    setSuggestFinishes(DCInputFinishes::createInstance(DCCreateFinishes::createInstance(),
                                                       DCLogisticDb::createInstance()));
    // Index services
    setIndexService(new DSCIndexController);
    setIndexBuilder(new DCInputIndexBuilder);
    setReqIndexBuilder(new DSCReqIndexBuilder);
    // Scores services
    setCreateCandidateScores(new DCUpdateInputDetails);
    setScoresModels(new DCScoreModels);
    setScoreBuilder(new DCCreateScoreModels);
    // Meta services
    setStatusCodes(new DCStatusCodes);
    setMetaInfo(new DCMetaInfo(meta.tournamentId,meta.keyPoint,meta.inputHint));
    setMetaBuilder(new DCMetaModelBuilder);
    // Json services
    setJsonResponseBuilder(createJsonBuilder());
    // Input services
    setGetScoreFromInput(new GetScoreFromDSCInput);
    setInputEvaluator(DSCInputEvaluator::createInstance());
    setInputBuilder(new DSCInputBuilder);
    // Input statistics services
    setPlayerStatsManager(new DCPlayerStatsManager);
    setUpdateMiddleVal(new DSCCalcMidVal);
    setUpdateScoreRange(new DCUpdateScoreRange);
    setUpdatePlayerStats(new DCUpdatePlayerStat);
    // Player services
    setPlayerController(new DSCPlayerController);
    // Player scores services
    setPlayerBuilderService(new DCPlayerBuilder);
}
AbstractDCJsonBuilder *DSController::createJsonBuilder()
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
