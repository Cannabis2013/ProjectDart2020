#ifndef INPUTSDB_H
#define INPUTSDB_H

#include <qvector.h>

#include <DartsStatistics/Db/istatsdb.h>

struct SnapShot;

class InputsDb : public IStatsDb<SnapShot>
{
public:
    virtual void add(const Model &model) override;
    virtual void add(const Models &models) override;
    virtual Model &model(const int &index) override;
    virtual Model &model(Pred predFunc) override;
    virtual QVector<Model> models() const override;
    virtual QVector<Model> models(Pred predFunc) const override;
    virtual void remove(const int &index) override;
    virtual void remove(const QVector<int> &indexes) override;
    virtual void clear() override;
    virtual int indexOf(const Model &model) const override;
    virtual void replace(const int &index, const Model &model) override;
private:
    QVector<SnapShot> _models;
};

#endif // INPUTSDB_H
