#include "localpersistenceinjector.h"
#include "TournamentsDbSLAs/persistenceservices.h"
#include "FileIOServices/filejsonio.h"
#include "DbServices/loadfromstorage.h"
#include "DbServices/savetostorage.h"
#include "SLAs/dmcservices.h"
void LocalPersistenceInjector::inject(DMCServices *context)
{
    auto persServices = new PersistenceServices;
    persServices->setIoDevice(new FileJsonIO("DartsData"));
    persServices->setLoadFromStorage(new LoadFromStorage);
    persServices->setSaveToStorage(new SaveToStorage);
    context->setPersistenceServices(persServices);
}
