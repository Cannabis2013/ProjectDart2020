#ifndef IDBCONTEXT_H
#define IDBCONTEXT_H
#include <qvector.h>
template<typename TModel>
class IDbContext
{
public:
    virtual IDbContext *add(TModel*) = 0;
    virtual TModel* model(const int&) const = 0;
    virtual TModel* model(std::function<bool(TModel*)>) const = 0;
    virtual QVector<TModel*> models() const = 0;
    virtual QVector<TModel*> models(std::function<bool(TModel*)> predFunc) const = 0;
    virtual IDbContext *remove(const int&) = 0;
    virtual IDbContext *remove(const QVector<int> &indexes) = 0;
    virtual int indexOf(TModel*) const = 0;
    virtual IDbContext *replace(const int&, TModel*) = 0;
};

#endif // IMODELSDBCONTEXT_H
