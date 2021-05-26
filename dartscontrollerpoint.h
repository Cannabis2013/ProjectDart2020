#ifndef DARTSPOINT_H
#define DARTSPOINT_H

#include "idartscontrollerpoint.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

namespace DartsPointSingleAttemptContext
{
    class DartsControllerPoint : public IDartsControllerPoint<QUuid,QString,QByteArray>
    {
    public:
        static DartsControllerPoint* createInstance()
        {
            return new DartsControllerPoint();
        }
        static DartsControllerPoint* fromJson(const QByteArray& json)
        {
            auto document = QJsonDocument::fromJson(json);
            auto jsonObject = document.object();
            return new DartsControllerPoint(jsonObject);
        }
        static DartsControllerPoint* fromJsonObject(const QJsonObject& jsonObject)
        {
            return new DartsControllerPoint(jsonObject);
        }
        QUuid playerId() const override
        {
            return _playerId;
        }
        void setPlayerId(const QUuid &newPlayerId)
        {
            _playerId = newPlayerId;
        }
        QString playerName() const override
        {
            return _playerName;
        }
        void setPlayerName(const QString &newPlayerName) override
        {
            _playerName = newPlayerName;
        }
        int accumulatedScore() const override
        {
            return _accumulatedScore;
        }
        void setAccumulatedScore(const int& accumulatedScore) override
        {
            _accumulatedScore = accumulatedScore;
        }
        int point() const override
        {
            return _point;
        }
        void setPoint(int newPoint)
        {
            _point = newPoint;
        }
        int modKeyCode() const override
        {
            return _modKeyCode;
        }
        void setModKeyCode(int newModKeyCode)
        {
            _modKeyCode = newModKeyCode;
        }
        QByteArray toJson() const override
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
        DartsControllerPoint()
        {}
        DartsControllerPoint(const QJsonObject& jsonObject)
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
