#ifndef BUILDDARTSPOINTINDEXES_H
#define BUILDDARTSPOINTINDEXES_H

#include "iunaryservice.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include "dartssingleattemptindexes.h"

namespace DartsPointSingleAttemptContext {
    typedef IUnaryService<const QByteArray&, const IDartsSingleAttemptIndexes*> IBuildIndexesService;
    class BuildDartsSingleAttemptIndexesByJson : public IBuildIndexesService
    {
    public:
        const IDartsSingleAttemptIndexes* service(const QByteArray& json) override
        {
            auto document = QJsonDocument::fromJson(json);
            auto jsonObject = document.object();
            auto totalTurns = jsonObject.value("totalTurns").toInt();
            auto turnIndex = jsonObject.value("turns").toInt();
            auto roundIndex = jsonObject.value("roundIndex").toInt();
            auto setIndex = jsonObject.value("setIndex").toInt();
            auto attemptIndex = jsonObject.value("attemptIndex").toInt();
            auto model = DartsSingleAttemptIndexes::createInstance()
                    ->setTotalTurns(totalTurns)
                    ->setTurnIndex(turnIndex)
                    ->setRoundIndex(roundIndex)
                    ->setSetIndex(setIndex)
                    ->setAttemptIndex(attemptIndex);
            return model;
        }
    };
}

#endif // BUILDDARTSPOINTINDEXES_H
