#ifndef GETWINNERIDBYJSON_H
#define GETWINNERIDBYJSON_H

#include "iunaryservice.h"
#include <quuid.h>

#include <qjsondocument.h>
#include <qjsonobject.h>

class GetWinnerIdByJson : public
        IUnaryService<const QByteArray&, QUuid>
{

    // IBinaryService interface
public:
    QUuid service(const QByteArray& json) override
    {
        auto document = QJsonDocument::fromJson(json);
        auto jsonObject = document.object();
        auto winnerStringId = jsonObject.value("winnerId").toString();
        auto id = QUuid::fromString(winnerStringId);
        return id;
    }
};

#endif // GETWINNERIDBYJSON_H
