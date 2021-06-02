#include "assemblejsonarrayfromdartspoints.h"

using namespace DartsModelsContext;

QJsonArray AssembleJsonArrayFromDartsPoints::service(const ModelsList &modelsList)
    {
    QJsonArray resultingJsonArray;
    for (const auto& model : modelsList) {
        auto dartsPoint = dynamic_cast<const IDartsPointInput*>(model);
        QJsonObject jsonObject;
        jsonObject["id"] = dartsPoint->id().toString();
        jsonObject["tournament"] = dartsPoint->tournamentId().toString();
        jsonObject["point"] = dartsPoint->point();
        jsonObject["score"] = dartsPoint->score();
        jsonObject["roundIndex"] = dartsPoint->roundIndex();
        jsonObject["setIndex"] = dartsPoint->setIndex();
        jsonObject["attempt"] = dartsPoint->attempt();
        jsonObject["playerId"] = dartsPoint->playerId().toString();
        jsonObject["hint"] = dartsPoint->hint();
        jsonObject["keyCode"] = dartsPoint->modKeyCode();
        resultingJsonArray << jsonObject;
    }
    return resultingJsonArray;
}
