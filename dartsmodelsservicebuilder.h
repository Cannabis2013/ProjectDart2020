#ifndef DARTSTOURNAMNETMODELSERVICEBUILDER_H
#define DARTSTOURNAMNETMODELSERVICEBUILDER_H

#include "dartsmodelsservice.h"
#include "imodelsservicebuilder.h"
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
#include "sortplayerinputsbypredicate.h"
#include "setdartsmodelhint.h"
#include "getdartstournamentbyindexservice.h"
#include "getdartstournamentbyid.h"
#include "getdartsinputmodelbyid.h"
#include "setdartsinputhintservice.h"
#include "deletetournamentsbyindexesservice.h"
#include "removemodelsfromdbcontext.h"
#include "dartspointlessthanpredicate.h"
#include "dartsscorelessthanpredicate.h"
#include "dartsinputsfilterservice.h"

class DartsModelsServiceBuilder :
        public IModelsServiceBuilder<IDartsModelsService>
{

    // IDartsServiceBuilder interface
public:
    IDartsModelsService *buildModelsService() const override;
};

#endif // DARTSTOURNAMNETMODELSERVICEBUILDER_H
