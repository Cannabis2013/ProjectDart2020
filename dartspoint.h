#ifndef DARTSPOINT_H
#define DARTSPOINT_H

#include <qjsondocument.h>
#include <qjsonobject.h>

namespace DartsPointSingleAttemptContext
{
    class DartsPoint
    {
    public:
        static DartsPoint* createInstance()
        {
            return new DartsPoint;
        }
        static DartsPoint* fromJson(const QByteArray& json)
        {
            auto document = QJsonDocument::fromJson(json);
            auto jsonObject = document.object();
            return new DartsPoint(jsonObject);
        }
        static DartsPoint* fromJsonObject(const QJsonObject& jsonObject)
        {
            return new DartsPoint(jsonObject);
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
        int accumulatedScore() const
        {
            return _accumulatedScore;
        }
        void setAccumulatedScore(const int& accumulatedScore)
        {
            _accumulatedScore = accumulatedScore;
        }
        int point() const
        {
            return _point;
        }
        void setPoint(int newPoint)
        {
            _point = newPoint;
        }
        int modKeyCode() const
        {
            return _modKeyCode;
        }
        void setModKeyCode(int newModKeyCode)
        {
            _modKeyCode = newModKeyCode;
        }
        QByteArray toJson() const
        {
            QJsonObject jsonobject;
            jsonobject["point"] = _point;
            jsonobject["modKeyCode"] = _modKeyCode;
            jsonobject["playerId"] = _playerId.toString(QUuid::WithoutBraces);
            jsonobject["playerName"] = _playerName;
            jsonobject["totalScore"] = _accumulatedScore;
            auto document = QJsonDocument(jsonobject);
            auto json = document.toJson();
            return json;
        }
    private:
        DartsPoint()
        {}
        DartsPoint(const QJsonObject& jsonObject)
        {
            _point = jsonObject.value("point").toInt();
            _modKeyCode = jsonObject.value("modKeyCode").toInt();
            _playerId = QUuid::fromString(jsonObject.value("playerId").toString());
            _playerName = jsonObject.value("playerName").toString();
        }
        int _point;
        int _modKeyCode;
        int _accumulatedScore;
        QUuid _playerId;
        QString _playerName;
    };
}
#endif // DARTSPOINT_H
