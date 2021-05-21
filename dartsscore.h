#ifndef DARTSSCORE_H
#define DARTSSCORE_H

#include <qjsondocument.h>
#include <qjsonobject.h>

namespace DartsScoreMultiAttemptContext
{
    class DartsScore
    {
    public:
        static DartsScore* createInstance()
        {
            return new DartsScore;
        }
        static DartsScore* fromJson(const QByteArray& json)
        {
            auto document = QJsonDocument::fromJson(json);
            auto jsonObject = document.object();
            return new DartsScore(jsonObject);
        }

        static DartsScore* fromJsonObject(const QJsonObject& jsonObject)
        {
            return new DartsScore(jsonObject);
        }

        int score() const
        {
            return _score;
        }
        QUuid playerId() const
        {
            return _playerId;
        }
        QString playerName() const
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
        virtual QByteArray toJson() const
        {
            QJsonObject jsonobject;
            jsonobject["score"] = _score;
            jsonobject["playerId"] = _playerId.toString(QUuid::WithoutBraces);
            jsonobject["playerName"] = _playerName;
            jsonobject["totalScore"] = _accumulatedScore;
            auto document = QJsonDocument(jsonobject);
            auto json = document.toJson();
            return json;
        }
        int accumulatedScore() const
        {
            return _accumulatedScore;
        }
        void setAccumulatedScore(const int& accumulatedScore)
        {
            _accumulatedScore = accumulatedScore;
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
        int _accumulatedScore;
        QUuid _playerId;
        QString _playerName;
    };
};

#endif // DARTSSCORE_H
