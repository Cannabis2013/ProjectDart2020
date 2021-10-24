#ifndef DPCONTROLLER_H
#define DPCONTROLLER_H
#include "DartsController/DCIndexServices/dcinputindexbuilder.h"
#include "DartsController/DCJsonServices/addtotalscoretodartsinputsasjson.h"
#include "DartsController/DCJsonServices/addplayernamestodartsinputsasjson.h"
#include "DartsController/DCFinishesServices/dcinputfinishes.h"
#include "DartsController/DCMetaServices/determinestatusbyid.h"
#include "DartsController/DCScoresServices/dcscoresservice.h"
#include "DartsController/DCScoresServices/dcupdateinputdetails.h"
#include "DartsController/DCIndexServices/dcinitializeindexservice.h"
#include "DartsController/DCMetaServices/dcwinnerservice.h"
#include "DartsController/Controller/dartscontroller.h"
#include "DartsController/DCPlayerServices/dcplayerbuilder.h"
#include "DartsController/DCPlayerServices/dcplayerservice.h"
#include "DartsController/DCScoresServices/dccreatescoremodels.h"
#include "DartsController/DCScoresServices/dcupdatescoremodels.h"
#include "DartsController/DCScoresServices/dcgetscorecand.h"
#include "DartsController/DCIndexServices/dcindexiterator.h"
#include "DartsController/DCIndexServices/dcindexredo.h"
#include "DartsController/DCPlayerServices/dcwinnerkeys.h"
#include "DartsController/DCIndexServices/dcresetindexes.h"
#include "DartsController/DCIndexServices/dcindexundo.h"
#include "DartsController/DCPlayerServices/dcgetwinnermodelfromjson.h"
#include "DartsController/DCPlayerServices/dcplayerkeys.h"
#include "DartsController/DCFinishesServices/dccreatefinishes.h"
#include "DartsController/DCFinishesServices/dclogisticdb.h"
#include "DartsController/DCScoresServices/dcresetscoremodels.h"
#include "DartsController/DCMetaServices/dcmetastatus.h"
#include "DartsController/DCMetaServices//dartsstatuscodes.h"
#include "DartsController/DCMetaServices/dchint.h"
#include "DartsController/DCMetaServices/dcinitialscore.h"
#include "DartsController/DCMetaServices/dctournamentid.h"
#include "DartsController/DPCServices/dpcinputevaluator.h"
#include "DartsController/DPCServices/dpcindexcontroller.h"
#include "DartsController/DPCServices/CreateDPCTurnValues.h"
#include "DartsController/DPCServices/dpcinputbuilder.h"
#include "DartsController/DPCServices/getscorefromdpcinput.h"
#include "DartsController/DCIndexServices/dcindexesjsonkeys.h"
#include "DartsController/DCPlayerServices/DPCPlayerAllowancesContext.h"
#include "DartsController/DCMetaServices/dcmetajsonbuilder.h"
#include "DartsControllerBuilder/DCBMetaServices/dcmeta.h"
#include "DartsController/DCJsonServices/dcjsonbuilder.h"
#include "DartsController/DCMetaServices/dcmetamodelbuilder.h"
#include "DartsController/DCInputServices/dcinputjsonbuilder.h"
#include "DartsController/DCIndexServices/dcindexjsonbuilder.h"
#include "DartsController/DCMetaServices/DCMetaInfoJsonBuilder.h"
#include "DartsController/DCTurnValuesServices/DCTurnValuesJsonBuilder.h"
#include "DartsController/DPCStatsServices/dpcscorestats.h"
#include "DartsController/DCIndexServices/dpcreqindexbuilder.h"
#include "DartsController/DCScoresServices/dcscorejsonbuilder.h"
#include "DartsController/DCIndexServices/dcplayerstatsjsonbuilder.h"
class DPController : public DartsController
{
public:
    DPController(const DCBuilding::DCMeta &meta);
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
    const DCBuilding::DCMeta _metaInfo;
};
#endif // DEFAULTDARTSPOINTCONTROLLER_H
