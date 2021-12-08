#ifndef CREATEDSC_H
#define CREATEDSC_H
#include "DartsController/Controller/dartscontroller.h"
#include "DartsController/DSCServices/dscinputevaluator.h"
#include "DartsController/DSCServices/dscinputbuilder.h"
#include "DartsController/DSCServices/dscvaluesbuilder.h"
#include "DartsController/DSCServices/dsccalcscore.h"
#include "DartsController/DCFinishesServices/dccreatefinishes.h"
#include "DartsController/DCFinishesServices/dclogisticdb.h"
#include "DartsController/DCFinishesServices/dcfinishbuilder.h"
#include "DartsController/DCMetaServices/dcmetacontext.h"
#include "DartsController/DCJsonServices/dcjsonbuilder.h"
#include "DartsController/DCMetaServices/dcmetabuilder.h"
#include "DartsController/DCInputServices/dcinputjsonbuilder.h"
#include "DartsController/DCIndexServices/dcidxjsonbuilder.h"
#include "DartsController/DCMetaServices/DCMetaInfoJsonBuilder.h"
#include "DartsController/DCTurnValuesServices/DCTurnValuesJsonBuilder.h"
#include "DartsController/PlayerStatsServices/dcstatscontext.h"
#include "DartsController/DCScoresServices/dcscorejsonbuilder.h"
#include "DartsController/DCScoresServices/dcscorejsonbuilder.h"
#include "DartsController/DCIndexServices/dcplayerstatsjsonbuilder.h"
#include "DartsController/DCIndexServices/dcreqidxjsonbuilder.h"
#include "DartsController/IndexServices/dscindexcontroller.h"
#include "DartsModelsContext/IndexesDbServices/dcidxconverter.h"
#include "DartsController/DCInputServices/dciptconverter.h"
#include "DartsController/ModelsComCtxServices/dcaddtomodelcontext.h"
#include "DartsController/DCScoresServices/dscplayerscontext.h"
#include "DartsController/DCScoresServices/dcupdplastats.h"
#include "DartsController/PlayerStatsServices/dscupdscorerng.h"
class CreateDSC
{
public:
    static DartsController *create()
    {
        auto dc = new DartsController;
        dc->setFinishBuilder(DCFinishBuilder::createInstance(DCCreateFinishes::createInstance(),
                                                               DCLogisticDb::createInstance()));
        auto metaCtx = new DCMetaContext;
        auto idxCtrl = new DSCIndexController;
        auto plaCtx = new DSCPlayersContext();
        dc->setMetaContext(metaCtx);
        dc->setStatsContext(new DCStatsContext);
        dc->setIndexCtrl(idxCtrl);
        dc->setIdxConverter(new DCIdxConverter);
        dc->setPlayersContext(plaCtx);
        dc->setInputEvaluator(new DSCInputEvaluator);
        dc->setGetScoreFromInput(new DSCCalcScore(idxCtrl,plaCtx));
        dc->setCreateInput(new DSCInputBuilder(dc->scoreCalc()));
        dc->setIptConverter(new DCIptConverter(dc->createInput()));
        dc->setUpdateScores(new DCUpdatePlayerStats(dc->statsContext(),plaCtx));
        dc->setAddToModelsCtx(new DCAddToModelsContext(idxCtrl,dc->iptConverter(),
                                                       metaCtx,dc->idxConverter()));
        dc->setUpdateInputStats(new DSCUpdScoreRng(dc->statsContext()));
        dc->setMetaBuilder(new DCMetaBuilder(metaCtx,idxCtrl,plaCtx));
        dc->setTurnValuesBuilder(new DSCValuesBuilder(idxCtrl,plaCtx,dc->finishBuilder()));
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
