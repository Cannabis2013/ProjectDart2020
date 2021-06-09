#ifndef CONNECTDETERMINEGAMEMODE_H
#define CONNECTDETERMINEGAMEMODE_H

#include "ibinaryservice.h"
#include "abstractmodelsservice.h"
#include "abstractroutebygamemode.h"

class ConnectRouteByGameMode : public
        IBinaryService<AbstractModelsService*,AbstractRouteByGameMode*,void>
{
public:
    void service(AbstractModelsService* modelsService,
                 AbstractRouteByGameMode* gameModeService) override
    {
        QObject::connect(modelsService,&AbstractModelsService::requestAssembleTournament,
                gameModeService,&AbstractRouteByGameMode::handleTournamentGameMode);
        QObject::connect(gameModeService,&AbstractRouteByGameMode::requestDartsDetails,
                modelsService,&AbstractModelsService::assembleDartsKeyValues);
    }
};

#endif // CONNECTDETERMINEGAMEMODE_H
