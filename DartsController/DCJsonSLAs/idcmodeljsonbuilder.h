#ifndef IDCMODELJSONBUILDER_H
#define IDCMODELJSONBUILDER_H
#include <qbytearray.h>
#include <qjsonobject.h>
template<typename TModel>
class IDCModelJsonBuilder
{
public:
    typedef TModel Model;
    virtual void json(QJsonObject &obj,const Model &model) const = 0;
};
#endif // IDCMODELJSONBUILDER_H
