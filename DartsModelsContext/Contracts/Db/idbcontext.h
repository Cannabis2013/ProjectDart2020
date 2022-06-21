#ifndef IDBCONTEXT_H
#define IDBCONTEXT_H
#include <functional>

#include <DartsModelsContext/Contracts/Db/ipersistence.h>

template<typename T>
class QVector;
template<typename TModel>

class IDbContext : public IPersistence
{
public:
    typedef TModel Model;
    virtual void add(Model *model) = 0;
    virtual TModel* model(const int &index) const = 0;
    virtual TModel* model(std::function<bool(Model*)>) const = 0;
    virtual QVector<TModel*> models() const = 0;
    virtual QVector<TModel*> models(std::function<bool(Model*, const int &)> predFunc) const = 0;
    virtual void remove(const int &index) = 0;
    virtual void remove(const QVector<int> &indexes) = 0;
    virtual void remove(std::function<bool(Model*,const int &)> predFunc) = 0;
    virtual int indexOf(Model *model) const = 0;
    virtual void replace(const int &index, Model *model) = 0;
};

#endif // IMODELSDBCONTEXT_H
