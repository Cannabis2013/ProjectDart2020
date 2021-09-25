#ifndef IDBCONTEXT_H
#define IDBCONTEXT_H

#include <qvector.h>

template<typename TModel>
class IDbContext
{
public:
    virtual void add(const TModel*) = 0;
    virtual const TModel* model(const int&) const = 0;
    virtual QVector<const TModel*> models() const = 0;
    virtual bool remove(const int&) = 0;
    virtual int indexOf(const TModel*) const = 0;
    virtual void replace(const int&, const TModel*) = 0;
    virtual void fetchModels() = 0;
    virtual void saveState() = 0;
};

#endif // IMODELSDBCONTEXT_H
