#ifndef IDCMODELCONVERTER_H
#define IDCMODELCONVERTER_H
class QJsonObject;
template<typename T>
class QVector;
template<typename TModel>
class IDCModelConverter
{
public:
    typedef TModel Model;
    typedef QJsonObject Json;
    virtual Model create(const Json &json) const = 0;
};

#endif // IDCPLAYERBUILDER_H
