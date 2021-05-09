#ifndef SCORESJSONASSEMBLERSERVICE_H
#define SCORESJSONASSEMBLERSERVICE_H

#include "iunaryservice.h"
#include "iplayerscoreservice.h"
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>

namespace ScoresAssemblerContext{
    typedef IPlayerScoreService<QUuid,
                             QString,QVector<int>,
                             QVector<QString>> ScoreController;
}

class DartsScoresJsonAssemblerService : public
        IUnaryService<const ScoresAssemblerContext::ScoreController*,QByteArray>
{
public:


    // IUnary interface
public:
    QByteArray service(const ScoresAssemblerContext::ScoreController* scoreService) override
    {
        auto count = scoreService->playersCount();
        QJsonObject jsonObject;
        QJsonArray playerScoreEntities;
        for (int i = 0; i < count; ++i) {
            QJsonObject obj;
            auto playerName = scoreService->playerNameByIndex(i);
            auto score = scoreService->playerScore(i);
            obj["playerName"] = playerName;
            obj["playerScore"] = score;
            playerScoreEntities.append(obj);
        };
        jsonObject["entities"] = playerScoreEntities;
        auto document = QJsonDocument(jsonObject);
        auto json = document.toJson();
        return json;
    }
};

#endif // SCORESJSONASSEMBLERSERVICE_H
