#ifndef ASSEMBLEJSONBYDARTSSCOREMODELS_H
#define ASSEMBLEJSONBYDARTSSCOREMODELS_H

#include "iunaryservice.h"
#include <QByteArray>
#include "imodel.h"
#include <quuid.h>
#include "dartsscoreinput.h"
#include <qjsonobject.h>
#include <qjsonarray.h>

namespace InputAssemblerContext {
    typedef QVector<const IDartsScoreInput*> modelsList;
}

class AssembleJsonByDartsScoreModels :
        public IUnaryService<const QVector<const IDartsScoreInput*>&,QJsonArray>
{
public:
    QJsonArray service(const QVector<const IDartsScoreInput*>& modelsList) override
    {
        QJsonArray resultingJsonArray;
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
        return resultingJsonArray;
    }
};

#endif // ASSEMBLEJSONBYDARTSSCOREMODELS_H
