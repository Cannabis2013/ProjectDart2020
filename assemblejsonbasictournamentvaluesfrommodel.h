#ifndef ASSEMBLEJSONFROMDARTSTOURNAMENT_H
#define ASSEMBLEJSONFROMDARTSTOURNAMENT_H

#include "ibinaryservice.h"
#include "idartstournament.h"
#include <quuid.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "iplayermodelsservice.h"
#include "iplayermodel.h"

class AddPlayerNamesToDartsTournamentJson :
        public IBinaryService<const QByteArray&,
                              const QVector<QString>&,
                              QByteArray>
{
public:
    QByteArray service(const QByteArray& json,
                       const QVector<QString>& playerNames) override
    {
        auto document = QJsonDocument::fromJson(json);
        auto jsonObject = document.object();
        auto arr = jsonObject.value("assignedPlayerIds").toArray();
        QJsonArray namesArr;
        for (const auto& playerName : playerNames)
            namesArr << playerName;
        jsonObject["assignedPlayerNames"] = namesArr;
        auto newJSon = QJsonDocument(jsonObject).toJson();
        return newJSon;
    }
};



#endif // ASSEMBLEJSONFROMDARTSTOURNAMENT_H
