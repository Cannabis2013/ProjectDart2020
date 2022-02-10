#include "jsontostatsmodel.h"
#include <qjsonobject.h>
#include "Players/Models/imirrorsdb.h"
#include "Players/Models/imirrorsdb.h"

CurrentStat JsonToStatsModel::convert(const Json &json) const
{
    CurrentStat stats;
    stats.name = json.value("name").toString();
    return stats;
}
