#include "createstatmodel.h"
#include <DartsStatistics/Contracts/Players/Models/playerstats.h>

PlayerStats CreateStatModel::create(const QString &name) const
{
    return {.name  = name};
}
