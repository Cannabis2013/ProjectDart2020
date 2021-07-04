#ifndef IMODELSDBCONTEXT_H
#define IMODELSDBCONTEXT_H

#include <qvector.h>

template<typename TModel>
class IModelsDbContext
{
public:
    typedef TModel Model;
    virtual void add(const Model*) = 0;
    virtual const Model* model(const int&) const = 0;
    virtual QVector<const Model*> models() const = 0;
    virtual bool remove(const int&) = 0;
    virtual int indexOf(const Model*) const = 0;
    virtual void replace(const int&, const Model*) = 0;
};

#endif // IMODELSDBCONTEXT_H
