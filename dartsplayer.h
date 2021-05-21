#ifndef DARTSPLAYER_H
#define DARTSPLAYER_H

#include "idartsplayer.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

namespace DartsScoreMultiAttemptContext
{
    class DartsPlayer : public IDartsPlayer
    {
    public:
        DartsPlayer(const QUuid& id, const QString& name):
            _playerId(id),_playerName(name)
        {}
        DartsPlayer()
        {}
        static const DartsPlayer* fromJson(const QByteArray& json)
        {
            auto document = QJsonDocument::fromJson(json);
            auto jsonObject = document.object();
            auto playerStringId = jsonObject.value("playerId").toString();
            auto playerId = QUuid::fromString(playerStringId);
            auto playerName = jsonObject.value("playerName").toString();
            auto dartsPlayerModel = new DartsPlayer(playerId,playerName);
            return dartsPlayerModel;
        }
        static const DartsPlayer* fromJsonObject(const QJsonObject& jsonObject)
        {
            auto playerStringId = jsonObject.value("playerId").toString();
            auto playerId = QUuid::fromString(playerStringId);
            auto playerName = jsonObject.value("playerName").toString();
            auto dartsModel = new DartsPlayer(playerId,playerName);
            return dartsModel;
        }
        QUuid playerId() const override
        {
            return _playerId;
        }
        QString playerName() const override
        {
            return _playerName;
        }
        void setPlayerId(const QUuid &newPlayerId)
        {
            _playerId = newPlayerId;
        }
        void setPlayerName(const QString &newPlayerName)
        {
            _playerName = newPlayerName;
        }
        QByteArray toJson() const override
        {
            QJsonObject jsonObject;
            jsonObject["playerId"] = _playerId.toString(QUuid::WithoutBraces);
            jsonObject["playerName"] = _playerName;
            auto document = QJsonDocument(jsonObject);
            auto json = document.toJson();
            return json;
        }
    private:
        QUuid _playerId;
        QString _playerName;
    };
}

#endif // DARTSPLAYER_H
