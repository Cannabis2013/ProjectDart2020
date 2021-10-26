#include "dscontroller.h"
DSController::DSController(const DCBuilding::DCMeta &meta)
{
    setWinnerService(new DCWinnerService());
    setTurnValuesBuilder(new DSCValuesBuilder);
    setSuggestFinishes(DCInputFinishes::createInstance(DCCreateFinishes::createInstance(),
                                                       DCLogisticDb::createInstance()));
    // Index services
    setIndexKeys(new DCIndexesJsonKeys);
    setIndexService(new DSCIndexController);
    setIndexesBuilder(new DCInputIndexBuilder);
    setReqIndexBuilder(new DSCReqIndexBuilder);
    // Scores services
    setCreateCandidateScores(new DCUpdateInputDetails);
    setGetTotalScoreService(new DCGetScoreCand);
    setScoresModels(new DCScoresService);
    setScoreBuilder(new DCCreateScoreModels);
    // Meta services
    setDetermineStatusById(new DetermineStatusById);
    setControllerStatus(new DCMetaStatus);
    setStatusCodes(new DCStatusCodes);
    setDisplayHint(DCHint::createInstance(meta.displayHint));
    setInputHint(DCHint::createInstance(meta.inputHint));
    setTournamentId(DCTournamentId::createInstance(meta.tournamentId));
    setInitialScore(DCInitialScore::createInstance(meta.keyPoint));
    setSetMetaJsonValues(new DCMetaJsonBuilder);
    setMetaBuilder(new DCMetaModelBuilder);
    // Json services
    setJsonResponseBuilder(createJsonBuilder());
    // Input services
    setGetScoreFromInput(new GetScoreFromDSCInput);
    setInputEvaluator(DSCInputEvaluator::createInstance());
    setInputBuilder(new DSCInputBuilder);
    // Input statistics services
    setPlayerStatsManager(new DCPlayerStatsManager);
    setUpdateMiddleVal(new DSCUpdateMidVal);
    setUpdateScoreRange(new DCUpdateScoreRange);
    setUpdatePlayerStats(new DCUpdatePlayerStat);
    // Player score services
    setPlayerBuilderService(new DCPlayerBuilder);
    setUpdateScoresService(new DCUpdateScoreModels);
    setResetScoreModels(new DCResetScoreModels);
    // Player services
    setPlayerService(new DCPlayerService);
    setWinnerModelFromJson(new DCGetWInnerModelsFromJson);
    setWinnerKeys(new DCWinnerKeys);
    setPlayerKeys(new DCPlayerKeys);
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
