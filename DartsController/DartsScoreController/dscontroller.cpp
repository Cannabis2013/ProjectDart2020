#include "dscontroller.h"
DSController::DSController(const DCBuilding::DCMeta &meta)
{
    setWinnerService(new DCWinnerService());
    setTurnValuesBuilder(new DSCValuesBuilder);
    setSuggestFinishes(DCInputFinishes::createInstance(DCCreateFinishes::createInstance(),
                                                       DCLogisticDb::createInstance()));
    // Index services
    setInitializeIndexes(new DCInitializeIndexes);
    setIndexIterator(new DCIndexIterator);
    setResetIndexes(new DCResetIndexes);
    setUndoIndex(new DCIndexUndo);
    setRedoIndex(new DCIndexRedo);
    setIndexKeys(new DCIndexesJsonKeys);
    setIndexService(new DSCIndexController);
    setIndexesBuilder(new DCIndexesBuilder);
    // Scores services
    setCreateCandidateScores(new DCCreateCandidateModels);
    setGetTotalScoreService(new DCGetScoreCand);
    setScoresService(new DCScoresService);
    setScoreBuilder(new DCCreateScoreModels);
    setAddScoreService(new DCAddScore);
    // Meta services
    setDetermineStatusById(new DetermineStatusById);
    setControllerStatus(new DCMetaStatus);
    setStatusCodes(new DCStatusCodes);
    setDisplayHint(DCHint::createInstance(meta.displayHint));
    setInputHint(DCHint::createInstance(meta.inputHint));
    setTournamentId(DCTournamentId::createInstance(meta.tournamentId));
    setInitialScore(DCInitialScore::createInstance(meta.keyPoint));
    setSetMetaJsonValues(new DCMetaJsonBuilder);
    setMetaBuilder(new DCMetaModelBuilder(indexService(),scoresService()));
    // Json services
    setJsonResponseBuilder(createJsonBuilder());
    // Input services
    setGetScoreFromInput(new GetScoreFromDSCInput);
    setInputEvaluator(DSCInputValidator::createInstance());
    setInputBuilder(new DSCInputBuilder);
    // Input statistics services
    setStatsBuilder(new DSCStatsBuilder);
    // Player score services
    setPlayerBuilderService(new DCPlayerBuilder);
    setSubtractScore(new DCSubtractScore);
    setUpdateScoreModels(new DCUpdateScoreModels);
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
    builder->setIndexesJsonBuilder(new DCIndexesJsonBuilder);
    builder->setInputStatJsonBuilder(new DCStatsJsonBuilder);
    builder->setMetaJsonBuilder(new DCMetaInfoJsonBuilder);
    builder->setTurnValuesJsonBuilder(new DCTurnValuesJsonBuilder);
    return builder;
}
