#ifndef CREATEJSONFROMDARTSSCOREMODELS_H
#define CREATEJSONFROMDARTSSCOREMODELS_H

#include <QByteArray>
#include "imodel.h"
#include <quuid.h>
#include "dartsscoreinput.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "icreatejsonfrominputs.h"

namespace DartsModelsContext {
    class CreateJsonFromDartsScoreModels :
            public ICreateJsonFromInputs
    {
    public:
        virtual QByteArray createJson(const QVector<const IPlayerInput *> &models) const override
        {
            auto arr = createJsonArray(models);
            auto obj = createJsonObject(arr);
            return createByteArray(obj);
        }
    private:
        QJsonArray createJsonArray(const QVector<const IPlayerInput *> &models) const
        {
            QJsonArray arr;
            for (const auto& m : models)
                arr << createJsonObject(m);
            return arr;
        }
        QJsonObject createJsonObject(const IPlayerInput* m) const
        {
            auto model = dynamic_cast<const IDartsScoreInput*>(m);
            QJsonObject jsonObject;
            jsonObject["id"] = model->id().toString();
            jsonObject["tournament"] = model->tournamentId().toString();
            jsonObject["score"] = model->score();
            jsonObject["roundIndex"] = model->roundIndex();
            jsonObject["setIndex"] = model->setIndex();
            jsonObject["playerId"] = model->playerId().toString();
            jsonObject["hint"] = model->hint();
            return jsonObject;
        }
        QJsonObject createJsonObject(const QJsonArray &arr) const
        {
            QJsonObject jsonObject;
            jsonObject["DartsMultiAttemptScores"] = arr;
            return jsonObject;
        }

        QByteArray createByteArray(const QJsonObject &obj) const
        {
            auto document = QJsonDocument(obj);
            auto json = document.toJson();
            return json;
        }
    };
}


#endif // ASSEMBLEJSONBYDARTSSCOREMODELS_H
