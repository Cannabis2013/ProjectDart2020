#ifndef DPCONTROLLER_H
#define DPCONTROLLER_H
#include "idcmetainfo.h"
#include "getscorefromdpcinput.h"
#include "dpcinputvalidator.h"
#include "CreateDPCTurnValues.h"
#include "dpccreateinputmodels.h"
#include "dcindexesbuilder.h"
#include "dartscontrollerpointmodelsservice.h"
#include "addtotalscoretodartspointsjson.h"
#include "addplayernamestodartspointsjson.h"
#include "jsonmerger.h"
#include "genericjsonbuilder.h"
#include "dartsmetadataservice.h"
#include "dcinputsuggestions.h"
#include "determinecontrollerstatebywinnerid.h"
#include "dcscoresservice.h"
#include "dccreatecandidatetuples.h"
#include "dcinitializeindexservice.h"
#include <dcwinnerservice.h>
#include <dartscontroller.h>
#include <dpcinputvalidator.h>
#include <dpcindexcontroller.h>
#include <dcplayerbuilder.h>
#include <dcaddscore.h>
#include <dccreatescoretuples.h>
#include <dcupdatescoremodels.h>
#include <dpcinputstojson.h>
#include <dcturnvaluestojson.h>
#include <dcgetscorecand.h>
#include <dcjsonresponsebuilder.h>
#include <dpcindexestojson.h>
#include <dcplayerservice.h>
#include <dcindexiterator.h>
#include <dcindexredo.h>
#include <dcwinnerkeys.h>
#include "jsonvaluesextractor.h"
#include "dcsubtractscore.h"
#include "dcresetindexes.h"
#include "dcindexundo.h"
#include "dcgetplayername.h"
#include "dcgetwinnermodelfromjson.h"
#include "dccreateplayersfromjson.h"
#include "dcplayerkeys.h"
#include "dcconstructrow.h"
#include "dclogisticdb.h"
#include "dcresetscoremodels.h"
class DPController : public DartsController
{
public:
    DPController(const DCBuilding::IDCMetaInfo *meta)
    {
        setInputEvaluator(DPCInputValidator::createInstance());
        setIndexService(new DPCIndexController);
        setResetIndexes(new DCResetIndexes);
        setInitializeIndexes(new DCInitializeIndexes);
        setTurnValuesBuilder(new CreateDPCTurnValues);
        setInputModelBuilder(new DPCCreateInputModels);
        setIndexesBuilder(new DCIndexesBuilder);
        setPlayerBuilderService(new DCPlayerBuilder);
        setGetScoreFromInput(new GetScoreFromDPCInput);
        setAddScoreService(new DCAddScore);
        setAddTotalScoresToJson(new AddTotalScoreToDartsPointsJson);
        setAddPlayerNamesToJson(new AddPlayerNamestoDartsPointsJson);
        setMetaData(new DCMetaInfo(meta));
        setScoreLogisticInterface(DCInputSuggestions::createInstance(DCConstructRow::createInstance(meta),
                                                                     DCLogisticDb::createInstance()));
        setDetermineControllerStateByWinnerId(new DetermineControllerStateByWinnerId);
        setGetTotalScoreService(new DCGetScoreCand);
        // Json services
        setInputsToJsonService(new DPCInputsToJson);
        setTurnValuesToJsonService(new DCTurnValuesToJson);
        setResponseBuilderService(new DCJsonResponseBuilder);
        setIndexesToJsonService(new DPCIndexesToJson);
        // Score tuple services
        setResetScoreModels(new DCResetScoreModels);
        setCreateScoreTuples(new DCCreateScoreTuples);
        setReplaceScoreModels(new DCUpdateScoreModels);
        setSubtractScore(new DCSubtractScore);
        //setCreateJsonFromPoint(new DPCPointToJson);
        setScoresService(new DCScoresService);
        setCreateCandidateTuples(new DCCreateCandidateTuples);
        setWinnerService(new DCWinnerService);
        setJsonExtractor(new JsonValuesExtractor);
        // Player services
        setPlayerService(new DCPlayerService(indexService(),scoresService()));
        setGetPlayerName(new DCGetPlayerName);
        setWinnerModelFromJson(new DCGetWInnerModelsFromJson);
        setCreatePlayersFromJson(new DCCreatePlayersFromJson);
        setWinnerKeys(new DCWinnerKeys);
        setPlayerKeys(new DCPlayerKeys);
        // Index services
        setIndexIterator(new DCIndexIterator);
        setUndoIndex(new DCIndexUndo);
        setRedoIndex(new DCIndexRedo);
    }
};
#endif // DEFAULTDARTSPOINTCONTROLLER_H
