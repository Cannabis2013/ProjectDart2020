#ifndef PLAJSONBUILDER_H
#define PLAJSONBUILDER_H
#include "DbSLAs/iplayer.h"
#include "DataSLAs/idatabuilder.h"
class QJsonObject;
class QJsonArray;
class QByteArray;
class PlaJsonBuilder : public IDataBuilder<IPlayer,QByteArray>
{
public:
    virtual Data create(const Models &models, Data &data) const override;
    virtual Data create(const Models &models) const override;
private:
    QJsonArray toJsonArray(const Models &models) const;
    QJsonObject toJsonObject(Model *model) const;
    QJsonObject toJsonObject(Data &data) const;
};
#endif // PLAJSONBUILDER_H
