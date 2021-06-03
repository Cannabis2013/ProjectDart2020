#ifndef DEFAULTDBMANIPULATORSERVICE_H
#define DEFAULTDBMANIPULATORSERVICE_H

#include "iplayerinputsdbmanipulatorservice.h"
#include "imodelsdbcontext.h"
#include "iplayerinput.h"

namespace DartsModelsContext {
    class DefaultDbManipulatorService : public
            IPlayerInputsDbManipulatorService<IPlayerInput,IModelsDbContext<IPlayerInput>,QUuid>
    {
    public:
        void removeModelsByHint(const ModelInterfaces& models,
                                const int &hint,
                                DbServiceInterface *dbService) const override;
        void removeModelById(const IdFormat &id,DbServiceInterface* dbService) const override;
        void removeModelsByTournamentId(const ModelInterfaces &models, const IdFormat &tournamentId, DbServiceInterface *dbService) const override;
    };
}


#endif // DEFAULTDBMANIPULATORSERVICE_H
