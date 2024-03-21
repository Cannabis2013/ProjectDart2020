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
                turnsLimit = jsonObj.value("playersCount").toInt();
                turnIndex = jsonObj.value("turnIndex").toInt();
                turnId = jsonObj.value("totalTurns").toInt();
                roundIndex = jsonObj.value("roundIndex").toInt();
                throwIndex = jsonObj.value("throwIndex").toInt();
                throwCount = jsonObj.value("currentThrows").toInt();
                availableThrows = jsonObj.value("totalThrows").toInt();
        }

        DartsIndex(const int& count)
        {
                turnsLimit = count;
        }

        DartsIndex()
        {
        }

        QByteArray toJson() const
        {
                QJsonObject jsonObj;
                jsonObj["playersCount"] = turnsLimit;
                jsonObj["turnIndex"] = turnIndex;
                jsonObj["throwIndex"] = throwIndex;
                jsonObj["totalTurns"] = turnId;
                jsonObj["roundIndex"] = roundIndex;
                jsonObj["currentThrows"] = throwCount;
                jsonObj["totalThrows"] = availableThrows;
                auto jsonDoc = new QJsonDocument(jsonObj);
                return jsonDoc->toJson(QJsonDocument::Compact);
        }

        int turnsLimit = 0;
        int turnIndex = 0;
        int turnId = 0;
        int roundIndex = 0;
        int throwIndex = 0;
        int throwCount = 0;
        int availableThrows = 0;
};

#endif // DARTINDEX_H
