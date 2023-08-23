#ifndef IPLAYERSDBCONTEXT_H
#define IPLAYERSDBCONTEXT_H

#include <QVector>
#include <functional>

template<typename TModel>
class IPlayersDbContext
{
public:
    typedef TModel Model;
    typedef std::function<bool(Model*)> Pred;
    virtual void add(Model *model) = 0;
    virtual Model *model(const int &) const = 0;
    virtual Model *model(Pred prefFunc) const = 0;
    virtual QVector<Model*> models() const = 0;
    virtual QVector<Model*> models(Pred prefFunc) const = 0;
    virtual void remove(const int &index) = 0;
    virtual void remove(const QVector<int> &indexes) = 0;
    virtual int indexOf(Model *model) const = 0;
    virtual void replace(const int &index, Model *model) = 0;
};
#endif // IPLAYERSDBCONTEXT_H
