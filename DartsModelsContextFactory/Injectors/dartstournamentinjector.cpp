#include "dartstournamentinjector.h"
#include "TournamentServices/GetDartsTournamentIds.h"
#include "TournamentServices/dartsbuilder.h"
#include "TournamentServices/dartsjsonconverter.h"
#include "TournamentServices/dartsmetamodelbuilder.h"
#include "TournamentServices/dartwinnermodelbuilder.h"
#include "TournamentServices/getdartstournamentfromdb.h"
#include "TournamentsDbServices/dartsdbcontext.h"
#include "SLAs/dartsmodelsservices.h"
#include "TournamentServices/dartsverifyconsistency.h"
#include "FileIOServices/filejsonio.h"

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
