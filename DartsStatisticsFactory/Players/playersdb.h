#ifndef PLAYERSDB_H
#define PLAYERSDB_H
#include "Db/istatsdb.h"
#include <QVector>
struct PlayerStat;
class PlayersDb : public IStatsDb<PlayerStat>
{
public:
    virtual void add(const Model &model) override;
    virtual Model &model(const int &index) override;
    virtual Model &model(Pred prefFunc) override;
    virtual QVector<Model> models() const override;
    virtual QVector<Model> models(Pred prefFunc) const override;
    virtual void remove(const int &index) override;
    virtual void remove(const QVector<int> &indexes) override;
    virtual void clear() override;
    virtual int indexOf(const Model &model) const override;
    virtual void replace(const int &index, const Model &model) override;
private:
    QVector<PlayerStat> _models;
};

#endif // PLAYERSDB_H
