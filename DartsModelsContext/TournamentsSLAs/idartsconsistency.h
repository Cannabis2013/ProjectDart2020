#ifndef IDARTSCONSISTENCY_H
#define IDARTSCONSISTENCY_H
#include "DartTournamentsContext/DTCModelsSLAs/itournament.h"
#include "PlayerModelsContext/SLAs/abstractplactx.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
class IDartsConsistency
{
public:
    virtual bool verify(IModel<QUuid> *tournament, const QVector<IModel<QUuid>*> &inputs,const AbstractPlaCtx *playersContext) const = 0;
};
#endif // IDARTSCONSISTENCY_H
