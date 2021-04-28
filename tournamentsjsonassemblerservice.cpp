#include "tournamentsjsonassemblerservice.h"

QJsonArray TournamentsJSonAssemblerService::assembleDartsTournamentsFromModels(const QVector<const IModel<QUuid>*> &models)
{
    QJsonArray tournamentsJSON;
    for (auto i = models.begin();i != models.end();i++) {
        auto model = *i;
        auto tournament = dynamic_cast<const IDartsTournament<QUuid,QVector<QUuid>,QString>*>(model);
        auto obj = assembleJsonObjectFromDartsTournamentModel(tournament);
        auto players = tournament->assignedPlayerIdentities();
        obj["Players"] = assembleJsonArrayFromTournamentPlayerIds(players);
        tournamentsJSON.append(obj);
    }
    return tournamentsJSON;
}

QJsonObject TournamentsJSonAssemblerService::assembleJsonObjectFromDartsTournamentModel(const IDartsTournament<QUuid, QVector<QUuid>, QString> *model)
{
    QJsonObject obj;
    obj["Id"] = model->id().toString();
    obj["Title"] = model->title();
    obj["KeyPoint"] = model->keyPoint();
    obj["GameMode"] = model->gameMode();
    obj["TerminalKeyCode"] = model->terminalKeyCode();
    obj["TableViewHint"] = model->displayHint();
    obj["InputMode"] = model->inputHint();
    obj["Winner"] = model->winnerId().toString();
    obj["Attempts"] = model->attempts();
    return obj;
}

QJsonArray TournamentsJSonAssemblerService::assembleJsonArrayFromTournamentPlayerIds(const QVector<QUuid> &players)
{
    QJsonArray jsonArray;
    auto count = players.count();
    for (int j = 0; j < count; ++j) {
        auto playerID = players.at(j).toString();
        QJsonObject playerObj;
        playerObj["ID"] = playerID;
        jsonArray << playerObj;
    }
    return jsonArray:
}
