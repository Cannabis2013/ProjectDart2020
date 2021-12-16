#ifndef PLABUILDER_H
#define PLABUILDER_H
#include <qjsondocument.h>
#include <qjsonvalue.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "PlayerModelsContext/DbSLAs/iplayerbuilder.h"
#include "PlayerModelsContext/Services/playermodel.h"
class PlaBuilder : public IPlayerBuilder<IPlayer,QByteArray>
{
public:
    BaseModel *createPlayer(const QByteArray &json) const override;
    QVector<IPlayer *> createPlayers(const QByteArray &json) const override;
    virtual QVector<BaseModel *> convert(const DataFormat &json) const override;
private:
    PlayerModel *toModel(const QJsonObject &obj) const;
    QJsonObject toJsonObject(const QByteArray &json) const;
    QJsonArray toJsonArray(const QByteArray &json) const;
    QUuid toId(const QString &stringId) const;
};
#endif // PLAYERMODELJSONEXTRACTOR_H
