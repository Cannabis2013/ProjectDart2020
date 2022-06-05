#ifndef IDCINPUTCONVERTER_H
#define IDCINPUTCONVERTER_H

#include <DartsController/Converters/idcjsontomodel.h>
#include <DartsController/Converters/idcmodeltojson.h>

template<typename TModel>
class IDCInputConverter : public IDCJsonToModel<TModel>, public IDCModelToJson<TModel>
{
public:
    typedef TModel Model;
    virtual QJsonObject convert(const Model &model) const = 0;
    virtual Model convert(const QJsonObject &json) const = 0;
};

#endif // IDCINPUTCONVERTER_H
