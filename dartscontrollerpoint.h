#ifndef DARTSPOINT_H
#define DARTSPOINT_H

#include "idartscontrollerpoint.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

namespace DartsPointControllerContext
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
        void setPlayerId(const QUuid &newPlayerId) override
        {
            _playerId = newPlayerId;
        }
        int totalScore() const override
        {
            return _accumulatedScore;
        }
        void setTotalScore(const int& accumulatedScore) override
        {
            _accumulatedScore = accumulatedScore;
        }
        int point() const override
        {
            return _point;
        }
        void setPoint(const int& newPoint) override
        {
            _point = newPoint;
        }
        int score() const override
        {
            return _score;
        }
        void setScore(const int &score) override
        {
            _score = score;
        }
        int modKeyCode() const override
        {
            return _modKeyCode;
        }
        void setModKeyCode(const int& newModKeyCode) override
        {
            _modKeyCode = newModKeyCode;
        }
        QByteArray toJson() const override
        {
            QJsonObject jsonobject;
            jsonobject["point"] = _point;
            jsonobject["modKeyCode"] = _modKeyCode;
            jsonobject["playerId"] = _playerId.toString(QUuid::WithoutBraces);
            jsonobject["score"] = _score;
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
            _score = jsonObject.value("score").toInt();
        }
        int _point;
        int _modKeyCode;
        int _score;
        int _accumulatedScore;
        QUuid _playerId;
    };
}
#endif // DARTSPOINT_H
