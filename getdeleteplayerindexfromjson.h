#ifndef GETDELETEPLAYERINDEXFROMJSON_H
#define GETDELETEPLAYERINDEXFROMJSON_H

#include "iunaryservice.h"
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>

class GetDeletePlayerIndexFromJson :
        public IUnaryService<const QByteArray&,int>
{
public:
    int service(const QByteArray& json) override
    {
        auto jsonObject = QJsonDocument::fromJson(json).object();
        auto index = jsonObject.value("index").toInt();
        return index;
    }
};

#endif // GETDELETEPLAYERINDEXFROMJSON_H
