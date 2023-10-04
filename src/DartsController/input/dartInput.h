#ifndef DARTINPUT_H
#define DARTINPUT_H

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>

class DartInput
{
public:
        DartInput() {}

        static DartInput fromJson(QByteArray arr){
                auto jsonDoc = QJsonDocument::fromJson(arr);
                auto jsonObj = jsonDoc.object();
                DartInput input;
                input._point =  jsonObj.value("point").toInt(-1);
                input._mod = jsonObj.value("mod").toString("");
                input._playerName = jsonObj.value("player").toString("");
                input._turnIndex = jsonObj.value("index").toInt();
                return input;
        }

        static DartInput fromJson(const QJsonObject &jsonObj){
                DartInput input;
                input._point =  jsonObj.value("point").toInt(-1);
                input._mod = jsonObj.value("mod").toString("");
                input._playerName = jsonObj.value("player").toString("");
                input._turnIndex = jsonObj.value("index").toInt();
                return input;
        }

        QJsonObject toJsonObject(){
                QJsonObject jsonObj;
                jsonObj["point"] = QString::number(_point);
                jsonObj["mod"] = _mod;
                jsonObj["player"] = _playerName;
                jsonObj["index"] = _turnIndex;
                return jsonObj;
        }

        static DartInput nullified(DartInput input){
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
        int _point = -1;
        QString _mod = "S";
        int _turnIndex;
        QString _playerName;
};

#endif // DARTINPUT_H
