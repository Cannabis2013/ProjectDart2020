#ifndef DARTSSCORE_H
#define DARTSSCORE_H

#include "idartsscore.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

namespace DartsScoreMultiAttemptContext
{
    class DartsScore : public IDartsScore
    {
    public:
        static DartsScore* createInstance()
        {
            return new DartsScore;
        }
        static DartsScore* createInstance(const QByteArray& json)
        {
            auto document = QJsonDocument::fromJson(json);
            auto jsonObject = document.object();
            return new DartsScore(jsonObject);
        }

        static DartsScore* createInstance(const QJsonObject& jsonObject)
        {
            return new DartsScore(jsonObject);
        }

        int score() const override
        {
            return _score;
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
        void setScore(int newScore)
        {
            _score = newScore;
        }
    private:
        DartsScore()
        {}
        DartsScore(const QJsonObject& jsonObject)
        {
            _score = jsonObject.value("score").toInt();
            _playerId = QUuid::fromString(jsonObject.value("playerId").toString());
            _playerName = jsonObject.value("playerName").toString();
        }
        int _score;
        QUuid _playerId;
        QString _playerName;
    };
};

#endif // DARTSSCORE_H
