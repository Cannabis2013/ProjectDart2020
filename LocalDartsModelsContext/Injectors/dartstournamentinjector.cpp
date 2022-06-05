#include "dartstournamentinjector.h"
#include <DartsModelsContext/TournamentsSLAs/tournamentservices.h>
#include <DartsModelsContext/SLAs/dartsmodelsservices.h>
#include <LocalDartsModelsContext/TournamentServices/getdartstournamentids.h>
#include <LocalDartsModelsContext/TournamentServices/dartsbuilder.h>
#include <LocalDartsModelsContext/TournamentServices/dartsjsonconverter.h>
#include <LocalDartsModelsContext/TournamentServices/dartsmetamodelbuilder.h>
#include <LocalDartsModelsContext/TournamentServices/dartsverifyconsistency.h>
#include <LocalDartsModelsContext/TournamentServices/dartwinnermodelbuilder.h>
#include <LocalDartsModelsContext/TournamentServices/getdartstournamentfromdb.h>
#include <LocalDartsModelsContext/TournamentsDbServices/dartsdbcontext.h>
#include <Shared/filejsonio.h>


void DartsTournamentInjector::injectServices(DartsModelsServices *context)
{
    auto dbContext = assembleDbContext();
    auto tnmServices = new TournamentServices;
    tnmServices->setDartsConverter(new DartsJsonConverter);
    tnmServices->setDartsDbCtx(dbContext);
    tnmServices->setWinnerInfoBuilder(new DartWinnerModelBuilder);
    tnmServices->setCreateMeta(new DartsMetaModelBuilder);
    tnmServices->setGetTournament(new GetDartsTournamentFromDb);
    tnmServices->setTournamentBuilder(new DartsBuilder);
    tnmServices->setGetTournamentIds(new GetDartsIds);
    tnmServices->setVerifyConsistency(new DartsVerifyConsistency);
    context->setTournamentServices(tnmServices);
}

IDbContext<IModel<QUuid> > *DartsTournamentInjector::assembleDbContext()
{
        auto ioDevice = new FileJsonIO("DartsData");
        auto converter = new DartsJsonConverter;
        auto dbContext = new DartsDbContext("DartsTournamentModels",ioDevice,converter);
        return dbContext;
}
