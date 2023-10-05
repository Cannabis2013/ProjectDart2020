#ifndef DARTSINTERNALINPUT_H
#define DARTSINTERNALINPUT_H

#include <qbytearray.h>
#include <qjsonobject.h>
#include <QJsonDocument>

class DartsInternalInput{
public:
        static DartsInternalInput fromJson(QByteArray arr){
                auto jsonDoc = QJsonDocument::fromJson(arr);
                auto jsonObj = jsonDoc.object();
                DartsInternalInput input;
                input._point =  jsonObj.value("point").toInt(-1);
                input._mod = jsonObj.value("mod").toString("");
                input._playerName = jsonObj.value("player").toString("");
                input._turnIndex = jsonObj.value("index").toInt();
                return input;
        }

        static DartsInternalInput fromJson(const QJsonObject &jsonObj){
                DartsInternalInput input;
                input._point =  jsonObj.value("point").toInt(-1);
                input._mod = jsonObj.value("mod").toString("");
                input._playerName = jsonObj.value("player").toString("");
                input._turnIndex = jsonObj.value("index").toInt();
                return input;
        }

        DartsInternalInput(const QString &mod, const int &point)
                : _point(point),_mod(mod){}

        QJsonObject toJsonObject(){
                QJsonObject jsonObj;
                jsonObj["point"] = QString::number(_point);
                jsonObj["mod"] = _mod;
                jsonObj["player"] = _playerName;
                jsonObj["index"] = _turnIndex;
                return jsonObj;
        }

        static DartsInternalInput nullified(DartsInternalInput input){
                input._point = 0;
                return input;
        }

        int point() const
        {
                return _point;
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

        int turnIndex() const { return _turnIndex; }

        void setTurnIndex(int newTurnIndex) { _turnIndex = newTurnIndex; }

private:
        DartsInternalInput(){}
        int _point = -1;
        QString _mod = "S";
        int _turnIndex;
        QString _playerName;
};

#endif // DARTSINTERNALINPUT_H
