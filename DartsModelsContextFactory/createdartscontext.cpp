#include "createdartscontext.h"
#include "Injectors/dartsinputinjector.h"
#include "Injectors/dartstournamentinjector.h"
#include "Injectors/dartsindexinjector.h"
#include "Injectors/localpersistenceinjector.h"
#include "TournamentsDbSLAs/persistenceservices.h"
#include "dartscontext.h"
#include "Injectors/dartsplayerinjector.h"
#include "Injectors/injectdartsroutines.h"
CreateDartsContext::CreateDartsContext()
{
    tournamentInjector = new DartsTournamentInjector;
    inputInjector = new DartsInputInjector;
    indexInjector = new DartsIndexInjector;
    persInjector = new LocalPersistenceInjector;
    injectPlaServices = new DartsPlayerInjector;
    injectRoutineServices = new InjectDartsRoutines();
}

AbsDartsCtx *CreateDartsContext::localJson(AbsPlaCtx *playersContext) const
{
    auto context = new DartsContext;
    context->setPlayersContext(playersContext);
    injectServices(context);
    injectRoutineServices->inject(context);
    fetchContext(context);
    return context;
}

void CreateDartsContext::injectServices(DartsModelsServices *context) const
{
    tournamentInjector->injectServices(context);
    inputInjector->injectServices(context);
    indexInjector->injectServices(context);
    persInjector->inject(context);
    injectPlaServices->inject(context);
}

void CreateDartsContext::fetchContext(DartsModelsServices *context) const
{
    auto dartsDb = context->tournamentServices()->dartsDbCtx();
    auto jsonToTnms = context->tournamentServices()->jsonToTournaments();
    auto jsonToTnm = context->tournamentServices()->dartsConverter();
    auto ioDevice = context->persistenceServices()->ioDevice();
    auto iptsDb = context->inputServices()->inputsDb();
    auto jsonToIpts = context->inputServices()->jsonToInputs();
    auto jsonToIpt = context->inputServices()->inputConverter();
    context->persistenceServices()->loadFromStorage()->load(dartsDb,jsonToTnms, jsonToTnm,ioDevice);
    context->persistenceServices()->loadFromStorage()->load(iptsDb,jsonToIpts, jsonToIpt,ioDevice);
}
