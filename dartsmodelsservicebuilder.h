#ifndef DARTSTOURNAMNETMODELSERVICEBUILDER_H
#define DARTSTOURNAMNETMODELSERVICEBUILDER_H

#include "dartsmodelsservice.h"
#include "imodelsservicebuilder.h"
#include "getordereddartspointmodels.h"
#include "tournamentjsondb.h"
#include "dartspointjsondbservice.h"
#include "dartsscorejsondb.h"
#include "getdartspointindexesbydartspointmodel.h"
#include "assemblesingleattemptpointsfromjson.h"
#include "assemblejsonarrayfromdartspoints.h"
#include "assemblejsonfromdartstournamentmodels.h"
#include "AssembleDartsTournamentsFromJsonArray.h"
#include "assemblemultiattemptscoresbyjson.h"
#include "assemblejsonbydartsscoremodels.h"
#include "getdartsscoreindexesbymodel.h"
#include "getordereddartsscoremodels.h"
#include "countscoresbytournamentandhint.h"
#include "getdartsscoremodelsbytournamentid.h"
#include "getdartsscoremodelsbyplayerid.h"
#include "getdartsscoremodelsbyroundindex.h"
#include "setdartsmodelhint.h"

class DartsModelsServiceBuilder :
        public IModelsServiceBuilder<IDartsModelsService>
{

    // IDartsServiceBuilder interface
public:
    IDartsModelsService *buildModelsService() const override;
};

#endif // DARTSTOURNAMNETMODELSERVICEBUILDER_H
