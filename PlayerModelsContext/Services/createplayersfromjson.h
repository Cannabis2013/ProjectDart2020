#ifndef CREATEPLAYERSFROMJSON_H
#define CREATEPLAYERSFROMJSON_H

#include <qjsondocument.h>
#include <qjsonvalue.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "PlayerModelsContext/DbSLAs/iplayercontextmodelbuilder.h"
#include "PlayerModelsContext/Services/playermodel.h"

class CreatePlayersFromJson : public IPlayerContextModelBuilder
{
public:
    QVector<IModel<QUuid>*> createPlayers(const QByteArray &json) const override;
    IModel<QUuid> *createPlayer(const QByteArray &json) const override;
private:
    PlayersContext::PlayerModel *toModel(const QJsonObject &obj) const;
    QJsonObject toJsonObject(const QByteArray &json) const;
    QJsonArray toJsonArray(const QByteArray &json) const;
    QUuid toId(const QString &stringId) const;
};
#endif // PLAYERMODELJSONEXTRACTOR_H
