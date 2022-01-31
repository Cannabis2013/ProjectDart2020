#ifndef ISTATSDB_H
#define ISTATSDB_H
#include <bits/std_function.h>
template<typename T> class QVector;
template<typename TModel>
class IStatsDb
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
    virtual void clear() = 0;
    virtual int indexOf(Model *model) const = 0;
    virtual void replace(const int &index, Model *model) = 0;
};
#endif // IPLAYERSDB_H
