#ifndef ITOURNAMENTREPAIR_H
#define ITOURNAMENTREPAIR_H
#include <quuid.h>
#include "DartsModelsContext/TournamentModelsSLAs/abstractdartstournament.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
#include "ModelsContext/ModelsSLAs/imodel.h"
#include "PlayerModelsContext/SLAs/abstractplayerscontext.h"
class ITournamentRepair
{
public:
    virtual bool repair(AbstractDartsTournament *tournament, const QVector<AbstractDartsInput*> &inputs, AbstractPlayersContext *playersContext) const = 0;
};
#endif // ITOURNAMENTREPAIR_H
