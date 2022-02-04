#ifndef INPUTSDB_H
#define INPUTSDB_H
#include "Db/istatsdb.h"
#include <qvector.h>
struct Input;
class InputsDb : public IStatsDb<Input>
{
public:
    virtual void add(const Model &model) override;
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
    QVector<Input> _models;
};

#endif // INPUTSDB_H
