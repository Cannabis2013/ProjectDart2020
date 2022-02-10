#ifndef IJSONTOSTATSMODEL_H
#define IJSONTOSTATSMODEL_H
class QJsonObject;
template<typename TModel>
class IJsonToStatsModel
{
public:
    typedef QJsonObject Json;
    virtual TModel convert(const Json &json) const = 0;
};

#endif // ICREATEPLAYER_H
