#ifndef GETINPUTMODELSSERVICE_H
#define GETINPUTMODELSSERVICE_H

#include "igetinputmodelsservice.h"
#include "iplayerinput.h"
#include "imodelsdbcontext.h"

namespace DartsModelsContext {
    class GetInputModelsService : public IGetInputModelsService
    {
    public:
        QVector<const IPlayerInput*> inputModels(const QUuid &tournamentId, const IDartsInputDb *dbService) const override;
        QVector<const IPlayerInput*> inputModels(const QUuid &tournamentId, const int &hint, const IDartsInputDb *dbService) const override;
    };
}


#endif // GETINPUTMODELSSERVICE_H
