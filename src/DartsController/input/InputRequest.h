#ifndef DARTINPUT_H
#define DARTINPUT_H

#include "Input.h"

class InputRequest
{
public:
        InputRequest() {}
        InputRequest(const QByteArray &json){
                auto jsonDoc = QJsonDocument::fromJson(json);
                auto jsonObj = jsonDoc.object();
                _mod = jsonObj.value("mod").toString("");
                _point =  jsonObj.value("point").toInt(-1);
        }

        InputRequest(const Input &internal){
                _mod = internal.mod();
                _point = internal.point();
        }

        Input toInput() const{
            Input internal(_mod,_point);
                return internal;
        }

        Input toNullified() const{
                return Input(_mod,0);
        }

        QJsonObject toJsonObject() const{
                QJsonObject jsonObj;
                jsonObj["point"] = QString::number(_point);
                jsonObj["mod"] = _mod;
                return jsonObj;
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
