#include "dartsinputinjector.h"
#include "SLAs/dartsmodelsservices.h"
#include "InputSLAs/dartsinputservices.h"
#include "InputServices/countdartsinputs.h"
#include "InputServices/dartsinputbuilder.h"
#include "InputServices/dartsinputconverter.h"
#include "InputServices/dartsinputdb.h"
#include "InputServices/getdartsinputs.h"
#include "InputServices/removedartsinputs.h"
#include "InputServices/sortdartsinputs.h"
#include "InputServices/sortdartsinputsbyindexes.h"

#include <FileIOServices/filejsonio.h>

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
