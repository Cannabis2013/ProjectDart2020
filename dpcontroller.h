#ifndef DPCONTROLLER_H
#define DPCONTROLLER_H

#include "idcmetainfo.h"
#include "getscorefromdpcinput.h"
#include "pointvalidator.h"
#include "CreateDPCTurnValues.h"
#include "dpccreateinputmodels.h"
#include "dcindexesbuilder.h"
#include "dartsplayermodelbuilderservice.h"
#include "dartscontrollerpointmodelsservice.h"
#include "addtotalscoretodartspointsjson.h"
#include "addplayernamestodartspointsjson.h"
#include "jsonmerger.h"
#include "genericjsonbuilder.h"
#include "dartsmetadataservice.h"
#include "dartspointstringsuggestion.h"
#include "determinecontrollerstatebywinnerid.h"
#include "dpcpointtojson.h"
#include "dcscoresservice.h"
#include "dccreatecandidatetuples.h"
#include "dcinitializeindexservice.h"
#include <dcwinnerservice.h>
#include <dartscontroller.h>
#include <pointvalidator.h>
#include <dcindexcontroller.h>
#include <dcplayerbuilder.h>
#include <dcaddscore.h>
#include <dccreatescoretuples.h>
#include <dcupdatetuples.h>
#include <dpcinputstojson.h>
#include <dcturnvaluestojson.h>
#include <dcgetscorecand.h>
#include <dcjsonresponsebuilder.h>
#include <dpcindexestojson.h>
#include <dcplayerservice.h>
#include <dcindexiterator.h>
#include <dcindexredo.h>
#include "jsonvaluesextractor.h"
#include "dcsubtractscore.h"
#include "dcresetindexes.h"
#include "dcindexundo.h"
#include "dcgetplayername.h"
class DPController : public DartsController
{
public:
    DPController(const DartsBuilderContext::IDCMetaInfo *meta)
    {
        setInputEvaluator(PointValidator::createInstance(meta->terminalKeyCode()));
        setIndexService(new DCIndexController(meta->attempts()));
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
        setScoreLogisticInterface(DartsPointStringSuggestion::createInstance(meta->attempts()));
        setDetermineControllerStateByWinnerId(new DetermineControllerStateByWinnerId);
        setGetTotalScoreService(new DCGetScoreCand);
        // Json services
        setInputsToJsonService(new DPCInputsToJson);
        setTurnValuesToJsonService(new DCTurnValuesToJson);
        setResponseBuilderService(new DCJsonResponseBuilder);
        setIndexesToJsonService(new DPCIndexesToJson);
        // Score tuple services
        setCreateScoreTuples(new DCCreateScoreTuples);
        setReplaceTuples(new DCUpdateTuples);
        setSubtractScore(new DCSubtractScore);
        //setCreateJsonFromPoint(new DPCPointToJson);
        setScoresService(new DCScoresService);
        setCreateCandidateTuples(new DCCreateCandidateTuples);
        setWinnerService(new DCWinnerService);
        setJsonExtractor(new JsonValuesExtractor);
        // Player services
        setPlayerService(new DCPlayerService(indexService(),scoresService()));
        setGetPlayerName(new DCGetPlayerName);
        // Index services
        setIndexIterator(new DCIndexIterator);
        setUndoIndex(new DCIndexUndo);
        setRedoIndex(new DCIndexRedo);
    }
};
#endif // DEFAULTDARTSPOINTCONTROLLER_H
