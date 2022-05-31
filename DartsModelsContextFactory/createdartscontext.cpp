#include "createdartscontext.h"
#include "Injectors/dartsinputinjector.h"
#include "Injectors/dartstournamentinjector.h"
#include "Injectors/dartsindexinjector.h"
#include "dartscontext.h"
#include "Injectors/dartsplayerinjector.h"
#include "Injectors/injectdartsroutines.h"

CreateDartsContext::CreateDartsContext()
{
        tournamentInjector = new DartsTournamentInjector;
        inputInjector = new DartsInputInjector;
        indexInjector = new DartsIndexInjector;
        injectPlaServices = new DartsPlayerInjector;
        injectRoutineServices = new InjectDartsRoutines();
}

AbstractDartsContext *CreateDartsContext::localJson(AbsPlaCtx *playersContext) const
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
    injectPlaServices->inject(context);
}

void CreateDartsContext::fetchContext(DartsModelsServices *context) const
{
    auto dartsDb = context->tournamentServices()->dbContext();
    auto inputsDb = context->inputServices()->dbContext();
    dartsDb->fetch();
    inputsDb->fetch();
}
