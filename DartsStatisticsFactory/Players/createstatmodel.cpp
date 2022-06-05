#include "createstatmodel.h"
#include <DartsStatistics/Players/Models/currentstats.h>

CurrentStat CreateStatModel::create(const QString &name) const
{
    return {.name  = name};
}
