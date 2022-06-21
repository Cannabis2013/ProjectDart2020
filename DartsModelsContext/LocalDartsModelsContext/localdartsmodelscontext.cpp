#include "localdartsmodelscontext.h"
#include "dartscontext.h"
#include "Injectors/dartsinputinjector.h"
#include "Injectors/dartstournamentinjector.h"
#include "Injectors/dartsindexinjector.h"
#include "Injectors/dartsplayerinjector.h"
#include "Injectors/injectdartsroutines.h"

LocalDartsModelsContext::LocalDartsModelsContext()
{
        tournamentInjector = new DartsTournamentInjector;
        inputInjector = new DartsInputInjector;
        indexInjector = new DartsIndexInjector;
        injectPlaServices = new DartsPlayerInjector;
        injectRoutineServices = new InjectDartsRoutines();
}

AbstractDartsContext *LocalDartsModelsContext::createInstance(AbstractPlayerContext *playersContext) const
{
        auto context = new DartsContext;
        context->setPlayersContext(playersContext);
        injectServices(context);
        injectRoutineServices->inject(context);
        fetchContext(context);
        return context;
}

void LocalDartsModelsContext::injectServices(DartsModelsServices *context) const
{
        tournamentInjector->injectServices(context);
        inputInjector->injectServices(context);
        indexInjector->injectServices(context);
        injectPlaServices->inject(context);
}

void LocalDartsModelsContext::fetchContext(DartsModelsServices *context) const
{
        auto dartsDb = context->tournamentServices()->dbContext();
        auto inputsDb = context->inputServices()->dbContext();
        dartsDb->fetch();
        inputsDb->fetch();
}
