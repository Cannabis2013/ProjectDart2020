#ifndef ITOURNAMENTREPAIR_H
#define ITOURNAMENTREPAIR_H
#include <quuid.h>
#include "DartsModelsContext/TournamentModelsSLAs/idartstournament.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
#include "PlayerModelsContext/SLAs/absplactx.h"
class ITournamentRepair
{
public:
    virtual bool repair(IDartsTournament *tournament,
                        const QVector<AbstractDartsInput*> &inputs,
                        AbsPlaCtx *playersContext) const = 0;
};
#endif // ITOURNAMENTREPAIR_H
