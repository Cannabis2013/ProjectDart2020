#ifndef WINNERINFO_H
#define WINNERINFO_H

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qstring.h>


class WinnerInfo
{
public:
        WinnerInfo(const QString& name) : _name(name)
        {}

        QByteArray toJson(){
                QJsonObject jsonObj;
                jsonObj["winnername"] = _name;
                jsonObj["type"] = "winnerInfo";
                auto jsonDoc = new QJsonDocument(jsonObj);
                return jsonDoc->toJson();
        }
private:
        QString _name;
};

#endif // WINNERINFO_H
