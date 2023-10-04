#ifndef DARTINDEX_H
#define DARTINDEX_H

#include "qjsonobject.h"
#include <qbytearray.h>
#include <qjsondocument.h>

struct DartIndex
{
        int playerIndex;
        int legIndex;
        int turnIndex;
        int totalTurns;

        static DartIndex fromJson(const QByteArray &json){
                DartIndex index;
                auto jsonDoc = QJsonDocument::fromJson(json);
                if(!jsonDoc.isObject())
                        return DartIndex();
                auto jsonObj = jsonDoc.object();
                index.playerIndex = jsonObj.value("playerIndex").toInt();
                index.legIndex = jsonObj.value("legIndex").toInt();
                index.turnIndex = jsonObj.value("turnIndex").toInt();
                index.totalTurns = jsonObj.value("totalTurns").toInt();
                return index;
        }

        QByteArray toJson(){
                QJsonObject jsonObj;
                jsonObj["playerIndex"] = playerIndex;
                jsonObj["legIndex"] = legIndex;
                jsonObj["turnIndex"] = turnIndex;
                jsonObj["totalTurns"] = totalTurns;
                auto jsonDoc = new QJsonDocument(jsonObj);
                return jsonDoc->toJson(QJsonDocument::Compact);
        }
};

#endif // DARTINDEX_H
