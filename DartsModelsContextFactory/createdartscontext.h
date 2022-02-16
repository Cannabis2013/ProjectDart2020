#ifndef CREATEDARTSCONTEXT_H
#define CREATEDARTSCONTEXT_H
#include <qobject.h>
class InjectDartsRoutines;
class DartsPlayerInjector;
class DartsModelsServices;
class LocalPersistenceInjector;
class DartsIndexInjector;
class DartsTournamentInjector;
class DartsInputInjector;
class AbsDartsCtx;
class AbsPlaCtx;
#ifdef DartsMdFactLib
    #define DartsFactoryExport Q_DECL_EXPORT
#else
    #define DartsFactoryExport Q_DECL_IMPORT
#endif
class DartsFactoryExport CreateDartsContext
{
public:
    CreateDartsContext();
    AbsDartsCtx *localJson(AbsPlaCtx *playersContext) const;
private:
    void injectServices(DartsModelsServices *context) const;
    void fetchContext(AbsDartsCtx *context) const;
    DartsTournamentInjector *tournamentInjector;
    DartsInputInjector *inputInjector;
    DartsIndexInjector *indexInjector;
    LocalPersistenceInjector *persInjector;
    DartsPlayerInjector *injectPlaServices;
    InjectDartsRoutines *injectRoutineServices;
};
#endif // DARTSMODELSSERVICEWITHJSONDB_H
