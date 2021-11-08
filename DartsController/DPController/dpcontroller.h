#ifndef DPCONTROLLER_H
#define DPCONTROLLER_H
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
#include <DartsController/DCIndexServices/dcreqindexjsonbuilder.h>
class DPController : public DartsController
{
public:
    DPController(const DCBMeta &meta);
private:
    void setMetaServices();
    void setScoresServices();
    void setJsonServices();
    void setStatisticsServices();
    void setFinishesServices();
    void setPlayerServices();
    void setInputServices();
    void setIndexServices();
    void setTurnValuesServices();
    AbstractDCJsonBuilder *createJsonBuilder();
    const DCBMeta _metaInfo;
};
#endif // DEFAULTDARTSPOINTCONTROLLER_H
