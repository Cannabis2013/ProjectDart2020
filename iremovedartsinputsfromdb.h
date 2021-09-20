#ifndef IREMOVEDARTSINPUTSFROMDB_H
#define IREMOVEDARTSINPUTSFROMDB_H

#include "iremovefromdb.h"
#include "ModelsContext/imodelsdbcontext.h"
class IRemoveDartsInputsFromDb : public IRemoveFromDb<IModel<QUuid>,IModelsDbContext, QUuid>
{
public:
    virtual void remove(const QUuid &id, IModelsDbContext *dbService) const override = 0;
    virtual void remove(const QVector<const IModel<QUuid>*> &models, const QUuid &tournamentId,
                        IModelsDbContext *dbService) const override = 0;
    virtual void remove(const QVector<const IModel<QUuid>*> &models, const int &hint,
                        IModelsDbContext *dbService) const override = 0;
};


#endif // IREMOVEINPUTSFROMDB_H
