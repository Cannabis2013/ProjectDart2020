#include "dartspersist.h"
#include "SLAs/dmcservices.h"
DartsPersist::DartsPersist(DMCServices *services):_services(services){}

bool DartsPersist::persistTournamentsChanges()
{
    return persistTournaments();
}

bool DartsPersist::persistInputChanges()
{
    return persistInputs();
}

bool DartsPersist::persistAllChanges()
{
    persistTournaments();
    return persistInputs();
}

bool DartsPersist::persistTournaments()
{
    auto tnmServices = _services->tournamentServices();
    auto tnmsConverter = tnmServices->tournamentsToJson();
    auto tnmConverter = tnmServices->dartsConverter();
    auto dbContext = tnmServices->dartsDbCtx();
    return persist(dbContext,tnmsConverter,tnmConverter);
}

bool DartsPersist::persistInputs()
{
    auto iptServices = _services->inputServices();
    auto iptsConverter = iptServices->inputModelsToJson();
    auto iptConverter = iptServices->inputConverter();
    auto dbContext = iptServices->inputsDb();
    return persist(dbContext,iptsConverter,iptConverter);
}

bool DartsPersist::persist(DbContext *dbContext, ModelsConverter *convertModels, ModelConverter *convertModel)
{
    auto persServices = _services->persistenceServices();
    auto saveToStorage = persServices->saveToStorage();
    auto ioDevice = persServices->ioDevice();
    auto models = dbContext->models();
    return saveToStorage->save(models,convertModels,convertModel,ioDevice);
}
