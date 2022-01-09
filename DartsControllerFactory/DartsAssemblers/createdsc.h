#ifndef CREATEDSC_H
#define CREATEDSC_H
#include "DSCServices/dscinputevaluator.h"
#include "DSCServices/dscinputbuilder.h"
#include "DSCServices/dscvaluesbuilder.h"
#include "DSCServices/dsccreatescore.h"
#include "DCFinishesServices/dccreatefinishes.h"
#include "DCFinishesServices/dclogisticdb.h"
#include "DCFinishesServices/dcfinishbuilder.h"
#include "DCMetaServices/dcmetacontext.h"
#include "DCJsonServices/dcjsonbuilder.h"
#include "DCMetaServices/dcmetabuilder.h"
#include "DCInputServices/dcinputjsonbuilder.h"
#include "DCIndexServices/dcidxjsonbuilder.h"
#include "DCMetaServices/DCMetaInfoJsonBuilder.h"
#include "DCTurnValuesServices/DCTurnValuesJsonBuilder.h"
#include "PlayerStatsServices/dcstatscontext.h"
#include "DCScoresServices/dcscorejsonbuilder.h"
#include "DCScoresServices/dcscorejsonbuilder.h"
#include "DCIndexServices/dcplayerstatsjsonbuilder.h"
#include "DCIndexServices/dcreqidxjsonbuilder.h"
#include "IndexServices/dscindexcontroller.h"
#include "DCInputServices/dciptconverter.h"
#include "ModelsComCtxServices/dcaddtomodelcontext.h"
#include "DCScoresServices/dscplayerscontext.h"
#include "DCScoresServices/dcupdplastats.h"
#include "PlayerStatsServices/dscupdscorerng.h"
#include "ConverterServices/dcidxconverter.h"
#include "dartscontroller.h"
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
        dc->setTurnValuesBuilder(new DSCValuesBuilder);
        dc->setGetScoreFromInput(new DSCCreateScore);
        dc->setCreateInput(new DSCInputBuilder);
        dc->setIptConverter(new DCIptConverter(dc->createInput()));
        dc->setUpdateScores(new DCUpdatePlayerStats(dc->statsContext(),plaCtx));
        dc->setAddToModelsCtx(new DCAddToModelsContext(dc->iptConverter(),dc->idxConverter()));
        dc->setUpdateInputStats(new DSCUpdScoreRng(dc->statsContext()));
        dc->setMetaBuilder(new DCMetaBuilder(metaCtx,idxCtrl,plaCtx));
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
