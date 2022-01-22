#ifndef IDCMODELBUILDER_H
#define IDCMODELBUILDER_H
template<typename T>
class QVector;
template<typename TModel, typename TJson>
class IDCModelBuilder
{
public:
    typedef TModel Model;
    typedef TJson Json;
    virtual Model create(const Json &json) const = 0;
};

#endif // IDCPLAYERBUILDER_H
