#ifndef CONNECTDETERMINEGAMEMODE_H
#define CONNECTDETERMINEGAMEMODE_H

#include "DartsModelsContext/SLAs/abstractdartsmodelscontext.h"
#include "DartApplication/RouteSLAs/abstractroutebygamemode.h"
#include "DartApplication/ConnectRouteSLAs/iconnectroutebygamemode.h"

class ConnectRouteByGameMode : public IConnectRouteByGameMode
{
public:
    void connect(AbstractDartsModelsContext* modelsService,
                 AbstractRouteByGameMode* gameModeService) const override
    {
        QObject::connect(modelsService,&AbstractDartsModelsContext::requestAssembleTournament,
                gameModeService,&AbstractRouteByGameMode::handleTournamentGameMode);
        QObject::connect(gameModeService,&AbstractRouteByGameMode::requestDartsDetails,
                modelsService,&AbstractDartsModelsContext::createDartsKeyValues);
    }
};

#endif // CONNECTDETERMINEGAMEMODE_H
