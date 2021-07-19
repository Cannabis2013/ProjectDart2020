#ifndef REMOVEINPUTSFROMDB_H
#define REMOVEINPUTSFROMDB_H

#include "iremovedartsinputsfromdb.h"
#include "idartsinputdb.h"
#include "iplayerinput.h"

namespace DartsModelsContext {
    class RemoveInputsFromDb : public IRemoveDartsInputsFromDb
    {
    public:
        void remove(const QVector<const IPlayerInput*> &models,
                    const int &hint,
                    IDartsInputDb *dbService) const override;
        void remove(const QVector<const IPlayerInput*> &models,
                    const QUuid &tournamentId,
                    IDartsInputDb *dbService) const override;
        void remove(const QUuid &id,
                    IDartsInputDb* dbService) const override;
    private:
        void removeModel(const IPlayerInput *inputModel, const int &hint, IDartsInputDb *dbService) const;
        bool removeModel(const IPlayerInput *inputModel, const QUuid &id, IDartsInputDb *dbService) const;
    };
}


#endif // DEFAULTDBMANIPULATORSERVICE_H
