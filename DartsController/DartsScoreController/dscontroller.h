#ifndef DSCONTROLLER_H
#define DSCONTROLLER_H
#include "DartsController/Controller/dartscontroller.h"
#include "DartsController/DCScoresServices/dccreatescoremodels.h"
#include "DartsController/DCIndexServices/dcinputindexbuilder.h"
#include <quuid.h>
#include "DartsController/DSCServices/dscinputevaluator.h"
#include "DartsController/DCMetaServices/dcwinnerservice.h"
#include "DartsController/DSCServices/dscinputbuilder.h"
#include "DartsController/DCMetaServices/determinestatusbyid.h"
#include "DartsController/DSCServices/dscvaluesbuilder.h"
#include "DartsController/DCPlayerServices/dcplayerbuilder.h"
#include "DartsController/DCScoresServices/dcscoremodels.h"
#include "DartsController/DCScoresServices/dcupdatescoremodels.h"
#include "DartsController/DCScoresServices/dcupdateinputdetails.h"
#include "DartsController/DCScoresServices/dcgetscorecand.h"
#include "DartsController/DSCServices/getscorefromdscinput.h"
#include "DartsController/DCFinishesServices/dccreatefinishes.h"
#include "DartsController/DCFinishesServices/dclogisticdb.h"
#include "DartsController/DCFinishesServices/dcinputfinishes.h"
#include "DartsController/DCMetaServices//dartsstatuscodes.h"
#include "DartsController/DCMetaServices/dcmetastatus.h"
#include "DartsController/DCMetaServices/dchint.h"
#include "DartsController/DCMetaServices/dcinitialscore.h"
#include "DartsController/DCMetaServices/dctournamentid.h"
#include "DartsController/DCIndexServices/dcindexesjsonkeys.h"
#include "DartsController/DCMetaServices/dcmetajsonbuilder.h"
#include "DartsControllerBuilder/DCBMetaServices/dcmeta.h"
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
#include "DartsController/PlayerStatsServices/dscupdatemidval.h"
#include "DartsController/PlayerStatsServices/dcupdatescorerange.h"
#include "DartsController/PlayerStatsServices/dcupdateplayerstat.h"
#include "DartsController/IndexServices/dscindexcontroller.h"
class DSController : public DartsController
{
public:
    DSController(const DCBuilding::DCMeta &meta);
private:
    AbstractDCJsonBuilder *createJsonBuilder();
};
#endif // DEFAULTDARTSSCORECONTROLLER_H
