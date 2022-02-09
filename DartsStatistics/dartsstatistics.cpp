#include "dartsstatistics.h"
#include <qvector.h>

void DartsStatistics::initStatisticModels(const ByteArray &ba)
{
    auto players = routines()->byteArrayToStats()->convert(ba);
    statisticServices()->statModels()->add(players);
}

void DartsStatistics::initSnapShots(const ByteArray &ba)
{
    auto inputs = routines()->byteArrayToSnapShots()->convert(ba);
    routines()->updatePlayerStatistics()->update(inputs);
    snapShotServices()->snapShots()->add(inputs);
}

void DartsStatistics::reset()
{
    routines()->resetContext()->reset();
}

void DartsStatistics::clear()
{
    statisticServices()->statModels()->clear();
    snapShotServices()->snapShots()->clear();
}

void DartsStatistics::update(const QString &name, const int &score, const int &modCode)
{
    auto input = snapShotServices()->createSnapShot()->create(name,score,modCode);
    routines()->updatePlayerStatistics()->update(input);
}

QByteArray DartsStatistics::createReport(const QString &name) const
{
    return routines()->createReport()->create(name);
}

bool DartsStatistics::removeSnapShot(const QString &name)
{
    return routines()->removeSnapShot()->remove(name);
}
