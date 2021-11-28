#ifndef IDARTSBUILDER_H
#define IDARTSBUILDER_H
#include <qvector.h>
#include "ModelsContext/DbSLAs/icreatemodelsfrom.h"
template<typename TBaseModel, typename TSuperModel = TBaseModel, typename TJsonFormat = QByteArray>
class IDartsBuilder : public ICreateModelsFrom<QByteArray,TBaseModel>
{
public:
    typedef TBaseModel BaseModel;
    typedef TSuperModel SuperModel;
    typedef TJsonFormat JsonFormat;
    virtual SuperModel *createModel(const JsonFormat &json) const = 0;
    virtual QVector<BaseModel*> create(const JsonFormat &json) const override = 0;
};
#endif // ICREATEDARTSPOINTMODELFROMJSON_H
