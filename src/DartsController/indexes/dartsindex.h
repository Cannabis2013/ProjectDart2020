#ifndef DARTINDEX_H
#define DARTINDEX_H

#include "qjsonobject.h"
#include <qbytearray.h>
#include <qjsondocument.h>

class DartsIndex {
public:
        DartsIndex(const QByteArray& json)
        {
                auto jsonDoc = QJsonDocument::fromJson(json);
                auto jsonObj = jsonDoc.object();
                playersCount = jsonObj.value("playersCount").toInt();
                playerIndex = jsonObj.value("playerIndex").toInt();
                turnIndex = jsonObj.value("turnIndex").toInt();
                throwIndex = jsonObj.value("throwIndex").toInt();
                totalTurns = jsonObj.value("totalTurns").toInt();
        }

        DartsIndex(const int& count)
        {
                playersCount = count;
        }

        DartsIndex()
        {
        }

        QByteArray toJson() const
        {
                QJsonObject jsonObj;
                jsonObj["playersCount"] = playersCount;
                jsonObj["playerIndex"] = playerIndex;
                jsonObj["turnIndex"] = turnIndex;
                jsonObj["throwIndex"] = throwIndex;
                jsonObj["totalTurns"] = totalTurns;
                auto jsonDoc = new QJsonDocument(jsonObj);
                return jsonDoc->toJson(QJsonDocument::Compact);
        }

        int playersCount = 0;
        int playerIndex = 0;
        int turnIndex = 0;
        int throwIndex = 0;
        int totalTurns = 0;
};

#endif // DARTINDEX_H
