#ifndef DARTSCREATEJSONFROMDARTSSCORE_H
#define DARTSCREATEJSONFROMDARTSSCORE_H

#include "idartscreatejsonfrommodel.h"
#include "idartsscoreinput.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

class DartsCreateJsonFromScoreModel : public IDartsCreateJsonFromModel<IModel<QUuid>>
{
public:
    virtual QByteArray createJson(const IModel<QUuid> *inputModel) const override
    {
        auto model = dynamic_cast<const ModelsContext::IDartsScoreInput*>(inputModel);
        QJsonObject jsonObject;
        jsonObject["score"] = model->score();
        jsonObject["roundIndex"] = model->roundIndex();
        jsonObject["setIndex"] = model->setIndex();
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

#endif // DARTSCREATEJSONFROMDARTSSCORE_H
