#ifndef DARTINPUT_H
#define DARTINPUT_H

#include "DartsInternalInput.h"
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <qbytearray.h>

class DartsInput
{
public:
        DartsInput() {}

        static DartsInput fromJson(QByteArray arr){
                auto jsonDoc = QJsonDocument::fromJson(arr);
                auto jsonObj = jsonDoc.object();
                DartsInput input;
                input._mod = jsonObj.value("mod").toString("");
                input._point =  jsonObj.value("point").toInt(-1);
                return input;
        }

        static DartsInput fromInternal(const DartsInternalInput &internal){
                DartsInput input;
                input._mod = internal.mod();
                input._point = internal.point();
                return input;
        }

        DartsInternalInput toInternal(){
                DartsInternalInput internal(_mod,_point);
                return internal;
        }

        QJsonObject toJsonObject(){
                QJsonObject jsonObj;
                jsonObj["point"] = QString::number(_point);
                jsonObj["mod"] = _mod;
                return jsonObj;
        }

        static DartsInput nullified(DartsInput input){
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
private:
        int _point = -1;
        QString _mod = "S";
};

#endif // DARTINPUT_H
