#ifndef IPLAYERBUILDER_H
#define IPLAYERBUILDER_H
#include <DartsModelsContext/ModelSLAs/imodel.h>
#include <QByteArray>
#include <qjsonobject.h>
template<typename TBaseModel, typename TDataFormat>
class IPlayerBuilder
{
public:
    typedef TBaseModel BaseModel;
    typedef TDataFormat DataFormat;
    virtual BaseModel* createPlayer(const DataFormat &json) const = 0;
    virtual QVector<BaseModel*> createPlayers(const DataFormat &json) const = 0;
    virtual QVector<BaseModel*> convert(const DataFormat &json) const = 0;
};
#endif // IPLAYERCONTEXTMODELBUILDER_H
