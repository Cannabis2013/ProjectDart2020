#ifndef DARTSPLAYER_H
#define DARTSPLAYER_H

#include "idartsplayer.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

namespace DartsScoreControllerContext
{
    class DartsPlayer : public IDartsPlayer<QUuid,QString>
    {
    public:
        static DartsPlayer* createInstance()
        {
            return new DartsPlayer();
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
