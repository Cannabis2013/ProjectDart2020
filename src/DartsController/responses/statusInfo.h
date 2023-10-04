#ifndef STATUSINFO_H
#define STATUSINFO_H

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qstring.h>


class StatusInfo
{
public:
        StatusInfo(const QString& statusMessage) : _statusMessage(statusMessage)
        {}

        QByteArray toJson(){
                QJsonObject jsonObj;
                jsonObj["status"] = _statusMessage;
                jsonObj["type"] = "status";
                auto jsonDoc = new QJsonDocument(jsonObj);
                return jsonDoc->toJson(QJsonDocument::Compact);
        }
private:
        QString _statusMessage;
};

#endif // STATUSINFO_H
