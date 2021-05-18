#include "assemblejsonarrayfromdartspoints.h"

QJsonArray AssembleJsonArrayFromDartsPoints::service(const QVector<const DartsModelsContext::IDartsPointInput *> &modelsList)
{
    QJsonArray resultingJsonArray;
    for (const auto& model : modelsList) {
        QJsonObject jsonObject;
        jsonObject["id"] = model->id().toString();
        jsonObject["tournament"] = model->tournamentId().toString();
        jsonObject["point"] = model->point();
        jsonObject["score"] = model->score();
        jsonObject["roundIndex"] = model->roundIndex();
        jsonObject["setIndex"] = model->setIndex();
        jsonObject["attempt"] = model->attempt();
        jsonObject["playerId"] = model->playerId().toString();
        jsonObject["hint"] = model->hint();
        jsonObject["keyCode"] = model->modKeyCode();
        resultingJsonArray << jsonObject;
    }
    return resultingJsonArray;
}
