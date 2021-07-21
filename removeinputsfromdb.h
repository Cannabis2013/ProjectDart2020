#ifndef REMOVEINPUTSFROMDB_H
#define REMOVEINPUTSFROMDB_H

#include "iplayerinput.h"
#include "iremovedartsinputsfromdb.h"

namespace ModelsContext {
    class RemoveInputsFromDb : public IRemoveDartsInputsFromDb
    {
    public:
        void remove(const QVector<const IModel<QUuid>*> &models,
                    const int &hint,
                    IDbService *dbService) const override;
        void remove(const QVector<const IModel<QUuid>*> &models,
                    const QUuid &tournamentId,
                    IDbService *dbService) const override;
        void remove(const QUuid &id,
                    IDbService* dbService) const override;
    private:
        void removeModel(const IModel<QUuid> *model, const int &hint, IDbService *dbService) const;
        bool removeModel(const IModel<QUuid> *inputModel, const QUuid &id, IDbService *dbService) const;
    };
}


#endif // DEFAULTDBMANIPULATORSERVICE_H
