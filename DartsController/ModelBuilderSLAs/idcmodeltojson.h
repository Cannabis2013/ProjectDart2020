#ifndef IDCMODELTOJSON_H
#define IDCMODELTOJSON_H
class QJsonObject;
template<typename TModel>
class IDCModelToJson
{
public:
    typedef TModel Model;
    typedef QJsonObject Json;
    virtual Json create(const Model &model) const = 0;
};
#endif // IDCMODELTOJSON_H
