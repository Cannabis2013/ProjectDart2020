#ifndef GETINPUTMODELSSERVICE_H
#define GETINPUTMODELSSERVICE_H

#include "igetinputmodelsservice.h"
#include "iplayerinput.h"
#include "imodelsdbcontext.h"

namespace DartsModelsContext {
    class GetInputModelsService : public
            IGetInputModelsService<IPlayerInput,
                                   IModelsDbContext<IPlayerInput>,QUuid>
    {
    public:
        InputModels inputModelsByTournamentId(const IdFormat &tournamentId, const DbServiceInterface *dbService) const override;
        InputModels inputModelsByHint(const IdFormat &tournamentId, const int &hint, const DbServiceInterface *dbService) const override;
    };
}


#endif // GETINPUTMODELSSERVICE_H
