#ifndef STATSMEMORY_H
#define STATSMEMORY_H

#include <QVector>
#include <DartsStatistics/Contracts/Db/istatsdb.h>

struct PlayerStats;
class IMirrorsDb;

class StatsMemory : public IStatsDb<PlayerStats>
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
    QVector<PlayerStats> _mirrors;
};

#endif // MIRRORSDB_H
