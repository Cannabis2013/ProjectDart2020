#ifndef DARTINDEX_H
#define DARTINDEX_H

#include "qjsonobject.h"
#include <qbytearray.h>
#include <qjsondocument.h>

struct DartsIndex
{
        int playersCount;
        int playerIndex;
        int legIndex;
        int turnIndex = 0;
        int totalTurns = 0;

        static DartsIndex fromJson(const QByteArray &json){
                DartsIndex index;
                auto jsonDoc = QJsonDocument::fromJson(json);
                if(!jsonDoc.isObject())
                        return DartsIndex();
                auto jsonObj = jsonDoc.object();
                index.playersCount = jsonObj.value("playersCount").toInt();
                index.playerIndex = jsonObj.value("playerIndex").toInt();
                index.legIndex = jsonObj.value("legIndex").toInt();
                index.turnIndex = jsonObj.value("turnIndex").toInt();
                index.totalTurns = jsonObj.value("totalTurns").toInt();
                return index;
        }

        QByteArray toJson() const{
                QJsonObject jsonObj;
                jsonObj["playersCount"] = playersCount;
                jsonObj["playerIndex"] = playerIndex;
                jsonObj["legIndex"] = legIndex;
                jsonObj["turnIndex"] = turnIndex;
                jsonObj["totalTurns"] = totalTurns;
                auto jsonDoc = new QJsonDocument(jsonObj);
                return jsonDoc->toJson(QJsonDocument::Compact);
        }
};

#endif // DARTINDEX_H
