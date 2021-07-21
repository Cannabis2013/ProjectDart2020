#ifndef IREMOVEDARTSINPUTSFROMDB_H
#define IREMOVEDARTSINPUTSFROMDB_H

#include "iremovefromdb.h"
#include "idbservice.h"
class IRemoveDartsInputsFromDb : public IRemoveFromDb<IModel<QUuid>,IDbService, QUuid>
{
public:
    virtual void remove(const QUuid &id, IDbService *dbService) const override = 0;
    virtual void remove(const QVector<const IModel<QUuid>*> &models, const QUuid &tournamentId,
                        IDbService *dbService) const override = 0;
    virtual void remove(const QVector<const IModel<QUuid>*> &models, const int &hint,
                        IDbService *dbService) const override = 0;
};


#endif // IREMOVEINPUTSFROMDB_H
