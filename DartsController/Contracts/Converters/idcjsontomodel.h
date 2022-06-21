#ifndef IDCJSONTOMODEL_H
#define IDCJSONTOMODEL_H
class QJsonObject;
template<typename T>
class QVector;
template<typename TModel>
class IDCJsonToModel
{
public:
    virtual TModel convert(const QJsonObject &json) const = 0;
};

#endif // IDCPLAYERBUILDER_H
