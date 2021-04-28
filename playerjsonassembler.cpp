#include "playerjsonassembler.h"


QJsonArray PlayerJsonAssembler::assembleJsonArrayFromModels(const QVector<const IModel<QUuid> *> &models)
{
    QJsonArray playersJSON;
    for (auto model : models) {
        auto playerModel = dynamic_cast<const PlayerModel*>(model);
        QJsonObject playerJSON;
        playerJSON["Id"] = playerModel->id().toString();
        playerJSON["UserName"] = playerModel->playerName();
        playerJSON["Mail"] = playerModel->email();
        playersJSON.append(playerJSON);
    }
    return playersJSON;
}
