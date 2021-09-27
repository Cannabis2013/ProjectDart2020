#ifndef DMCINPUTSTOJSON_H
#define DMCINPUTSTOJSON_H

#include "DartsModelsContext/DMCInputSLAs/idartsinputmodelstojson.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "DartsModelsContext/DMCInputSLAs/idartsinput.h"

class DMCInputsToJson : public IDartsInputModelsToJson
{
public:
    virtual QByteArray toJson(const QVector<const IModel<QUuid>*> &models) const override
    {
        using namespace ModelsContext;
        QJsonArray pointsJsonArray;
        for (const auto& model : models) {
            auto inputModel = dynamic_cast<const IDartsInput*>(model);
            QJsonObject playerJsonObject;
            auto playerId = inputModel->playerId();
            playerJsonObject["playerId"] = playerId.toString(QUuid::WithoutBraces);
            playerJsonObject["point"] = inputModel->point();
            playerJsonObject["modKeyCode"] = inputModel->modKeyCode();
            playerJsonObject["score"] = inputModel->score();
            pointsJsonArray << playerJsonObject;
        }
        auto json = QJsonDocument(pointsJsonArray).toJson();
        return json;
    }
};

#endif // DARTSPOINTSJSONSERVICE_H