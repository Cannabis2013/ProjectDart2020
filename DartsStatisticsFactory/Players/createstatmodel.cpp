#include "createstatmodel.h"

#include "Players/Models/currentstats.h"

CurrentStat CreateStatModel::create(const QString &name) const
{
    return {.name  = name};
}
