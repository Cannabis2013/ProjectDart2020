#ifndef IMODELSDBCONTEXT_H
#define IMODELSDBCONTEXT_H
#include <qvector.h>
#include "ModelsContext/DbSLAs/idbcontext.h"
#include "ModelsContext/MCModelsSLAs/imodel.h"
#include <quuid.h>
class IModelsDbContext : public IDbContext<IModel<QUuid>>
{
public:
    virtual IModelsDbContext *add(IModel<QUuid> *model) = 0;
    virtual IModel<QUuid> *model(const int &index) const = 0;
    virtual QVector<IModel<QUuid>*> models() const = 0;
    virtual IModelsDbContext *remove(const int &index) = 0;
    virtual int indexOf(IModel<QUuid> *model) const = 0;
    virtual IModelsDbContext *replace(const int &index, IModel<QUuid> *model) = 0;
};
#endif // IDARTSSCOREDB_H
