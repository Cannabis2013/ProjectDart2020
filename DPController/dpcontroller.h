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
#include "dcinputfinishes.h"
#include "determinestatusbyid.h"
#include "dcscoresservice.h"
#include "dccreatecandidatetuples.h"
#include "dcinitializeindexservice.h"
#include <dcwinnerservice.h>
#include "DartsController/dartscontroller.h"
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
#include "dccreatefinishes.h"
#include "dclogisticdb.h"
#include "dcresetscoremodels.h"
#include "DartsController/dcmetastatus.h"
#include "DartsController/dartsstatuscodes.h"
class DPController : public DartsController
{
public:
    DPController(const DCBuilding::IDCMetaInfo *meta)
    {
        setInputEvaluator(DPCInputValidator::createInstance());
        setIndexService(new DPCIndexController);
        setTurnValuesBuilder(new CreateDPCTurnValues);
        setInputModelBuilder(new DPCCreateInputModels);
        setIndexesBuilder(new DCIndexesBuilder);
        setGetScoreFromInput(new GetScoreFromDPCInput);
        setAddScoreService(new DCAddScore);
        setAddTotalScoresToJson(new AddTotalScoreToDartsPointsJson);
        setAddPlayerNamesToJson(new AddPlayerNamestoDartsPointsJson);
        setMetaData(new DCMetaInfo(meta));
        setSuggestFinishes(DCInputFinishes::createInstance(DCCreateFinishes::createInstance(), DCLogisticDb::createInstance()));
        setDetermineStatusById(new DetermineStatusById);
        setGetTotalScoreService(new DCGetScoreCand);
        // Meta services
        setMetaStatus(new DCMetaStatus);
        setStatusCodes(new DCStatusCodes);
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
        setScoresService(new DCScoresService);
        setCreateCandidateTuples(new DCCreateCandidateTuples);
        setWinnerService(new DCWinnerService);
        setJsonExtractor(new JsonValuesExtractor);
        // Player services
        setPlayerBuilderService(new DCPlayerBuilder);
        setPlayerService(new DCPlayerService(indexService(),scoresService()));
        setGetPlayerName(new DCGetPlayerName);
        setWinnerModelFromJson(new DCGetWInnerModelsFromJson);
        setCreatePlayersFromJson(new DCCreatePlayersFromJson);
        setWinnerKeys(new DCWinnerKeys);
        setPlayerKeys(new DCPlayerKeys);
        // Index services
        setResetIndexes(new DCResetIndexes);
        setInitializeIndexes(new DCInitializeIndexes);
        setIndexIterator(new DCIndexIterator);
        setUndoIndex(new DCIndexUndo);
        setRedoIndex(new DCIndexRedo);
    }
};
#endif // DEFAULTDARTSPOINTCONTROLLER_H
