#include "controllervalues.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <qjsonarray.h>

ControllerValues::ControllerValues(const QByteArray& json)
{
        auto jsonDoc = QJsonDocument::fromJson(json);
        auto rootObj = jsonDoc.object();
        auto playersArr = rootObj["players"].toArray();
        for (const auto& obj : playersArr) {
                auto jsonObj = obj.toObject();
                _players.append(DartsPlayer::fromJson(jsonObj));
        }
        _initialScore = rootObj["initialScore"].toInt(501);
        _mode = rootObj["gameMode"].toInt(1);
}

int ControllerValues::playersCount() const
{
        return _players.size();
}

QList<DartsPlayer> ControllerValues::players() const
{
        return _players;
}

int ControllerValues::initialScore() const
{
        return _initialScore;
}

int ControllerValues::mode() const
{
        return _mode;
}
