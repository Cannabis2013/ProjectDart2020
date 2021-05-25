#ifndef ASSEMBLEJSONBYDARTSSCOREMODELS_H
#define ASSEMBLEJSONBYDARTSSCOREMODELS_H

#include "iunaryservice.h"
#include <QByteArray>
#include "imodel.h"
#include <quuid.h>
#include "dartsscoreinput.h"
#include <qjsonobject.h>
#include <qjsonarray.h>

namespace DartsModelsContext {
    class AssembleJsonByDartsScoreModels :
            public IUnaryService<const QVector<const IDartsScoreInput*>&,QJsonObject>
    {
    public:
        QJsonObject service(const QVector<const IDartsScoreInput*>& modelsList) override
        {
            QJsonArray resultingJsonArray;
            QJsonObject jsonObject;
            for (const auto& model : modelsList) {
                QJsonObject jsonObject;
                jsonObject["id"] = model->id().toString();
                jsonObject["tournament"] = model->tournamentId().toString();
                jsonObject["score"] = model->score();
                jsonObject["roundIndex"] = model->roundIndex();
                jsonObject["setIndex"] = model->setIndex();
                jsonObject["playerId"] = model->playerId().toString();
                jsonObject["hint"] = model->hint();
                resultingJsonArray << jsonObject;
            }
            jsonObject["DartsMultiAttemptScores"] = resultingJsonArray;
            return jsonObject;
        }
    };
}


#endif // ASSEMBLEJSONBYDARTSSCOREMODELS_H
