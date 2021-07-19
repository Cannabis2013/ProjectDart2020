#ifndef CONNECTDETERMINEGAMEMODE_H
#define CONNECTDETERMINEGAMEMODE_H

#include "abstractmodelsservice.h"
#include "abstractroutebygamemode.h"
#include "iconnectroutebygamemode.h"

class ConnectRouteByGameMode : public IConnectRouteByGameMode
{
public:
    void connect(AbstractModelsService* modelsService,
                 AbstractRouteByGameMode* gameModeService) const override
    {
        QObject::connect(modelsService,&AbstractModelsService::requestAssembleTournament,
                gameModeService,&AbstractRouteByGameMode::handleTournamentGameMode);
        QObject::connect(gameModeService,&AbstractRouteByGameMode::requestDartsDetails,
                modelsService,&AbstractModelsService::createDartsKeyValues);
    }
};

#endif // CONNECTDETERMINEGAMEMODE_H
