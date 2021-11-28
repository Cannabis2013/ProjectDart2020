#ifndef CREATEDSC_H
#define CREATEDSC_H
#include "DartsController/Controller/dartsctrl.h"
#include "DartsController/DCScoresServices/dccreatescoremodels.h"
#include "DartsController/DSCServices/dscinputevaluator.h"
#include "DartsController/DSCServices/dscinputbuilder.h"
#include "DartsController/DSCServices/dscvaluesbuilder.h"
#include "DartsController/DCScoresServices/dcscorescontext.h"
#include "DartsController/DCScoresServices/dcupdateinputdetails.h"
#include "DartsController/DSCServices/getscorefromdscinput.h"
#include "DartsController/DCFinishesServices/dccreatefinishes.h"
#include "DartsController/DCFinishesServices/dclogisticdb.h"
#include "DartsController/DCFinishesServices/dcfinishbuilder.h"
#include "DartsController/DCMetaServices//dartsstatuscodes.h"
#include "DartsController/DCMetaServices/dcmetacontext.h"
#include "DartsControllerBuilder/DCBMetaServices/dcbmeta.h"
#include "DartsController/DCJsonServices/dcjsonbuilder.h"
#include "DartsController/DCMetaServices/dcmetabuilder.h"
#include "DartsController/DCInputServices/dcinputjsonbuilder.h"
#include "DartsController/DCIndexServices/dcidxjsonbuilder.h"
#include "DartsController/DCMetaServices/DCMetaInfoJsonBuilder.h"
#include "DartsController/DCTurnValuesServices/DCTurnValuesJsonBuilder.h"
#include "DartsController/PlayerStatsServices/dcplayerstatsmanager.h"
#include "DartsController/DCIndexServices/dscreqindexbuilder.h"
#include "DartsController/DCScoresServices/dcscorejsonbuilder.h"
#include "DartsController/DCScoresServices/dcscorejsonbuilder.h"
#include "DartsController/DCIndexServices/dcplayerstatsjsonbuilder.h"
#include "DartsController/DCIndexServices/dcreqidxjsonbuilder.h"
#include "DartsController/PlayerStatsServices/dsccalcmidval.h"
#include "DartsController/PlayerStatsServices/dcupdatescorerange.h"
#include "DartsController/PlayerStatsServices/dcupdateplayerstat.h"
#include "DartsController/IndexServices/dscindexcontroller.h"
#include "DartsController/DCPlayerServices/dscplayercontroller.h"
#include "DartsModelsContext/IndexesDbServices/dcidxconverter.h"
#include <DartsController/DCInputServices/dciptconverter.h>
class CreateDSC
{
public:
    static DartsCtrl *create()
    {
        auto dc = new DartsCtrl;
        dc->setFinishBuilder(DCFinishBuilder::createInstance(DCCreateFinishes::createInstance(),
                                                               DCLogisticDb::createInstance()));
        dc->setIdxConverter(new DCIdxConverter);
        dc->setCreateCandidateScores(new DCUpdateInputDetails);
        dc->setScoreBuilder(new DCCreateScoreModels);
        dc->setStatusCodes(new DCStatusCodes);
        dc->setMetaContext(new DCMetaContext);
        dc->setGetScoreFromInput(new GetScoreFromDSCInput);
        dc->setInputEvaluator(DSCInputEvaluator::createInstance());
        dc->setPlayerStatsManager(new DCPlayerStatsManager);
        dc->setUpdateMiddleVal(new DSCCalcMidVal);
        dc->setUpdatePlayerStats(new DCUpdatePlayerStat);
        dc->setPlayerContext(new DSCPlayerController);
        dc->setIndexCtrl(new DSCIndexController);
        dc->setScoresModels(new DCScoresContext(dc->metaCtx()));
        dc->setIptConverter(new DCIptConverter);
        dc->setInputBuilder(new DSCInputBuilder(dc->metaCtx(),dc->scoreCalc(),dc->idxCtrl(),dc->scoresCtx(),dc->playersCtx()));
        dc->setUpdateScoreRange(new DCUpdateScoreRange(dc->statsCtx(),dc->calcMidVal(),dc->idxCtrl(),dc->metaCtx()));
        dc->setReqIndexBuilder(new DSCReqIndexBuilder(dc->idxCtrl()));
        dc->setMetaBuilder(new DCMetaBuilder(dc->metaCtx(),dc->idxCtrl(),dc->scoresCtx(),dc->statusCodes()));
        dc->setTurnValuesBuilder(new DSCValuesBuilder(dc->idxCtrl(),dc->scoresCtx(),dc->finishBuilder()));
        auto builder = new DCJsonBuilder;
        builder->setInputJsonBuilder(new DCInputJsonBuilder);
        builder->setScoreModelJsonBuilder(new DCScoreJsonBuilder);
        builder->setIdxJsonBuilder(new DCIdxJsonBuilder);
        builder->setReqIdxJsonBuilder(new DCReqIdxJsonBuilder);
        builder->setMetaJsonBuilder(new DCMetaInfoJsonBuilder);
        builder->setPlayerStatsJsonBuilder(new DCPlayerStatsJsonBuilder);
        builder->setTurnValuesJsonBuilder(new DCTurnValuesJsonBuilder);
        dc->setJsonResponseBuilder(builder);
        return dc;
    }
};
#endif // DEFAULTDARTSSCORECONTROLLER_H
