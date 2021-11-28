#ifndef IPLAYERJSONBUILDER_H
#define IPLAYERJSONBUILDER_H
#include "ModelsContext/DbSLAs/icreatedatafrom.h"
template<typename TBaseModel, typename TJsonFormat>
class IPlayerJsonBuilder : public ICreateDataFrom<TBaseModel,QByteArray>
{
public:
    typedef TBaseModel BaseModel;
    typedef TJsonFormat JsonFormat;
    virtual JsonFormat create(const QVector<BaseModel*>& models) const = 0;
    virtual JsonFormat create(const QVector<BaseModel*> &models, JsonFormat &json) const override = 0;
};
#endif // ICREATEJSONFROMPLAYERMODELS_H
