#ifndef IMODELSDBCONTEXT_H
#define IMODELSDBCONTEXT_H
#include <qvector.h>
#include "ModelsContext/DbSLAs/idbcontext.h"
#include "ModelsContext/ModelsSLAs/imodel.h"
#include <quuid.h>
class IModelsDbContext : public IDbContext<IModel<QUuid>>
{
public:
    virtual void add(IModel<QUuid> *model) override  = 0;
    virtual IModel<QUuid> *model(const int &index) const override = 0;
    virtual IModel<QUuid>* model(std::function<bool (IModel<QUuid>*)> predFunct) const override = 0;
    virtual QVector<IModel<QUuid>*> models() const override = 0;
    virtual QVector<IModel<QUuid>*> models(std::function<bool (IModel<QUuid>*)> predFunct) const override = 0;
    virtual void remove(const int &index) override = 0;
    virtual int indexOf(IModel<QUuid> *model) const override = 0;
    virtual void replace(const int &index, IModel<QUuid> *model) override = 0;
};
#endif // IDARTSSCOREDB_H
