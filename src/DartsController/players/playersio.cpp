#include "playersio.h"
#include "qjsonarray.h"
#include "src/FileIO/filejsonio.h"

#include <QJsonDocument>

PlayersIO::PlayersIO(const QString& filePath)
{
        _filePath = filePath;
}

QList<DartsPlayer> PlayersIO::initFromFile()
{
        QList<DartsPlayer> players;
        FileJsonIO jsonIO(_filePath);
        auto jsonDoc = QJsonDocument::fromJson(jsonIO.read());
        if(!jsonDoc.isArray())
                return QList<DartsPlayer>();
        const auto localArray =  jsonDoc.array();
        for (const auto& jsonObj : localArray)
                players << DartsPlayer(jsonObj.toObject());
        return players;
}

bool PlayersIO::saveToFile(const QList<DartsPlayer>& players)
{
        FileJsonIO jsonIO(_filePath);
        QJsonArray jsonArr;
        for (auto& player : players)
                jsonArr.append(player.jsonObject());
        auto jsonDoc = new QJsonDocument(jsonArr);
        return jsonIO.write(jsonDoc->toJson());
}
