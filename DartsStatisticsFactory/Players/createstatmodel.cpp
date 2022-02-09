#include "createstatmodel.h"

#include "Players/Models/imirrorsdb.h"

CurrentStat CreateStatModel::create(const QString &name) const
{
    return {.name  = name};
}
