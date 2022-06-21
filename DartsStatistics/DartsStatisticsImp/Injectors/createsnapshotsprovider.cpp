#include "createsnapshotsprovider.h"

#include <DartsStatistics/Contracts/Inputs/snapshotsservices.h>
#include <DartsStatistics/DartsStatisticsImp/Inputs/createinput.h>
#include <DartsStatistics/DartsStatisticsImp/Inputs/inputsdb.h>

SnapShotsServices *CreateSnapShotsProvider::create()
{
        auto services = new SnapShotsServices;
        services->setSnapShotsDb(new InputsDb);
        services->setCreateSnapShot(new CreateInput);
        return services;
}
