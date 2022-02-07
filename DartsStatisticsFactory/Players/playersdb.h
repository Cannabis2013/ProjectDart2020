#ifndef PLAYERSDB_H
#define PLAYERSDB_H
#include "Db/istatsdb.h"
#include <QVector>
struct CurrentStats;
class PlayersDb : public IStatsDb<CurrentStats>
{
public:
    virtual void add(const Model &model) override;
    virtual void add(const Models &models) override;
    virtual Model &model(const int &index) override;
    virtual Model &model(Pred prefFunc) override;
    virtual Models models() const override;
    virtual Models models(Pred prefFunc) const override;
    virtual void remove(const int &index) override;
    virtual void remove(const QVector<int> &indexes) override;
    virtual void clear() override;
    virtual int indexOf(const Model &model) const override;
    virtual void replace(const int &index, const Model &model) override;
private:
    QVector<CurrentStats> _models;
};

#endif // PLAYERSDB_H
