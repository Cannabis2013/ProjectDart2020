#ifndef IREMOVEDARTSINPUTSFROMDB_H
#define IREMOVEDARTSINPUTSFROMDB_H

#include "iremovefromdb.h"
#include "idartsinputdb.h"
#include "iplayerinput.h"
class IRemoveDartsInputsFromDb : public IRemoveFromDb<IPlayerInput,IDartsInputDb,QUuid>
{
public:
    virtual void remove(const QUuid &id, IDartsInputDb *dbService) const override = 0;
    virtual void remove(const QVector<const IPlayerInput*> &models, const QUuid &tournamentId,
                              IDartsInputDb *dbService) const override = 0;
    virtual void remove(const QVector<const IPlayerInput*> &models,
                              const int &hint,
                              IDartsInputDb *dbService) const override = 0;
};

#endif // IREMOVEDARTSINPUTSFROMDB_H
