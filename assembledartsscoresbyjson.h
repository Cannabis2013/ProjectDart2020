#ifndef ASSEMBLEDARTSSCORESBYJSON_H
#define ASSEMBLEDARTSSCORESBYJSON_H

#include "iunaryservice.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include "qjsonarray.h"
#include "dartsscore.h"

namespace DartsScoreMultiAttemptContext{
    class AssembleDartsScoresByJson : public
            IUnaryService<const QByteArray&,
                          QVector<const IDartsScore*>>
    {
    public:
        QVector<const IDartsScore*> service(const QByteArray& json) override
        {
            auto document = QJsonDocument::fromJson(json);
            auto scoreData = document.array();
            QVector<const IDartsScore*> extendedValueModels;
            for (const auto &jsonVal : scoreData) {
                auto obj = jsonVal.toObject();
                auto dartsScoreModel = new DartsScore();
                dartsScoreModel->setScore(obj.value("score").toInt());
                auto playerStringId = obj.value("playerId").toString();
                dartsScoreModel->setPlayerId(QUuid::fromString(playerStringId));
                extendedValueModels << dartsScoreModel;
            }
            return extendedValueModels;
        }
    };
}


#endif // ASSEMBLEDARTSSCORESBYJSON_H
