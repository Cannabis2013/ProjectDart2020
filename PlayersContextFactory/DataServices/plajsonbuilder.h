#ifndef PLAJSONBUILDER_H
#define PLAJSONBUILDER_H
#include "DbSLAs/iplayer.h"
#include "DataSLAs/ijsonbuilder.h"
class QJsonObject;
class QJsonArray;
class QByteArray;
class PlaJsonBuilder : public IJsonBuilder<IPlayer>
{
public:
    ByteArray create(const Models &models, ByteArray &data) const override;
    ByteArray create(const Models &models) const override;
    ByteArray create(Model *model) const override;
private:
    QJsonArray toJsonArray(const Models &models) const;
    QJsonObject toJsonObject(Model *model) const;
    QJsonObject toJsonObject(ByteArray &data) const;
};
#endif // PLAJSONBUILDER_H
