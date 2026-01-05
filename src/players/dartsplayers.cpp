#include "dartsplayers.h"
#include <QJsonArray>
#include <QJsonValue>
#include <QRandomGenerator>
#include "src/FileIO/filejsonio.h"
#include <qjsondocument.h>

QStringList &DartsPlayers::all()
{
    return _playerNames;
}

void DartsPlayers::init(const QStringList &playerNames)
{
    _playerNames = playerNames;
}

void DartsPlayers::initFromFile()
{    
    auto jsonDoc = FileJsonIO(_storagePath).readAsJson();
    if (!jsonDoc.isArray())
        return;

    _playerNames.clear();

    const auto arr = jsonDoc.array();
    for (const auto &jsonObj : arr)
        _playerNames << jsonObj.toString();
}

bool DartsPlayers::saveState()
{
    QJsonArray arr;
    for (auto &name : _playerNames)
        arr.append(name);
    return FileJsonIO(_storagePath).write(arr);
}

void DartsPlayers::reset()
{
    _playerNames.clear();
}
