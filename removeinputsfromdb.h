#ifndef REMOVEINPUTSFROMDB_H
#define REMOVEINPUTSFROMDB_H

#include "iplayerinput.h"
#include "DartsController/DCInputSLAs/iremovedartsinputsfromdb.h"

class RemoveInputsFromDb : public IRemoveDartsInputsFromDb
{
public:
    void remove(const QVector<const IModel<QUuid>*> &models,
                const int &hint,
                IModelsDbContext *dbService) const override;
    void remove(const QVector<const IModel<QUuid>*> &models,
                const QUuid &tournamentId,
                IModelsDbContext *dbService) const override;
    void remove(const QUuid &id,
                IModelsDbContext* dbService) const override;
private:
    void removeModel(const IModel<QUuid> *model, const int &hint, IModelsDbContext *dbService) const;
    bool removeModel(const IModel<QUuid> *inputModel, const QUuid &id, IModelsDbContext *dbService) const;
};
#endif // DEFAULTDBMANIPULATORSERVICE_H
