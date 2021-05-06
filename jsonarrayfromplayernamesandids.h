#ifndef JSONARRAYFROMPLAYERSERVICE_H
#define JSONARRAYFROMPLAYERSERVICE_H

#include "ibinaryservice.h"
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>

class JsonArrayFromPlayerNamesAndIds :
        public IBinaryService<const QVector<QUuid>&,const QVector<QString>&, QByteArray>
{
public:
    QByteArray service(const QVector<QUuid>& playerIds, const QVector<QString>& playerNames) override
    {
        QJsonArray playerJsonArray;
        for (int i = 0; i < playerIds.count(); ++i) {
            QJsonObject playerJsonObject;
            playerJsonObject["playerId"] = playerIds.at(i).toString(QUuid::WithoutBraces);
            playerJsonObject["playerName"] = playerNames.at(i);
            playerJsonArray << playerJsonObject;
        }
        auto json = QJsonDocument(playerJsonArray).toJson();
        return json;
    }
};

#endif // JSONARRAYFROMPLAYERSERVICE_H
