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
            QVector<const IDartsScore*> dartsScoreModels;
            for (const auto &jsonVal : scoreData)
                dartsScoreModels << DartsScore::createInstance(jsonVal.toObject());
            return dartsScoreModels;
        }
    };
}


#endif // ASSEMBLEDARTSSCORESBYJSON_H
