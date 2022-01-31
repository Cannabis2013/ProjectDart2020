#include "dartstournamentinjector.h"
#include "TournamentServices/GetDartsTournamentIds.h"
#include "TournamentServices/dartsbuilder.h"
#include "TournamentServices/dartsjsonconverter.h"
#include "TournamentServices/dartsmetamodelbuilder.h"
#include "TournamentServices/dartwinnermodelbuilder.h"
#include "TournamentServices/getdartstournamentfromdb.h"
#include "TournamentServices/jsontodartsmodels.h"
#include "TournamentsDbServices/dartsdbcontext.h"
#include "DbServices/convertdartsmodels.h"
#include "SLAs/dmcservices.h"

void DartsTournamentInjector::injectServices(DMCServices *context)
{
    auto tnmServices = new DartsServices;
    tnmServices->setDartsConverter(new DartsJsonConverter);
    tnmServices->setDartsDbCtx(new DartsDbContext);
    tnmServices->setTournamentsToJson(new ConvertDartsModels);
    tnmServices->setWinnerInfoBuilder(new DartWinnerModelBuilder);
    tnmServices->setCreateMeta(new DartsMetaModelBuilder);
    tnmServices->setGetTournament(new GetDartsTournamentFromDb);
    tnmServices->setTournamentBuilder(new DartsBuilder);
    tnmServices->setGetTournamentIds(new GetDartsIds);
    tnmServices->setJsonToTournaments(new JsonToDartsModels);
    context->setTournamentServices(tnmServices);
}
