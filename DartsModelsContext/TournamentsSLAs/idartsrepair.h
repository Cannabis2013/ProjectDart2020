#ifndef IDARTSREPAIR_H
#define IDARTSREPAIR_H
#include <quuid.h>
#include "ModelsContext/ModelsSLAs/imodel.h"
#include "PlayerModelsContext/SLAs/abstractplayerscontext.h"
class IDartsRepair
{
public:
    virtual bool repair(IModel<QUuid> *model, const QVector<IModel<QUuid>*> &models, AbstractPlayersContext *playersContext) const = 0;
};
#endif // IDARTSREPAIR_H
