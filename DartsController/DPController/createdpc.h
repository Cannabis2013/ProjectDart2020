#ifndef CREATEDPC_H
#define CREATEDPC_H
#include "DartsController/DCFinishesServices/dcfinishbuilder.h"
#include "DartsController/DCScoresServices/dpcplayerscontext.h"
#include "DartsController/Controller/dartscontroller.h"
#include "DartsController/DCFinishesServices/dccreatefinishes.h"
#include "DartsController/DCFinishesServices/dclogisticdb.h"
#include "DartsController/DCMetaServices/dcmetacontext.h"
#include "DartsController/DPCServices/dpcinputevaluator.h"
#include "DartsController/DPCServices/DPCTurnValuesBuilder.h"
#include "DartsController/DPCServices/dpcinputbuilder.h"
#include "DartsController/DPCServices/getscorefromdpcinput.h"
#include "DartsController/DCJsonServices/dcjsonbuilder.h"
#include "DartsController/DCMetaServices/dcmetabuilder.h"
#include "DartsController/DCInputServices/dcinputjsonbuilder.h"
#include "DartsController/DCIndexServices/dcidxjsonbuilder.h"
#include "DartsController/DCMetaServices/DCMetaInfoJsonBuilder.h"
#include "DartsController/DCTurnValuesServices/DCTurnValuesJsonBuilder.h"
#include "DartsController/DCScoresServices/dcscorejsonbuilder.h"
#include "DartsController/DCIndexServices/dcplayerstatsjsonbuilder.h"
#include "DartsController/PlayerStatsServices/dpcupdatescorerange.h"
#include "DartsController/IndexServices/dpcidxctrl.h"
#include "DartsController/DCIndexServices/dcreqidxjsonbuilder.h"
#include "DartsModelsContext/IndexesDbServices/dcidxconverter.h"
#include "DartsController/DCInputServices/dciptconverter.h"
#include "DartsController/ModelsComCtxServices/dcaddtomodelcontext.h"
#include "DartsController/DCScoresServices/dcupdplastats.h"
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
        dc->setGetScoreFromInput(new GetScoreFromDPCInput(dc->idxCtrl(),dc->playersContext()));
        dc->setCreateInput(new DPCInputBuilder(dc->scoreCalc()));
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
