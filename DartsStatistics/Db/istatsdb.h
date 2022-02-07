#ifndef ISTATSDB_H
#define ISTATSDB_H
#include <functional>
template<typename T> class QVector;
template<typename TModel>
class IStatsDb
{
public:
    typedef TModel Model;
    typedef QVector<Model> Models;
    typedef std::function<bool(const Model&)> Pred;
    virtual void add(const Model &model) = 0;
    virtual void add(const Models &models) = 0;
    virtual Model &model(const int &index) = 0;
    virtual Model &model(Pred prefFunc) = 0;
    virtual Models models() const = 0;
    virtual Models models(Pred prefFunc) const = 0;
    virtual void remove(const int &index) = 0;
    virtual void remove(const QVector<int> &indexes) = 0;
    virtual void clear() = 0;
    virtual int indexOf(const Model &model) const = 0;
    virtual void replace(const int &index, const Model &model) = 0;
};
#endif // IPLAYERSDB_H
