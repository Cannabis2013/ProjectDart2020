#ifndef CONNECTDETERMINEGAMEMODE_H
#define CONNECTDETERMINEGAMEMODE_H

#include "ibinaryservice.h"
#include "abstractmodelsservice.h"
#include "abstracttournamentgamemodeservice.h"

class ConnectTournamentGameModeService : public
        IBinaryService<AbstractModelsService*,AbstractTournamentGameModeService*,void>
{
public:
    void service(AbstractModelsService* modelsService,
                 AbstractTournamentGameModeService* gameModeService) override
    {
        QObject::connect(modelsService,&AbstractModelsService::requestAssembleTournament,
                gameModeService,&AbstractTournamentGameModeService::handleTournamentGameMode);
        QObject::connect(gameModeService,&AbstractTournamentGameModeService::requestDartsDetails,
                modelsService,&AbstractModelsService::assembleDartsKeyValues);
    }
};

#endif // CONNECTDETERMINEGAMEMODE_H
