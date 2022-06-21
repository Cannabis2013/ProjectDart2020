#include "dartsinputinjector.h"
#include <DartsModelsContext/Contracts/dartsmodelsservices.h>
#include <DartsModelsContext/LocalDartsModelsContext/InputServices/countdartsinputs.h>
#include <DartsModelsContext/LocalDartsModelsContext/InputServices/dartsinputbuilder.h>
#include <DartsModelsContext/LocalDartsModelsContext/InputServices/dartsinputconverter.h>
#include <DartsModelsContext/LocalDartsModelsContext/InputServices/dartsinputdb.h>
#include <DartsModelsContext/LocalDartsModelsContext/InputServices/getdartsinputs.h>
#include <DartsModelsContext/LocalDartsModelsContext/InputServices/removedartsinputs.h>
#include <DartsModelsContext/LocalDartsModelsContext/InputServices/sortdartsinputs.h>
#include <DartsModelsContext/LocalDartsModelsContext/InputServices/sortdartsinputsbyindexes.h>
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
