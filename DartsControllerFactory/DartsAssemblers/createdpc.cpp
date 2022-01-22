#include "createdpc.h"
#include "DCFinishesServices/dcfinishbuilder.h"
#include "DCScoresServices/dpcplayerscontext.h"
#include "DCFinishesServices/dclogisticdb.h"
#include "DCMetaServices/dcmetacontext.h"
#include "DPCServices/dpcinputevaluator.h"
#include "DPCServices/DPCTurnValuesBuilder.h"
#include "DPCServices/dpcinputadder.h"
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
#include "ModelsComCtxServices/dcaddtomodelcontext.h"
#include "DCScoresServices/dcupdplastats.h"
#include "dartscontroller.h"
#include "ConverterServices/dcindexconverter.h"
#include "PlayerStatsServices/dcstatscontext.h"
#include "DCFinishesServices/dartscreatefinishes.h"
#include "Injectors/dcinjectfinclient.h"
CreateDPC::CreateDPC()
{
    finInjector = new DCInjectFinClient;
}

AbsDartsCtrl *CreateDPC::create()
{
    auto dc = new DartsController;
    finInjector->inject(dc);
    dc->setMetaContext(new DCMetaContext);
    dc->setIndexConverter(new DCIndexConverter);
    dc->setStatistics(new DCStatsContext);
    dc->setIndexCtrl(new DPCIdxCtrl);
    dc->setIndexConverter(new DCIndexConverter);
    dc->setPlayersContext(new DPCPlayersContext);
    dc->setInputEvaluator(new DPCInputEvaluator);
    dc->setTurnValuesBuilder(new DPCTurnValuesBuilder);
    dc->setGetScoreFromInput(new DPCCreateScore);
    dc->setCreateInput(new DPCInputAdder);
    dc->setUpdateScores(new DCUpdatePlayerStats);
    dc->setAddToModelsCtx(new DCAddToModelsContext);
    dc->setUpdateInputStats(new DPCUpdateScoreRange);
    dc->setMetaBuilder(new DCMetaBuilder);
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
