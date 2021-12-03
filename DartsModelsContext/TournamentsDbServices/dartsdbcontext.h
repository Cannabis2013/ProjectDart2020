#ifndef DARTSDBCONTEXT_H
#define DARTSDBCONTEXT_H
#include <quuid.h>
#include "ModelsContext/ModelsSLAs/imodel.h"
#include "ModelsContext/DbSLAs/idbcontext.h"
class DartsDbContext : public IDbContext<IModel<QUuid>>
{
public:
    virtual DartsDbContext *add(IModel<QUuid> *model) override;
    virtual IModel<QUuid> *model(const int &index) const override;
    IModel<QUuid>* model(std::function<bool (IModel<QUuid>*)> predFunct) const override;
    virtual QVector<IModel<QUuid>*> models() const override;
    virtual QVector<IModel<QUuid>*> models(std::function<bool (IModel<QUuid> *)> predFunct) const override;
    virtual DartsDbContext *remove(const int &index) override;
    virtual DartsDbContext *remove(const QVector<int> &indexes) override;
    virtual int indexOf(IModel<QUuid> *model) const override;
    virtual DartsDbContext *replace(const int &index, IModel<QUuid> *model) override;
private:
    IModel<QUuid> *modelByIndex(const int &idx) const;
    QVector<IModel<QUuid>*> _models;
};
#endif // DARTSTOURNAMENTJSONDB_H
