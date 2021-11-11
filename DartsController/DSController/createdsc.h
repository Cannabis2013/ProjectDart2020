#ifndef CREATEDSC_H
#define CREATEDSC_H
#include "DartsController/Controller/dartscontroller.h"
#include "DartsController/DCScoresServices/dccreatescoremodels.h"
#include "DartsController/DCIndexServices/dcinputindexbuilder.h"
#include "DartsController/DSCServices/dscinputevaluator.h"
#include "DartsController/DSCServices/dscinputbuilder.h"
#include "DartsController/DSCServices/dscvaluesbuilder.h"
#include "DartsController/DCPlayerServices/dcplayerbuilder.h"
#include "DartsController/DCScoresServices/dcscoremodels.h"
#include "DartsController/DCScoresServices/dcupdateinputdetails.h"
#include "DartsController/DSCServices/getscorefromdscinput.h"
#include "DartsController/DCFinishesServices/dccreatefinishes.h"
#include "DartsController/DCFinishesServices/dclogisticdb.h"
#include "DartsController/DCFinishesServices/dcinputfinishes.h"
#include "DartsController/DCMetaServices//dartsstatuscodes.h"
#include "DartsController/DCMetaServices/dcmetainfo.h"
#include "DartsControllerBuilder/DCBMetaServices/dcbmeta.h"
#include "DartsController/DCJsonServices/dcjsonbuilder.h"
#include "DartsController/DCMetaServices/dcmetamodelbuilder.h"
#include "DartsController/DCInputServices/dcinputjsonbuilder.h"
#include "DartsController/DCIndexServices/dcindexjsonbuilder.h"
#include "DartsController/DCMetaServices/DCMetaInfoJsonBuilder.h"
#include "DartsController/DCTurnValuesServices/DCTurnValuesJsonBuilder.h"
#include "DartsController/PlayerStatsServices/dcplayerstatsmanager.h"
#include "DartsController/DCIndexServices/dscreqindexbuilder.h"
#include "DartsController/DCScoresServices/dcscorejsonbuilder.h"
#include "DartsController/DCScoresServices/dcscorejsonbuilder.h"
#include "DartsController/DCIndexServices/dcplayerstatsjsonbuilder.h"
#include "DartsController/DCIndexServices/dcreqindexjsonbuilder.h"
#include "DartsController/PlayerStatsServices/dsccalcmidval.h"
#include "DartsController/PlayerStatsServices/dcupdatescorerange.h"
#include "DartsController/PlayerStatsServices/dcupdateplayerstat.h"
#include "DartsController/IndexServices/dscindexcontroller.h"
#include "DartsController/DCPlayerServices/dscplayercontroller.h"
#include "DartsControllerBuilder/SLAs/icreatedartscontroller.h"
class CreateDSC : public ICreateDartsController<AbstractDartsContext>
{
public:
    AbstractDartsController *create(AbstractDartsContext *modelsContext) override
    {
        auto dc = new DartsController;
        dc->setTurnValuesBuilder(new DSCValuesBuilder);
        dc->setSuggestFinishes(DCInputFinishes::createInstance(DCCreateFinishes::createInstance(),
                                                               DCLogisticDb::createInstance()));
        dc->setIndexService(new DSCIndexController);
        dc->setIndexBuilder(new DCInputIndexBuilder);
        dc->setReqIndexBuilder(new DSCReqIndexBuilder);
        dc->setCreateCandidateScores(new DCUpdateInputDetails);
        dc->setScoresModels(new DCScoreModels);
        dc->setScoreBuilder(new DCCreateScoreModels);
        dc->setStatusCodes(new DCStatusCodes);
        dc->setMetaBuilder(new DCMetaModelBuilder);
        dc->setJsonResponseBuilder(createJsonBuilder());
        dc->setGetScoreFromInput(new GetScoreFromDSCInput);
        dc->setInputEvaluator(DSCInputEvaluator::createInstance());
        dc->setInputBuilder(new DSCInputBuilder);
        dc->setPlayerStatsManager(new DCPlayerStatsManager);
        dc->setUpdateMiddleVal(new DSCCalcMidVal);
        dc->setUpdateScoreRange(new DCUpdateScoreRange);
        dc->setUpdatePlayerStats(new DCUpdatePlayerStat);
        dc->setPlayerController(new DSCPlayerController);
        dc->setPlayerBuilderService(new DCPlayerBuilder);
        dc->setJsonResponseBuilder(createJsonBuilder());
        dc->setModelsContext(modelsContext);
        return dc;
    }
private:
    AbstractDCJsonBuilder *createJsonBuilder()
    {
        auto builder = new DCJsonBuilder;
        builder->setInputJsonBuilder(new DCInputJsonBuilder);
        builder->setScoreModelJsonBuilder(new DCScoreJsonBuilder);
        builder->setIndexesJsonBuilder(new DCIndexJsonBuilder);
        builder->setReqIndexJsonBuilder(new DCReqIndexJsonBuilder);
        builder->setMetaJsonBuilder(new DCMetaInfoJsonBuilder);
        builder->setPlayerStatsJsonBuilder(new DCPlayerStatsJsonBuilder);
        builder->setTurnValuesJsonBuilder(new DCTurnValuesJsonBuilder);
        return builder;
    }
};
#endif // DEFAULTDARTSSCORECONTROLLER_H
