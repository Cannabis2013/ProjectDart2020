#include "DartsModelsContext/DMCConnectServices/connectdartsmodelscontext.h"

void ConnectDartsModelsContext::connect(AbstractApplicationInterface *application,
                                        AbstractDartsModelsContext* modelsService,
                                        AbstractDCBuilder *dcBuilder)
{
    /*
     * Request tournament gamemode
     */
    QObject::connect(application,&AbstractApplicationInterface::setCurrentActiveTournament,
            modelsService,&AbstractDartsModelsContext::getGameMode);
    /*
     * Get all tournaments
     */
    QObject::connect(application,&AbstractApplicationInterface::requestTournaments,
            modelsService,&AbstractDartsModelsContext::getTournaments);
    QObject::connect(modelsService,&AbstractDartsModelsContext::sendTournament,
            application,&AbstractApplicationInterface::sendRequestedTournament);
    QObject::connect(modelsService,&AbstractDartsModelsContext::sendTournaments,
            application,&AbstractApplicationInterface::sendTournaments);
    /*
     * Create tournament
     */
    QObject::connect(modelsService,&AbstractDartsModelsContext::tournamentCreatedAndPersisted,
            application,&AbstractApplicationInterface::tournamentAssembledAndStored);
    /*
     * Delete tournament
     */
    connectDeleteTournamentInterface(application,modelsService);
    /*
     * Connect modelsservice to RouteByInputHint
     */
    connectToDCBuilder(modelsService,dcBuilder);
    /*
     * Send tournament meta information
     */
    QObject::connect(modelsService,&AbstractDartsModelsContext::sendTournamentMeta,
                     application,&AbstractApplicationInterface::sendDartsTournamentData);
}

void ConnectDartsModelsContext::connectDeleteTournamentInterface(AbstractApplicationInterface *application, AbstractDartsModelsContext *modelsService)
{
    QObject::connect(application,&AbstractApplicationInterface::requestDeleteTournaments,
            modelsService,&AbstractDartsModelsContext::deleteTournaments);
    QObject::connect(modelsService,&AbstractDartsModelsContext::tournamentsDeletedStatus,
            application,&AbstractApplicationInterface::tournamentsDeletedSuccess);
}

void ConnectDartsModelsContext::connectToDCBuilder(AbstractDartsModelsContext *modelsService,
                                                          AbstractDCBuilder *dcBuilder)
{
    QObject::connect(modelsService,&AbstractDartsModelsContext::sendDartsDetails,
                     dcBuilder,&AbstractDCBuilder::createController);
}

void ConnectDartsModelsContext::registerTypes()
{
    qRegisterMetaType<QVector<QString>>("QVector<QString>");
    qRegisterMetaType<QVector<QUuid>>("QVector<QUuid>");
    qRegisterMetaType<QVector<int>>("QVector<int>");
}
