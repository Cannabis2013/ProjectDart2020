#include "dartsplayers.h"
#include "src/players/services/pdcchampions.h"
#include "src/FileIO/filejsonio.h"
#include <QJsonArray>
#include <QJsonValue>
#include <qjsondocument.h>

DartsPlayers::DartsPlayers(const QString& filepath)
    : _storagePath(filepath)
{
}

void DartsPlayers::init()
{
        _players = PdcChampions().generate();
}

void DartsPlayers::initFromFile()
{
        QList<DartsPlayer> players;
        auto jsonDoc = FileJsonIO(_storagePath).readAsJson();
        if (!jsonDoc.isArray())
                return;
        const auto localArray = jsonDoc.array();
        for (const auto& jsonObj : localArray)
                players << DartsPlayer(jsonObj.toObject());
        _players = players;
}

void DartsPlayers::reset()
{
        PdcChampions generator;
        _players = generator.generate();
}

QList<DartsPlayer>& DartsPlayers::all()
{
        return _players;
}

bool DartsPlayers::saveState()
{
        QJsonArray jsonArr;
        for (auto& player : _players)
                jsonArr.append(player.jsonObject());
        return FileJsonIO(_storagePath).writeAsJson(jsonArr);
}
