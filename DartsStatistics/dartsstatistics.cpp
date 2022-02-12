#include "dartsstatistics.h"
#include <qvector.h>

void DartsStatistics::addPlayer(const QString &name)
{
    auto statsModel = statisticServices()->createStatistic()->create(name);
    statisticServices()->statModels()->add(statsModel);
}

void DartsStatistics::addSnapShot(const QString &name, const int &score, const int &modCode)
{
    auto input = snapShotServices()->createSnapShot()->create(name,score,modCode);
    routines()->updatePlayerStatistics()->update(input);
    snapShotServices()->snapShotsDb()->add(input);
}

void DartsStatistics::reset()
{
    routines()->resetContext()->reset();
}

void DartsStatistics::clear()
{
    statisticServices()->statModels()->clear();
    snapShotServices()->snapShotsDb()->clear();
}

QByteArray DartsStatistics::createReport(const QString &name) const
{
    return routines()->createReport()->create(name);
}

bool DartsStatistics::removeSnapShot(const QString &name)
{
    return routines()->removeSnapShot()->remove(name);
}
