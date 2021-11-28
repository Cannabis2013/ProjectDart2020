#ifndef IDARTSCONSISTENCY_H
#define IDARTSCONSISTENCY_H
#include "DartTournamentsContext/DTCModelsSLAs/itournament.h"
#include "PlayerModelsContext/SLAs/abstractplayerscontext.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
class IDartsConsistency
{
public:
    virtual bool verify(IModel<QUuid> *tournament, const QVector<AbstractDartsInput*> &inputs,const AbstractPlayersContext *playersContext) const = 0;
};
#endif // IDARTSCONSISTENCY_H
