#include "playerreport.h"
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include "src/players/persistences/idartsplayers.h"
#include "src/servicecollection.h"
#include "src/turns/models/dartsturnindex.h"
#include "src/turns/persistences/idartsindexes.h"

PlayerReport::PlayerReport(ServiceCollection* services)
    : _services(services)
{
}

QString PlayerReport::current() const
{
    auto playerIndex = _services->indexes->index().playerIndex();
    auto players = _services->players->all();
    return players.at(playerIndex);
}

QStringList PlayerReport::all() const
{
    return _services->players->all();
}

int PlayerReport::playerIndex(const QString &name) const
{
    return _services->players->all().indexOf(name);
}
