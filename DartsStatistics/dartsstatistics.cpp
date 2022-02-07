#include "dartsstatistics.h"
#include <qvector.h>

void DartsStatistics::initPlayers(const ByteArray &ba)
{
    auto players = routines()->byteArrayToStats()->convert(ba);
    currentStatsServices()->statsDb()->add(players);
}

void DartsStatistics::initInputs(const ByteArray &ba)
{
    auto inputs = routines()->convertToInputs()->convert(ba);
    routines()->updateCurrentStats()->update(inputs);
    inputServices()->inputsDb()->add(inputs);
}

void DartsStatistics::reset()
{
    routines()->resetContext()->reset();
}

void DartsStatistics::clear()
{
    currentStatsServices()->statsDb()->clear();
    inputServices()->inputsDb()->clear();
}

void DartsStatistics::update(const QString &name, const int &score, const int &modCode)
{
    auto input = inputServices()->createInput()->create(name,score,modCode);
    routines()->updateCurrentStats()->update(input);
}

QByteArray DartsStatistics::createReport(const QString &name) const
{
    return routines()->createReport()->create(name);
}

bool DartsStatistics::takeInput(const QString &name)
{
    return routines()->removeInputFromDb()->remove(name);
}
