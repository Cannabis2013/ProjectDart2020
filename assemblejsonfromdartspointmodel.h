#ifndef ASSEMBLEJSONFROMDARTSPOINTMODEL_H
#define ASSEMBLEJSONFROMDARTSPOINTMODEL_H

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <idartspointinput.h>
#include "iunaryservice.h"

class AssembleJsonFromDartsPointModel :
        public IUnaryService<const DartsModelsContext::IDartsPointInput*,QByteArray>
{

    // IUnaryService interface
public:
    QByteArray service(const DartsModelsContext::IDartsPointInput* model) override
    {
        QJsonObject jsonObject;
        jsonObject["modKeyCode"] = model->modKeyCode();
        jsonObject["point"] = model->point();
        jsonObject["playerId"] = model->playerId().toString(QUuid::WithoutBraces);
        jsonObject["roundIndex"] = model->roundIndex();
        jsonObject["setIndex"] = model->setIndex();
        jsonObject["attempt"] = model->attempt();
        jsonObject["hint"] = model->hint();
        auto document = QJsonDocument(jsonObject);
        auto json = document.toJson();
        return json;
    }
};

#endif // ASSEMBLEJSONFROMDARTSPOINTMODEL_H
