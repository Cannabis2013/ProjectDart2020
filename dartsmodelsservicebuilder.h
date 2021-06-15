#ifndef DARTSTOURNAMNETMODELSERVICEBUILDER_H
#define DARTSTOURNAMNETMODELSERVICEBUILDER_H

#include "dartsmodelsservice.h"
#include "imodelsservicebuilder.h"
#include "tournamentjsondb.h"
#include "dartspointjsondbservice.h"
#include "dartsscorejsondb.h"
#include "dartssingleattemptindexesbuilder.h"
#include "assembledartspointsfromjson.h"
#include "assemblejsonarrayfromdartspoints.h"
#include "assemblejsonfromdartstournamentmodels.h"
#include "AssembleDartsTournamentsFromJsonArray.h"
#include "assemblemultiattemptscoresbyjson.h"
#include "assemblejsonbydartsscoremodels.h"
#include "getdartsscoreindexesbymodel.h"
#include "inputmodelssortservice.h"
#include "setdartsmodelhint.h"
#include "getdartstournamentbyindexservice.h"
#include "getdartstournamentbyid.h"
#include "dartsinputmodelhintservice.h"
#include "deletetournamentsbyindexesservice.h"
#include "sortdartspointinputsbyindexes.h"
#include "dartsscorelessthanpredicate.h"
#include "dartsinputsfilterservice.h"
#include "assignplayeridstodartstournamentmodel.h"
class DartsModelsServiceBuilder :
        public IModelsServiceBuilder<IDartsModelsService>
{

    // IDartsServiceBuilder interface
public:
    IDartsModelsService *buildModelsService() const override;
};

#endif // DARTSTOURNAMNETMODELSERVICEBUILDER_H
