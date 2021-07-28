#ifndef JSONMODELSSERVICE_H
#define JSONMODELSSERVICE_H
#include "dartsmodelsservice.h"
// Genereic models includes
#include "removeinputsfromdb.h"
#include "removemodelsfromdb.h"
// Input models includes
#include "dartspointjsondb.h"
#include "dartsinputjsondb.h"
#include "dartsscoresethint.h"
#include "dartspointsethint.h"
#include "getinputmodelsservice.h"
#include "inputmodelssortservice.h"
#include "sortdartspointinputsbyindexes.h"
#include "inputmodelscountservice.h"
#include "dartspointsjsonservice.h"
#include "dartscreatejsonfromscores.h"
#include "dartspointjsondb.h"
#include "dartsscorejsondb.h"
#include "createdartsscoreindexes.h"
#include "getdartsscorefromdb.h"
#include "getdartspointfromdb.h"
#include "dartscreatepointindexes.h"
#include "createjsonfromdartspointindexes.h"
#include "dartsscoresethint.h"
#include "dartscreatejsonfromdartspoint.h"
#include "dartscreatejsonfromdartsscore.h"
#include "createplayermodels.h"
// Player models includes
#include "getplayersfromdb.h"
#include "createjsonfromplayers.h"
#include "createplayerfromjson.h"
#include "jsonplayersdbcontext.h"
#include "localplayersdbcontext.h"
// Tournament models includes
#include "removemodelsfromdb.h"
#include "adddetailstotournamentjson.h"
#include "tournamentsjsondb.h"
#include "createdartstournamentfromjson.h"
#include "dartstournamentjsonbuilder.h"
#include "dartstournamentsjsondb.h"
#include "getdartstournamentfromdb.h"
#include "extractwinnerinfofromjson.h"
#include "addplayerdetailstotournament.h"
#include "getdatafromdartstournament.h"
#include "dartscreatejsonfromscoreindexes.h"
#include "dartscreatejsonmetadata.h"
#include "dartscreatepointmodel.h"
#include "dartscreatescoremodel.h"
#include "gettournamentwinner.h"
#include "createjsonfromtournamentdetails.h"

class JsonModelsService : public ModelsContext::DartsModelsService
{
public:
    JsonModelsService();
private:
    void setModelUtilityServices();
    void setTournamentServices();
    void setScoreInputServices();
    void setPointInputServices();
    void setInputDbUtilityServices();
    void setModelsServices();
};

#endif // DARTSMODELSSERVICEWITHJSONDB_H
