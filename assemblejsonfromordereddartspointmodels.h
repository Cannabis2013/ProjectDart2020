#ifndef ASSEMBLEJSONFROMORDEREDDARTSPOINTMODELS_H
#define ASSEMBLEJSONFROMORDEREDDARTSPOINTMODELS_H

#include "ibinaryservice.h"
#include "idartspointinput.h"
#include <quuid.h>
#include <qvector.h>
#include "iplayermodelsservice.h"
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "iplayermodel.h"

namespace DartsModelsContext {
    class AssembleJsonFromOrderedDartsPointModels :
            public IBinaryService<const QVector<const IDartsInput*>&,
                                  const IPlayerModelsService*,const QByteArray>
    {
    public:
        const QByteArray service(const QVector<const IDartsInput*>& orderedDartsPoints,
                                 const IPlayerModelsService* playerModelsService) override
        {
            QJsonArray arr;
            for (const auto& playerInput : orderedDartsPoints) {
                auto dartsPoint = dynamic_cast<const IDartsPointInput*>(playerInput);
                QJsonObject jsonObject;
                jsonObject["playerId"] = dartsPoint->playerId().toString(QUuid::WithoutBraces);
                jsonObject["playerName"] = getPlayerNameFromPlayerId(dartsPoint->playerId(),playerModelsService);
                jsonObject["point"] = dartsPoint->point();
                jsonObject["score"] = dartsPoint->score();
                jsonObject["modKeyCode"] = dartsPoint->modKeyCode();
                arr << jsonObject;
            }
            auto json = QJsonDocument(arr).toJson();
            return json;
        }
    private:
        QString getPlayerNameFromPlayerId(const QUuid& playerId,
                                          const IPlayerModelsService* playerModelsService)
        {
            auto playerName = playerModelsService->playerNameById(playerId);
            return playerName;
        }
    };
}


#endif // ASSEMBLEJSONFROMORDEREDDARTSPOINTMODELS_H
