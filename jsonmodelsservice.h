#ifndef JSONMODELSSERVICE_H
#define JSONMODELSSERVICE_H
#include "dartsmodelsservice.h"
// Genereic models includes
#include "removeinputsfromdb.h"
#include "removemodelsfromdb.h"
// Input models includes
#include "dartsinputsjsondb.h"
#include "dartsinputjsondb.h"
#include "dartspointsethint.h"
#include "getinputmodelsservice.h"
#include "inputmodelssortservice.h"
#include "sortdartspointinputsbyindexes.h"
#include "inputmodelscountservice.h"
#include "dartspointsjsonservice.h"
#include "dartsinputsjsondb.h"
#include "getdartspointfromdb.h"
#include "dartscreateindexes.h"
#include "dartsinputindexestojson.h"
#include "dartscreatejsonfromdartspoint.h"
#include "createplayermodels.h"
// Player models includes
#include "getplayersfromdb.h"
#include "createjsonfromplayers.h"
#include "createplayerfromjson.h"
#include "jsonplayersdbcontext.h"
#include "localplayersdbcontext.h"
// Tournament models includes
#include "dartstournamentextractor.h"
#include "removemodelsfromdb.h"
#include "adddetailstotournamentjson.h"
#include "tournamentsjsondb.h"
#include "createdartstournamentfromjson.h"
#include "dartstournamentjsonbuilder.h"
#include "dartstournamentsjsondb.h"
#include "getdartstournamentfromdb.h"
#include "extractwinnerinfofromjson.h"
#include "addplayerdetailstotournament.h"
#include "dartscreatejsonmetadata.h"
#include "dartscreateinputmodel.h"
#include "gettournamentwinner.h"
#include "createjsonfromtournamentdetails.h"

class JsonModelsService : public DartsModelsService
{
public:
    JsonModelsService();
private:
    void setModelUtilityServices();
    void setTournamentServices();
    void setPointInputServices();
    void setInputDbUtilityServices();
    void setModelsServices();
};

#endif // DARTSMODELSSERVICEWITHJSONDB_H
