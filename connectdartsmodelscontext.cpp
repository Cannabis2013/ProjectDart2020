#include "connectdartsmodelscontext.h"

void ConnectDartsModelsContext::connect(AbstractApplicationInterface *application,
                                        AbstractDartsModelsContext* modelsService)
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
    QObject::connect(application,&AbstractApplicationInterface::requestDeleteTournaments,
            modelsService,&AbstractDartsModelsContext::deleteTournaments);
    QObject::connect(modelsService,&AbstractDartsModelsContext::tournamentsDeletedStatus,
            application,&AbstractApplicationInterface::tournamentsDeletedSuccess);
    /*
     * Send tournament meta information
     */
    QObject::connect(modelsService,&AbstractDartsModelsContext::sendTournamentMeta,
            application,&AbstractApplicationInterface::sendDartsTournamentData);
}

void ConnectDartsModelsContext::registerTypes()
{
    qRegisterMetaType<QVector<QString>>("QVector<QString>");
    qRegisterMetaType<QVector<QUuid>>("QVector<QUuid>");
    qRegisterMetaType<QVector<int>>("QVector<int>");
}
