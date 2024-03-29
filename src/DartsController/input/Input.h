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
                _throwIndex = jsonObj.value("index").toInt();
        }

        Input(const QString &mod, const int &point)
                : _point(point),_mod(mod){}

        Input(){}

        QJsonObject toJsonObject(){
                QJsonObject jsonObj;
                jsonObj["point"] = _point;
                jsonObj["mod"] = _mod;
                jsonObj["player"] = _playerName;
                jsonObj["index"] = _throwIndex;
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
        void setPlayerName(const QString& newPlayerName)
        {
                _playerName = newPlayerName;
        }

        int throwIndex() const { return _throwIndex; }

        void setThrowIndex(int newTurnIndex) { _throwIndex = newTurnIndex; }

private:
        int _point = 0;
        QString _mod = "S";
        int _throwIndex;
        QString _playerName;
};

#endif // DARTSINTERNALINPUT_H
