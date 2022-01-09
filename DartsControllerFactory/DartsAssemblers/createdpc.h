#ifndef CREATEDPC_H
#define CREATEDPC_H
#include "DCFinishesServices/dcfinishbuilder.h"
#include "DCScoresServices/dpcplayerscontext.h"
#include "DCFinishesServices/dccreatefinishes.h"
#include "DCFinishesServices/dclogisticdb.h"
#include "DCMetaServices/dcmetacontext.h"
#include "DPCServices/dpcinputevaluator.h"
#include "DPCServices/DPCTurnValuesBuilder.h"
#include "DPCServices/dpcinputbuilder.h"
#include "DPCServices/dpccreatescore.h"
#include "DCJsonServices/dcjsonbuilder.h"
#include "DCMetaServices/dcmetabuilder.h"
#include "DCInputServices/dcinputjsonbuilder.h"
#include "DCIndexServices/dcidxjsonbuilder.h"
#include "DCMetaServices/DCMetaInfoJsonBuilder.h"
#include "DCTurnValuesServices/DCTurnValuesJsonBuilder.h"
#include "DCScoresServices/dcscorejsonbuilder.h"
#include "DCIndexServices/dcplayerstatsjsonbuilder.h"
#include "PlayerStatsServices/dpcupdatescorerange.h"
#include "IndexServices/dpcidxctrl.h"
#include "DCIndexServices/dcreqidxjsonbuilder.h"
#include "DCInputServices/dciptconverter.h"
#include "ModelsComCtxServices/dcaddtomodelcontext.h"
#include "DCScoresServices/dcupdplastats.h"
#include "dartscontroller.h"
#include "ConverterServices/dcidxconverter.h"
#include "PlayerStatsServices/dcstatscontext.h"
class CreateDPC
{
public:
    static DartsController *create()
    {
        auto dc = new DartsController;
        dc->setMetaContext(new DCMetaContext);
        dc->setIdxConverter(new DCIdxConverter);
        dc->setStatsContext(new DCStatsContext);
        dc->setFinishBuilder(DCFinishBuilder::createInstance(DCCreateFinishes::createInstance(),
                                                             DCLogisticDb::createInstance()));
        dc->setIndexCtrl(new DPCIdxCtrl);
        dc->setIdxConverter(new DCIdxConverter);
        dc->setPlayersContext(new DPCPlayersContext);
        dc->setInputEvaluator(new DPCInputEvaluator);
        dc->setTurnValuesBuilder(new DPCTurnValuesBuilder);
        dc->setGetScoreFromInput(new DPCCreateScore);
        dc->setCreateInput(new DPCInputBuilder);
        dc->setUpdateScores(new DCUpdatePlayerStats(dc->statsContext(),dc->playersContext()));
        dc->setIptConverter(new DCIptConverter(dc->createInput()));
        dc->setAddToModelsCtx(new DCAddToModelsContext(dc->iptConverter(),dc->idxConverter()));
        dc->setUpdateInputStats(new DPCUpdateScoreRange(dc->statsContext()));
        dc->setMetaBuilder(new DCMetaBuilder(dc->metaCtx(),dc->idxCtrl(),dc->playersContext()));
        auto builder = new DCJsonBuilder;
        builder->setInputJsonBuilder(new DCInputJsonBuilder);
        builder->setIdxJsonBuilder(new DCIdxJsonBuilder);
        builder->setMetaJsonBuilder(new DCMetaInfoJsonBuilder);
        builder->setTurnValuesJsonBuilder(new DCTurnValuesJsonBuilder);
        builder->setScoreModelJsonBuilder(new DCScoreJsonBuilder);
        builder->setPlayerStatsJsonBuilder(new DCPlayerStatsJsonBuilder);
        builder->setReqIdxJsonBuilder(new DCReqIdxJsonBuilder);
        dc->setJsonResponseBuilder(builder);
        return dc;
    }
};
#endif // DEFAULTDARTSPOINTCONTROLLER_H
