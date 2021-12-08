#ifndef IPLAYERSDBCONTEXT_H
#define IPLAYERSDBCONTEXT_H
#include "ModelsContext/DbSLAs/imodelsdbcontext.h"
#include "PlayerModelsContext/DbSLAs/iplayerbuilder.h"
#include "PlayerModelsContext/DbSLAs/iplayerjsonbuilder.h"
#include <qfuture.h>
class IPlayersDbContext : public IModelsDbContext
{
public:
    virtual void add(IModel<QUuid> *model) = 0;
    virtual IModel<QUuid> *model(const int &) const = 0;
    virtual QVector<IModel<QUuid> *> models() const = 0;
    virtual void remove(const int &index) = 0;
    virtual void remove(const QVector<int> &indexes) = 0;
    virtual int indexOf(IModel<QUuid> *model) const = 0;
    virtual void replace(const int &index, IModel<QUuid> *model) = 0;
};
#endif // IPLAYERSDBCONTEXT_H
