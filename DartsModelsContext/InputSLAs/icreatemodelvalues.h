#ifndef ICREATEMODELVALUES_H
#define ICREATEMODELVALUES_H
template<typename T>
class QVector;
template<typename TModel, typename TValsContainer>
class ICreateModelValues
{
public:
    typedef TModel Model;
    typedef QVector<Model*> Models;
    typedef TValsContainer Container;
    typedef QVector<Container> Containers;
    virtual Container create(Model *model) const = 0;
    virtual Containers create(const Models &models) const = 0;
};
#endif // ICREATEMODELVALUES_H
