#include "dartsplayers.h"
#include <QJsonArray>
#include <QJsonValue>
#include <qjsondocument.h>

DartsPlayers::DartsPlayers(IDartsIndexes* indexes)
{
        _indexes = indexes;
        _playersIO = new PlayersIO("players.dat");
}

void DartsPlayers::initPlayers(const QStringList& names)
{
        _names = names;
}

void DartsPlayers::initPlayers()
{
        _names = _playersIO->initFromFile();
}

QString DartsPlayers::name(int index) const
{
        return _names.at(index);
}

QString DartsPlayers::name() const
{
        auto playerIndex = _indexes->index().playerIndex();
        if(playerIndex >= _names.count())
                return QString();
        return _names.at(playerIndex);
}

int DartsPlayers::playersCount()
{
        return _names.count();
}

QStringList DartsPlayers::names() const
{
        return _names;
}

bool DartsPlayers::saveState()
{
        return _playersIO->saveToFile(_names);
}
