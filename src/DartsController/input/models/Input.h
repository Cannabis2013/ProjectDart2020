#ifndef DARTSINTERNALINPUT_H
#define DARTSINTERNALINPUT_H

#include <qbytearray.h>
#include <qjsonobject.h>
#include <QJsonDocument>

class Input{
public:
        Input(const QJsonObject &jsonObj){
                _point =  jsonObj.value("point").toInt(-1);
                _mod = jsonObj.value("mod").toString("");
                _playerName = jsonObj.value("player").toString("");
                _turnId = jsonObj.value("turnId").toInt();
                _throwId = jsonObj.value("throwId").toInt();
        }

        Input(const QString& mod, const int& point, const QString& name, const int& throwIndex)
            : _point(point)
            , _mod(mod)
            , _playerName(name)
            , _throwId(throwIndex)
        {
        }

        Input(){}

        QJsonObject toJsonObject(){
                QJsonObject jsonObj;
                jsonObj["point"] = _point;
                jsonObj["mod"] = _mod;
                jsonObj["player"] = _playerName;
                jsonObj["turnId"] = _turnId;
                jsonObj["throwId"] = _throwId;
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
        
        int throwId() const
        {
                return _throwId;
        }

        int turnId() const
        {
                return _turnId;
        }

private:
        int _point = 0;
        QString _mod = "S";
        QString _playerName;
        int _turnId;
        int _throwId;
};

#endif // DARTSINTERNALINPUT_H
