#ifndef DARTSINTERNALINPUT_H
#define DARTSINTERNALINPUT_H

#include <qbytearray.h>
#include <qjsonobject.h>
#include <QJsonDocument>

class DartsInput {
public:
        DartsInput(const QJsonObject& jsonObj)
        {
                _point =  jsonObj.value("point").toInt(-1);
                _mod = jsonObj.value("mod").toString("");
                _playerName = jsonObj.value("player").toString("");
                _roundIndex = jsonObj.value("roundIndex").toInt();
                _turnId = jsonObj.value("turnId").toInt();
        }

        DartsInput(const QString& mod, const int& point)
            : _point(point)
            , _mod(mod)
        {
        }

        DartsInput() { }

        QJsonObject toJsonObject(){
                QJsonObject jsonObj;
                jsonObj["point"] = _point;
                jsonObj["mod"] = _mod;
                jsonObj["player"] = _playerName;
                jsonObj["roundIndex"] = _roundIndex;
                jsonObj["turnId"] = _turnId;
                return jsonObj;
        }

        int point() const
        {
                return _point;
        }

        void setPoint(int point)
        {
                _point = point;
        }

        QString mod() const
        {
                return _mod;
        }

        QString playerName() const
        {
                return _playerName;
        }

        int roundIndex() const
        {
                return _roundIndex;
        }

        int turnId() const
        {
                return _turnId;
        }

        void setTurnId(int newTurnId)
        {
                _turnId = newTurnId;
        }

        void setRoundIndex(int newRoundIndex)
        {
                _roundIndex = newRoundIndex;
        }

        void setPlayerName(const QString& newPlayerName)
        {
                _playerName = newPlayerName;
        }

private:
        int _point = 0;
        QString _mod = "S";
        QString _playerName;
        int _turnId;
        int _roundIndex;
};
#endif // DARTSINTERNALINPUT_H
