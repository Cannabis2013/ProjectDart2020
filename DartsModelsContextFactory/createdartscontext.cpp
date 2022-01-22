#include "createdartscontext.h"
#include "Injectors/dartsinputinjector.h"
#include "Injectors/dartstournamentinjector.h"
#include "Injectors/dartsindexinjector.h"
#include "Injectors/localpersistenceinjector.h"
#include "TournamentsDbSLAs/persistenceslas.h"
#include "dartscontext.h"
CreateDartsContext::CreateDartsContext()
{
    inputInjector = new DartsInputInjector;
    tournamentInjector = new DartsTournamentInjector;
    indexInjector = new DartsIndexInjector;
    persInjector = new LocalPersistenceInjector;
}

AbsDartsCtx *CreateDartsContext::localJson(AbsPlaCtx *playersContext) const
{
    auto context = new DartsContext(playersContext);
    tournamentInjector->injectServices(context);
    inputInjector->injectServices(context);
    indexInjector->injectServices(context);
    persInjector->inject(context);
    fetchContext(context);
    return context;
}

void CreateDartsContext::fetchContext(AbsDartsCtx *context) const
{
    context->loadFromStorage()->load(context->dartsDbCtx(),context->jsonToTournaments(),
                                     context->dartsConverter(),context->ioDevice());
    context->loadFromStorage()->load(context->inputsDb(),context->jsonToInputs(),
                                     context->inputConverter(),context->ioDevice());
}
