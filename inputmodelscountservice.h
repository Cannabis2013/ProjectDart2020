#ifndef INPUTMODELSCOUNTSERVICE_H
#define INPUTMODELSCOUNTSERVICE_H

#include "imodelsdbcontext.h"
#include "iinputmodelscountservice.h"
#include <iplayerinput.h>

namespace DartsModelsContext {
    class InputModelsCountService : public
            IInputModelsCountService<IModelsDbContext<IPlayerInput>,QUuid>
    {
    public:
        virtual int countInputModelsByTournamentId(const IdFormat &tournamentId, const ModelsService *service) const override
        {
            int count = 0;
            for (const auto& model : service->models())
                count = model->tournamentId() == tournamentId ? ++count : count;
            return count;
        }
    };
}

#endif // INPUTMODELSCOUNTSERVICE_H
