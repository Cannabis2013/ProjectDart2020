#ifndef ASSEMBLEJSONFROMDARTSSCOREMODEL_H
#define ASSEMBLEJSONFROMDARTSSCOREMODEL_H

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <idartsscoreinput.h>
#include "iunaryservice.h"

class AssembleJsonFromDartsScoreModel :
        public IUnaryService<const IDartsScoreInput*,QByteArray>
{

    // IUnaryService interface
public:
    QByteArray service(const IDartsScoreInput* model) override
    {
        QJsonObject jsonObject;
        jsonObject["playerId"] = model->playerId().toString(QUuid::WithoutBraces);
        jsonObject["roundIndex"] = model->roundIndex();
        jsonObject["setIndex"] = model->setIndex();
        jsonObject["score"] = model->score();
        jsonObject["hint"] = model->hint();
        auto document = QJsonDocument(jsonObject);
        auto json = document.toJson();
        return json;
    }
};

#endif // ASSEMBLEJSONFROMDARTSSCOREMODEL_H
