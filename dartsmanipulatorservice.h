#ifndef DARTSMANIPULATORSERVICE_H
#define DARTSMANIPULATORSERVICE_H

#include "idbmanipulatorservice.h"
#include "imodelsdbcontext.h"
#include "iplayerinput.h"

namespace DartsModelsContext {
    class DartsManipulatorService : public IDbManipulatorService<IModelsDbContext<IModel<QUuid,QByteArray>,QUuid>,QUuid>
    {

        // IDbManipulatorService interface
    public:
        virtual void removeModelsByHint(const IdFormat &tournamentId, const int &hint, const DbServiceInterface *dbService) const override;
    };
}

#endif // DARTSMANIPULATORSERVICE_H
