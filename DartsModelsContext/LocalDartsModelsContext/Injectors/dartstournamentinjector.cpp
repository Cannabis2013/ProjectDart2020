#include "dartstournamentinjector.h"
#include <DartsModelsContext/Contracts/Tournament/tournamentservices.h>
#include <DartsModelsContext/Contracts/dartsmodelsservices.h>
#include <DartsModelsContext/LocalDartsModelsContext/TournamentServices/getdartstournamentids.h>
#include <DartsModelsContext/LocalDartsModelsContext/TournamentServices/dartsbuilder.h>
#include <DartsModelsContext/LocalDartsModelsContext/TournamentServices/dartsjsonconverter.h>
#include <DartsModelsContext/LocalDartsModelsContext/TournamentServices/dartsmetamodelbuilder.h>
#include <DartsModelsContext/LocalDartsModelsContext/TournamentServices/dartsverifyconsistency.h>
#include <DartsModelsContext/LocalDartsModelsContext/TournamentServices/dartwinnermodelbuilder.h>
#include <DartsModelsContext/LocalDartsModelsContext/TournamentServices/getdartstournamentfromdb.h>
#include <DartsModelsContext/LocalDartsModelsContext/TournamentsDbServices/dartsdbcontext.h>
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
