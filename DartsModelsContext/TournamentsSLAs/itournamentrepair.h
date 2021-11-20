#ifndef ITOURNAMENTREPAIR_H
#define ITOURNAMENTREPAIR_H
#include <quuid.h>
#include "ModelsContext/ModelsSLAs/imodel.h"
#include "PlayerModelsContext/SLAs/abstractplactx.h"
class ITournamentRepair
{
public:
    virtual bool repair(IModel<QUuid> *model, const QVector<IModel<QUuid>*> &models, AbstractPlaCtx *playersContext) const = 0;
};
#endif // ITOURNAMENTREPAIR_H
