#include "dartsinputinjector.h"
#include <DartsModelsContext/SLAs/dartsmodelsservices.h>
#include <LocalDartsModelsContext/InputServices/countdartsinputs.h>
#include <LocalDartsModelsContext/InputServices/dartsinputbuilder.h>
#include <LocalDartsModelsContext/InputServices/dartsinputconverter.h>
#include <LocalDartsModelsContext/InputServices/dartsinputdb.h>
#include <LocalDartsModelsContext/InputServices/getdartsinputs.h>
#include <LocalDartsModelsContext/InputServices/removedartsinputs.h>
#include <LocalDartsModelsContext/InputServices/sortdartsinputs.h>
#include <LocalDartsModelsContext/InputServices/sortdartsinputsbyindexes.h>
#include <Shared/filejsonio.h>

void DartsInputInjector::injectServices(DartsModelsServices *context)
{
    auto dbContext = assembleDbContext();
    auto iptServices = new DartsInputServices;
    iptServices->setInputConverter(new DartsInputConverter);
    iptServices->setRemoveInputsFromDb(new RemoveDartsInputs);
    iptServices->setSortInputsByIndexes(new SortDartsInputsByIndexes);
    iptServices->setInputBuilder(new DartsInputBuilder);
    iptServices->setSortInputs(new SortDartsInputs);
    iptServices->setCountInputs(new CountDartsInputs);
    iptServices->setInputsDb(dbContext);
    iptServices->setGetInputsFromDb(new GetDartsInputs);
    context->setInputServices(iptServices);

}

DartsInputDb *DartsInputInjector::assembleDbContext()
{
    auto ioDevice = new FileJsonIO("DartsData");
    auto converter = new DartsInputConverter;
    auto dbContext = new DartsInputDb("DartsInputModels",ioDevice,converter);
    return dbContext;
}
