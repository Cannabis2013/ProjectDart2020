#include "dartsstatistics.h"
#include <qvector.h>

void DartsStatistics::initPlayers(const ByteArray &ba)
{
    auto players = convertToPlayers()->convert(ba);
    addPlayersToMemory()->add(players);
}

void DartsStatistics::initInputs(const ByteArray &ba)
{
    auto inputs = convertToInputs()->convert(ba);
    addInputsToMemory()->add(inputs);
}

void DartsStatistics::reset()
{
    resetPlayers()->reset();
    resetInputs()->reset();
}

void DartsStatistics::clear()
{
    playerServices()->playersDb()->clear();
    inputServices()->inputsDb()->clear();
}

void DartsStatistics::update(const QString &name, const int &point, const int &score, const int &modCode)
{
    /*
     * Todo:
     *  - Calculate statistics data
     *  - Update player model
     */
}

QByteArray DartsStatistics::createReport(const QString &name) const
{
}

void DartsStatistics::take(const QString &name)
{
}
