#ifndef ASSEMBLEDARTSSCOREBYJSON_H
#define ASSEMBLEDARTSSCOREBYJSON_H

#include "iunaryservice.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include "qjsonarray.h"
#include "dartsscore.h"

namespace DartsScoreMultiAttemptContext {
    class AssembleDartsScoreByJson : public
            IUnaryService<const QByteArray&,
                          const IDartsScore*>
    {
    public:
        const IDartsScore* service(const QByteArray& json) override
        {
            auto document = QJsonDocument::fromJson(json);
            auto obj = document.object();
            auto dartsScoreModel = new DartsScore();
            dartsScoreModel->setScore(obj.value("score").toInt());
            auto playerStringId = obj.value("playerId").toString();
            dartsScoreModel->setPlayerId(QUuid::fromString(playerStringId));
            return dartsScoreModel;
        }
    };
};



#endif // ASSEMBLEDARTSSCOREBYJSON_H
