#ifndef IPLAYERBUILDER_H
#define IPLAYERBUILDER_H
#include "ModelsContext/ModelsSLAs/imodel.h"
#include <QByteArray>
#include <qjsonobject.h>
#include "ModelsContext/DbSLAs/icreatemodelsfrom.h"
template<typename TBaseModel, typename TDataFormat>
class IPlayerBuilder : public ICreateModelsFrom<TDataFormat,TBaseModel>
{
public:
    typedef TBaseModel BaseModel;
    typedef TDataFormat DataFormat;
    virtual BaseModel* createPlayer(const DataFormat &json) const = 0;
    virtual QVector<BaseModel*> createPlayers(const DataFormat &json) const = 0;
    virtual QVector<BaseModel*> create(const DataFormat &json) const override = 0;
};
#endif // IPLAYERCONTEXTMODELBUILDER_H
