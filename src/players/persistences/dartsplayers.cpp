#include <QJsonArray>
#include <QJsonValue>
#include <QRandomGenerator>
#include "dartsplayers.h"
#include "src/FileIO/filejsonio.h"
#include <qjsondocument.h>

DartsPlayers::DartsPlayers(const QString& filepath)
    : _storagePath(filepath)
{
    _available = std::initializer_list<DartsPlayer>{{"Max van Gerwen"},
                                                    {"Lars Skovsen"},
                                                    {"Laila Suhr"},
                                                    {"Hjalte Grønnegård"},
                                                    {"Rasmus Clemmesen"},
                                                    {"Jes"},
                                                    {"Simone"},
                                                    {"Bjarke Grønnegård"},
                                                    {"Ewelina"},
                                                    {"Benjamin Weiss"},
                                                    {"Loise Juhler"},
                                                    {"Storm Weiss"}};
}

void DartsPlayers::init(const QStringList &names)
{
    _selectedNames = names;
    fillPlayers();
}

void DartsPlayers::initFromFile()
{
    QList<DartsPlayer> players;
    auto jsonDoc = FileJsonIO(_storagePath).readAsJson();
    if (!jsonDoc.isArray())
        return;
    const auto arr = jsonDoc.array();
    for (const auto &jsonObj : arr)
      players << DartsPlayer(jsonObj.toObject());
    _players = players;
}

QList<DartsPlayer>& DartsPlayers::all()
{
    return _players;
}

bool DartsPlayers::saveState()
{
    QJsonArray arr;
    for (auto &player : _players)
        arr.append(player.jsonObject());
    return FileJsonIO(_storagePath).write(arr);
}

void DartsPlayers::fillPlayers()
{
    _players.clear();
    for (const auto &name : std::as_const(_selectedNames)) {
        for (const auto &player : std::as_const(_available)) {
            if (player.name() == name)
                _players.append(player);
        }
    }
}

QList<DartsPlayer> &DartsPlayers::available()
{
    return _available;
}

int DartsPlayers::count()
{
    return _players.count();
}

void DartsPlayers::reset()
{
    fillPlayers();
}
