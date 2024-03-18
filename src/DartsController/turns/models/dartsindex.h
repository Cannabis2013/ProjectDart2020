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
                currentTurnIndex = jsonObj.value("currentTurnIndex").toInt();
                currentThrowId = jsonObj.value("currentThrowId").toInt();
                totalTurns = jsonObj.value("totalTurns").toInt();
                currentThrowIndex = jsonObj.value("currentThowIndex").toInt();
                currentThrows = jsonObj.value("currentThrows").toInt();
                totalThrows = jsonObj.value("totalThrows").toInt();
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
                jsonObj["currentTurnIndex"] = currentTurnIndex;
                jsonObj["totalTurns"] = totalTurns;
                jsonObj["currentThowIndex"] = currentThrowIndex;
                jsonObj["currentThrowId"] = currentThrowId;
                jsonObj["currentThrows"] = currentThrows;
                jsonObj["totalThrows"] = totalThrows;
                auto jsonDoc = new QJsonDocument(jsonObj);
                return jsonDoc->toJson(QJsonDocument::Compact);
        }

        int playersCount = 0;
        int currentTurnIndex = 0;
        int currentThrowId = 0;
        int totalTurns = 0;
        int currentThrowIndex = 0;
        int currentThrows = 0;
        int totalThrows = 0;
};

#endif // DARTINDEX_H
