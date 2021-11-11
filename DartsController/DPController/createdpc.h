#ifndef CREATEDPC_H
#define CREATEDPC_H
#include "DartsController/DCIndexServices/dcinputindexbuilder.h"
#include "DartsController/DCFinishesServices/dcinputfinishes.h"
#include "DartsController/DCScoresServices/dcscoremodels.h"
#include "DartsController/DCScoresServices/dcupdateinputdetails.h"
#include "DartsController/Controller/dartscontroller.h"
#include "DartsController/DCPlayerServices/dcplayerbuilder.h"
#include "DartsController/DCScoresServices/dccreatescoremodels.h"
#include "DartsController/DCFinishesServices/dccreatefinishes.h"
#include "DartsController/DCFinishesServices/dclogisticdb.h"
#include "DartsController/DCMetaServices//dartsstatuscodes.h"
#include "DartsController/DCMetaServices/dcmetainfo.h"
#include "DartsController/DPCServices/dpcinputevaluator.h"
#include "DartsController/DPCServices/DPCTurnValuesBuilder.h"
#include "DartsController/DPCServices/dpcinputbuilder.h"
#include "DartsController/DPCServices/getscorefromdpcinput.h"
#include "DartsController/DCPlayerServices/dpcplayercontroller.h"
#include "DartsControllerBuilder/DCBMetaServices/dcbmeta.h"
#include "DartsController/DCJsonServices/dcjsonbuilder.h"
#include "DartsController/DCMetaServices/dcmetamodelbuilder.h"
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
#include "DartsController/IndexServices/dpcindexcontroller.h"
#include "DartsController/DCIndexServices/dcreqindexjsonbuilder.h"
#include "DartsControllerBuilder/SLAs/icreatedartscontroller.h"
class CreateDPC : public ICreateDartsController<AbstractDartsContext>
{
public:
    virtual AbstractDartsController *create(AbstractDartsContext *modelsContext) override
    {
        auto dc = new DartsController;
        dc->setStatusCodes(new DCStatusCodes);
        dc->setMetaBuilder(new DCMetaModelBuilder);
        dc->setScoreBuilder(new DCCreateScoreModels);
        dc->setScoresModels(new DCScoreModels);
        dc->setCreateCandidateScores(new DCUpdateInputDetails);
        dc->setJsonResponseBuilder(createJsonBuilder());
        dc->setPlayerStatsManager(new DCPlayerStatsManager);
        dc->setUpdateMiddleVal(new DPCCalcMidVal);
        dc->setUpdateScoreRange(new DCUpdateScoreRange);
        dc->setUpdatePlayerStats(new DCUpdatePlayerStat);
        dc->setSuggestFinishes(DCInputFinishes::createInstance(DCCreateFinishes::createInstance(),
                                                               DCLogisticDb::createInstance()));
        dc->setPlayerController(new DPCPlayerController);
        dc->setPlayerBuilderService(new DCPlayerBuilder);
        dc->setInputBuilder(new DPCInputBuilder);
        dc->setInputEvaluator(DPCInputEvaluator::createInstance());
        dc->setGetScoreFromInput(new GetScoreFromDPCInput);
        dc->setIndexService(new DPCIndexController);
        dc->setIndexBuilder(new DCInputIndexBuilder);
        dc->setReqIndexBuilder(new DPCReqIndexBuilder);
        dc->setTurnValuesBuilder(new DPCTurnValuesBuilder);
        dc->setJsonResponseBuilder(createJsonBuilder());
        dc->setModelsContext(modelsContext);
        return dc;
    }
private:
    AbstractDCJsonBuilder *createJsonBuilder()
    {
        auto builder = new DCJsonBuilder;
        builder->setInputJsonBuilder(new DCInputJsonBuilder);
        builder->setIndexesJsonBuilder(new DCIndexJsonBuilder);
        builder->setMetaJsonBuilder(new DCMetaInfoJsonBuilder);
        builder->setTurnValuesJsonBuilder(new DCTurnValuesJsonBuilder);
        builder->setScoreModelJsonBuilder(new DCScoreJsonBuilder);
        builder->setPlayerStatsJsonBuilder(new DCPlayerStatsJsonBuilder);
        builder->setReqIndexJsonBuilder(new DCReqIndexJsonBuilder);
        return builder;
    }
};
#endif // DEFAULTDARTSPOINTCONTROLLER_H
