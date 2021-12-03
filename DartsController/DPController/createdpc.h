#ifndef CREATEDPC_H
#define CREATEDPC_H
#include "DartsController/DCFinishesServices/dcfinishbuilder.h"
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
#include "DartsController/DCIndexServices/dcidxjsonbuilder.h"
#include "DartsController/DCMetaServices/DCMetaInfoJsonBuilder.h"
#include "DartsController/DCTurnValuesServices/DCTurnValuesJsonBuilder.h"
#include "DartsController/DCIndexServices/dpcreqindexbuilder.h"
#include "DartsController/DCScoresServices/dcscorejsonbuilder.h"
#include "DartsController/DCIndexServices/dcplayerstatsjsonbuilder.h"
#include "DartsController/PlayerStatsServices/dcupdateplayerstat.h"
#include "DartsController/PlayerStatsServices/dcupdatescorerange.h"
#include "DartsController/PlayerStatsServices/dpccalcmidval.h"
#include "DartsController/IndexServices/dpcidxctrl.h"
#include "DartsController/DCIndexServices/dcreqidxjsonbuilder.h"
#include "DartsModelsContext/IndexesDbServices/dcidxconverter.h"
#include "DartsController/DCInputServices/dciptconverter.h"
class CreateDPC
{
public:
    static DartsController *create()
    {
        auto dc = new DartsController;
        dc->setStatusCodes(new DCStatusCodes);
        dc->setMetaContext(new DCMetaContext);
        dc->setIdxConverter(new DCIdxConverter);
        dc->setScoreBuilder(new DCCreateScoreModels);
        dc->setScoresModels(new DCScoresContext(dc->metaContext()));
        dc->setCreateCandidateScores(new DCUpdateInputDetails);
        dc->setPlayerStatsManager(new DCPlayerStatsManager);
        dc->setUpdateMiddleVal(new DPCCalcMidVal);
        dc->setUpdatePlayerStats(new DCUpdatePlayerStat);
        dc->setFinishBuilder(DCFinishBuilder::createInstance(DCCreateFinishes::createInstance(),DCLogisticDb::createInstance()));
        dc->setPlayerContext(new DPCPlayerContext);
        dc->setInputEvaluator(DPCInputEvaluator::createInstance());
        dc->setGetScoreFromInput(new GetScoreFromDPCInput);
        dc->setIndexCtrl(new DPCIdxCtrl);
        dc->setIdxConverter(new DCIdxConverter);
        dc->setIptConverter(new DCIptConverter);
        dc->setInputBuilder(new DPCInputBuilder(dc->metaContext(),dc->scoreCalc(),dc->idxCtrl(),dc->scoresContext(),dc->playersContext()));
        dc->setUpdateScoreRange(new DCUpdateScoreRange(dc->statsContext(),dc->calcMidVal(),dc->idxCtrl(),dc->metaContext()));
        dc->setTurnValuesBuilder(new DPCTurnValuesBuilder(dc->idxCtrl(),dc->scoresContext(),dc->finishBuilder()));
        dc->setReqIndexBuilder(new DPCReqIndexBuilder(dc->idxCtrl()));
        dc->setMetaBuilder(new DCMetaBuilder(dc->metaContext(),dc->idxCtrl(),dc->scoresContext(),dc->statusCodes()));
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
