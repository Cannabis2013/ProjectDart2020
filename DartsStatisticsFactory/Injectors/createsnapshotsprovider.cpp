#include "createsnapshotsprovider.h"

#include <DartsStatistics/Inputs/snapshotsservices.h>

#include <DartsStatisticsFactory/Inputs/createinput.h>
#include <DartsStatisticsFactory/Inputs/inputsdb.h>

SnapShotsServices *CreateSnapShotsProvider::create()
{
        auto services = new SnapShotsServices;
        services->setSnapShotsDb(new InputsDb);
        services->setCreateSnapShot(new CreateInput);
        return services;
}
