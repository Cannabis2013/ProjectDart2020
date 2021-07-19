#ifndef JSONDARTSMODELSSERVICE_H
#define JSONDARTSMODELSSERVICE_H

#include "dartsmodelsservice.h"
// Genereic models includes
#include "removeinputsfromdb.h"
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
#include "getdartsplayermodelsfromdb.h"
#include "dartsplayerjsonbuilder.h"
#include "dartsplayermodelbuilder.h"
#include "playermodelsjsondb.h"
#include "playermodelslocaljsondb.h"
#include "getdatafromplayermodels.h"
// Tournament models includes
#include "removetournamentsfromdb.h"
#include "adddetailstotournamentjson.h"
#include "tournamentsjsondb.h"
#include "dartstournamentbuilder.h"
#include "dartstournamentjsonbuilder.h"
#include "dartstournamentsjsondb.h"
#include "getdartstournamentfromdb.h"
#include "getdartstournamentdatafromjson.h"
#include "addplayerdetailstotournament.h"
#include "getdatafromdartstournament.h"
#include "dartscreatejsonfromscoreindexes.h"
#include "dartscreatejsonmetadata.h"
#include "dartscreatepointmodel.h"
#include "dartscreatescoremodel.h"
#include "gettournamentwinner.h"
#include "settournamentwinnerid.h"
// Db utilities
#include "dbgetindexesfromjson.h"

class JsonDartsModelsService : public DartsModelsContext::DartsModelsService
{
public:
    JsonDartsModelsService();
private:
    void setPlayerRelatedServices();
    void setModelUtilityServices();
    void setTournamentServices();
    void setScoreInputServices();
    void setPointInputServices();
    void setInputDbUtilityServices();
    void setModelsServices();
    void setUtilitiyServices();
};

#endif // DARTSMODELSSERVICEWITHJSONDB_H
