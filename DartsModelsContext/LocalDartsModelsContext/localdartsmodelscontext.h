#ifndef CREATEDARTSCONTEXT_H
#define CREATEDARTSCONTEXT_H

#include <qobject.h>

class InjectDartsRoutines;
class DartsPlayerInjector;
class DartsModelsServices;
class DartsIndexInjector;
class DartsTournamentInjector;
class DartsInputInjector;
class AbstractDartsContext;
class AbstractPlayerContext;

class LocalDartsModelsContext
{
public:
        LocalDartsModelsContext();
        AbstractDartsContext *createInstance(AbstractPlayerContext *playersContext) const;
private:
        void injectServices(DartsModelsServices *context) const;
        void fetchContext(DartsModelsServices *context) const;
        DartsTournamentInjector *tournamentInjector;
        DartsInputInjector *inputInjector;
        DartsIndexInjector *indexInjector;
        DartsPlayerInjector *injectPlaServices;
        InjectDartsRoutines *injectRoutineServices;
};
#endif // DARTSMODELSSERVICEWITHJSONDB_H
