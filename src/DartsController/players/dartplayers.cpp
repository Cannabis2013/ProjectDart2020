#include "dartplayers.h"
#include "src/FileIO/filejsonio.h"
#include <QJsonArray>
#include <QJsonValue>
#include <qjsondocument.h>

DartPlayers::DartPlayers()
{}

void DartPlayers::initPlayers(const QStringList& names)
{
        _playerNames = names;
        saveToFile();
}

void DartPlayers::initPlayers()
{
        initFromFile();
}

QString DartPlayers::name(int index) const
{
        return _playerNames.at(index);
}

int DartPlayers::playersCount()
{
        return _playerNames.count();
}

QStringList DartPlayers::names() const
{
        return _playerNames;
}

void DartPlayers::initFromFile()
{
        FileJsonIO jsonIO("players.dat");
        auto jsonDoc = QJsonDocument::fromJson(jsonIO.read());
        if(!jsonDoc.isArray())
                return;
        for (auto val : jsonDoc.array())
                _playerNames.append(val.toString(""));
}

void DartPlayers::saveToFile()
{
        FileJsonIO jsonIO("players.dat");
        QJsonArray jsonArr;
        for (auto& name : qAsConst(_playerNames))
                jsonArr.append(name);
        auto jsonDoc = new QJsonDocument(jsonArr);
        jsonIO.write(jsonDoc->toJson());
}
