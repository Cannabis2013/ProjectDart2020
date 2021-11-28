#ifndef PLAYERBUILDER_H
#define PLAYERBUILDER_H
#include <qjsondocument.h>
#include <qjsonvalue.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "PlayerModelsContext/DbSLAs/iplayerbuilder.h"
#include "PlayerModelsContext/Services/playermodel.h"
class PlayerBuilder : public IPlayerBuilder<IModel<QUuid>,QByteArray>
{
public:
    IModel<QUuid> *createPlayer(const QByteArray &json) const override;
    QVector<IModel<QUuid>*> createPlayers(const QByteArray &json) const override;
    virtual QVector<BaseModel *> create(const Data &json) const override;
private:
    PlayerModel *toModel(const QJsonObject &obj) const;
    QJsonObject toJsonObject(const QByteArray &json) const;
    QJsonArray toJsonArray(const QByteArray &json) const;
    QUuid toId(const QString &stringId) const;
};
#endif // PLAYERMODELJSONEXTRACTOR_H
