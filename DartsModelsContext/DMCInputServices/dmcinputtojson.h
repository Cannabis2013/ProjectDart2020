#ifndef DMCINPUTTOJSON_H
#define DMCINPUTTOJSON_H

#include "DartsModelsContext/DMCInputSLAs/idartscreatejsonfrommodel.h"
#include "DartsModelsContext/DMCInputSLAs/idartsinput.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

class DMCInputToJson : public IDartsCreateJsonFromModel<IModel<QUuid>>
{
public:
    virtual QByteArray createJson(const IModel<QUuid> *inputModel) const override
    {
        auto model = dynamic_cast<const ModelsContext::IDartsInput*>(inputModel);
        QJsonObject jsonObject;
        jsonObject["point"] = model->point();
        jsonObject["score"] = model->score();
        jsonObject["modKeyCode"] = model->modKeyCode();
        jsonObject["roundIndex"] = model->roundIndex();
        jsonObject["setIndex"] = model->setIndex();
        jsonObject["attempt"] = model->attempt();
        jsonObject["hint"] = model->hint();
        jsonObject["id"] = model->id().toString(QUuid::WithoutBraces);
        jsonObject["playerId"] = model->playerId().toString(QUuid::WithoutBraces);
        jsonObject["playerName"] = model->playerName();
        jsonObject["tournamentId"] = model->tournamentId().toString(QUuid::WithoutBraces);
        auto document = QJsonDocument(jsonObject);
        auto json = document.toJson();
        return json;
    }
};

#endif // DARTSCREATEJSONFROMDARTSPOINT_H
