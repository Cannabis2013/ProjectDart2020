#ifndef IDCMODELTOJSON_H
#define IDCMODELTOJSON_H
class QJsonObject;
template<typename TModel>
class IDCModelToJson
{
public:
    virtual QJsonObject convert(const TModel &model) const = 0;
};
#endif // IDCMODELTOJSON_H
