#ifndef ASSEMBLEDARTSSCOREINDEXESBYJSON_H
#define ASSEMBLEDARTSSCOREINDEXESBYJSON_H

#include "DartsScoreMultiAttempIndexes.h"

#include "iunaryservice.h"
#include <qjsondocument.h>
#include <QJsonObject>

namespace  DartsScoreMultiAttemptContext{
    class AssembleDartsScoreIndexesByJson : public
            IUnaryService<const QByteArray&,const IDartsMultiAttemptIndexes*>
    {
    public:
        const IDartsMultiAttemptIndexes* service(const QByteArray& json) override
        {
            DartsMultiAttemptIndexes* indexes = new DartsMultiAttemptIndexes;
            auto jsonObject = QJsonDocument::fromJson(json).object();
            indexes->setTotalTurns(jsonObject.value("totalTurns").toInt());
            indexes->setTurns(jsonObject.value("turnIndex").toInt());
            indexes->setRoundIndex(jsonObject.value("roundIndex").toInt());
            indexes->setSetIndex(jsonObject.value("setIndex").toInt());
            return indexes;
        }
    };
}

#endif // ASSEMBLEDARTSSCOREINDEXESBYJSON_H
