#ifndef IADDPLAYERSTOMEM_H
#define IADDPLAYERSTOMEM_H
template<typename T> class QVector;
template<typename TModel>
class IAddModelsToMemory
{
public:
    typedef TModel Model;
    typedef QVector<Model> Models;
    virtual void add(const Models &players) const = 0;
};

#endif // IADDPLAYERSTOMEM_H
