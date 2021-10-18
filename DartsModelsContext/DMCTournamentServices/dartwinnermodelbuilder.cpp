#include "DartsModelsContext/DMCTournamentServices/dartwinnermodelbuilder.h"

DartWinnerModelBuilder::DataModel DartWinnerModelBuilder::create(const QByteArray &json) const
{
    return toModel(toJsonObject(json));
}

DartWinnerModelBuilder::DataModel DartWinnerModelBuilder::toModel(const QJsonObject &obj) const
{
    DataModel data;
    data.tournamentId = QUuid::fromString(obj.value("tournamentId").toString());;
    data.winnerId = QUuid::fromString(obj.value("winnerId").toString());
    data.winnerName = obj.value("winnerName").toString("");
    return data;
}

QJsonObject DartWinnerModelBuilder::toJsonObject(const QByteArray &json) const
{
    auto document = QJsonDocument::fromJson(json);
    auto obj = document.object();
    return obj;
}
