#ifndef APPENDSTRINGTOJSON_H
#define APPENDSTRINGTOJSON_H

#include "ibinary.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <QJsonArray>

class AppendStringToJsonService : public
        IBinary<const QByteArray&,const QString&,QByteArray>
{
public:
    QByteArray service(const QByteArray& json, const QString& string) override
    {
        auto document = QJsonDocument::fromJson(json);
        auto jsonObject = document.object();
        jsonObject["playerName"] = string;
        auto newDocument = QJsonDocument(jsonObject);
        auto updatedJson = newDocument.toJson();
        return updatedJson;
    }
};

#endif // APPENDSTRINGTOJSON_H
