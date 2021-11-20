#ifndef CREATEDPC_H
#define CREATEDPC_H
#include "DartsController/DCFinishesServices/dcinputfinishes.h"
#include "DartsController/DCScoresServices/dcscorescontext.h"
#include "DartsController/DCScoresServices/dcupdateinputdetails.h"
#include "DartsController/Controller/dartscontroller.h"
#include "DartsController/DCScoresServices/dccreatescoremodels.h"
#include "DartsController/DCFinishesServices/dccreatefinishes.h"
#include "DartsController/DCFinishesServices/dclogisticdb.h"
#include "DartsController/DCMetaServices//dartsstatuscodes.h"
#include "DartsController/DCMetaServices/dcmetacontext.h"
#include "DartsController/DPCServices/dpcinputevaluator.h"
#include "DartsController/DPCServices/DPCTurnValuesBuilder.h"
#include "DartsController/DPCServices/dpcinputbuilder.h"
#include "DartsController/DPCServices/getscorefromdpcinput.h"
#include "DartsController/DCPlayerServices/dpcplayercontext.h"
#include "DartsControllerBuilder/DCBMetaServices/dcbmeta.h"
#include "DartsController/DCJsonServices/dcjsonbuilder.h"
#include "DartsController/DCMetaServices/dcmetabuilder.h"
#include "DartsController/DCInputServices/dcinputjsonbuilder.h"
#include "DartsController/DCIndexServices/dcindexjsonbuilder.h"
#include "DartsController/DCMetaServices/DCMetaInfoJsonBuilder.h"
#include "DartsController/DCTurnValuesServices/DCTurnValuesJsonBuilder.h"
#include "DartsController/DCIndexServices/dpcreqindexbuilder.h"
#include "DartsController/DCScoresServices/dcscorejsonbuilder.h"
#include "DartsController/DCIndexServices/dcplayerstatsjsonbuilder.h"
#include "DartsController/PlayerStatsServices/dcupdateplayerstat.h"
#include "DartsController/PlayerStatsServices/dcupdatescorerange.h"
#include "DartsController/PlayerStatsServices/dpccalcmidval.h"
#include "DartsController/IndexServices/dpcidxctrl.h"
#include "DartsController/DCIndexServices/dcreqindexjsonbuilder.h"
#include "DartsModelsContext/IndexesDbServices/dcindexbuilder.h"
class CreateDPC
{
public:
    static AbstractDartsController *create()
    {
        auto dc = new DartsController;
        dc->setStatusCodes(new DCStatusCodes);
        dc->setMetaContext(new DCMetaContext);
        dc->setIndexBuilder(new DCIndexBuilder);
        dc->setScoreBuilder(new DCCreateScoreModels);
        dc->setScoresModels(new DCScoresContext(dc->metaContext()));
        dc->setCreateCandidateScores(new DCUpdateInputDetails);
        dc->setPlayerStatsManager(new DCPlayerStatsManager);
        dc->setUpdateMiddleVal(new DPCCalcMidVal);
        dc->setUpdatePlayerStats(new DCUpdatePlayerStat);
        dc->setDartsFinishBuilder(DCInputFinishes::createInstance(DCCreateFinishes::createInstance(),
                                                                  DCLogisticDb::createInstance()));
        dc->setPlayerContext(new DPCPlayerContext);
        dc->setInputEvaluator(DPCInputEvaluator::createInstance());
        dc->setGetScoreFromInput(new GetScoreFromDPCInput);
        dc->setIndexCtrl(new DPCIdxCtrl(dc->indexBuilder()));
        dc->setIndexBuilder(new DCIndexBuilder);
        dc->setInputBuilder(new DPCInputBuilder(dc->metaContext(),dc->scoreCalculator(),dc->idxCtrl(),dc->scoresCtx(),dc->playersCtx()));
        dc->setUpdateScoreRange(new DCUpdateScoreRange(dc->statsCtx(),dc->calcMidVal(),dc->idxCtrl(),dc->metaContext()));
        dc->setTurnValuesBuilder(new DPCTurnValuesBuilder(dc->idxCtrl(),dc->scoresCtx(),dc->dartsFinishBuilder()));
        dc->setReqIndexBuilder(new DPCReqIndexBuilder(dc->idxCtrl(),dc->indexBuilder()));
        dc->setMetaBuilder(new DCMetaBuilder(dc->metaContext(),dc->idxCtrl(),dc->scoresCtx(),dc->statusCodes()));
        auto builder = new DCJsonBuilder;
        builder->setInputJsonBuilder(new DCInputJsonBuilder);
        builder->setIndexesJsonBuilder(new DCIndexJsonBuilder);
        builder->setMetaJsonBuilder(new DCMetaInfoJsonBuilder);
        builder->setTurnValuesJsonBuilder(new DCTurnValuesJsonBuilder);
        builder->setScoreModelJsonBuilder(new DCScoreJsonBuilder);
        builder->setPlayerStatsJsonBuilder(new DCPlayerStatsJsonBuilder);
        builder->setReqIndexJsonBuilder(new DCReqIndexJsonBuilder);
        dc->setJsonResponseBuilder(builder);
        return dc;
    }
};
#endif // DEFAULTDARTSPOINTCONTROLLER_H
