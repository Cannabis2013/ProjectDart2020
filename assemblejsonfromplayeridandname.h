#ifndef ASSEMBLEJSONFROMPLAYERIDANDNAME_H
#define ASSEMBLEJSONFROMPLAYERIDANDNAME_H

#include "ibinaryservice.h"
#include <quuid.h>
#include <qjsondocument.h>
#include <qjsonobject.h>

class AssembleJsonFromPlayerNameAndId :
        public IBinaryService<const QUuid&,const QString&,QByteArray>
{
public:


    // IBinaryService interface
public:
    QByteArray service(const QUuid& playerId,const QString& playerName) override
    {
        QJsonObject jsonObject;
        jsonObject["playerId"] = playerId.toString(QUuid::WithoutBraces);
        jsonObject["playerName"] = playerName;
        auto json = QJsonDocument(jsonObject).toJson();
        return json;
    }
};

#endif // ASSEMBLEJSONFROMPLAYERIDANDNAME_H
