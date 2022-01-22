#include "localpersistenceinjector.h"
#include "TournamentsDbSLAs/persistenceslas.h"
#include "FileIOServices/filejsonio.h"
#include "DbServices/loadfromstorage.h"
#include "DbServices/savetostorage.h"
void LocalPersistenceInjector::inject(PersistenceSLAs *context)
{
    context->setIoDevice(new FileJsonIO("DartsData"));
    context->setLoadFromStorage(new LoadFromStorage);
    context->setSaveToStorage(new SaveToStorage);
}
