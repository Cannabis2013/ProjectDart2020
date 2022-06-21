#include "createstatmodel.h"
#include <DartsStatistics/Contracts/Players/Models/currentstats.h>

CurrentStat CreateStatModel::create(const QString &name) const
{
    return {.name  = name};
}
