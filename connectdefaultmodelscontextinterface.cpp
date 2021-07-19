#include "connectdefaultmodelscontextinterface.h"

void ConnectDefaultModelsContextInterface::connect(AbstractApplicationInterface *application,
                                                                  AbstractModelsService* modelsService)
{
    /*
     * Request tournament gamemode
     */
    QObject::connect(application,&AbstractApplicationInterface::setCurrentActiveTournament,
            modelsService,&AbstractModelsService::handleRequestGameMode);
    /*
     * Get all tournaments
     */
    QObject::connect(application,&AbstractApplicationInterface::requestTournaments,
            modelsService,&AbstractModelsService::handleRequestTournaments);
    QObject::connect(modelsService,&AbstractModelsService::sendTournament,
            application,&AbstractApplicationInterface::sendRequestedTournament);
    QObject::connect(modelsService,&AbstractModelsService::sendTournaments,
            application,&AbstractApplicationInterface::sendTournaments);
    /*
     * Get all players
     */
    QObject::connect(application,&AbstractApplicationInterface::requestPlayers,
            modelsService,&AbstractModelsService::handleRequestPlayersDetails);
    QObject::connect(modelsService,&AbstractModelsService::sendPlayers,
            application,&AbstractApplicationInterface::sendPlayers);
    /*
     * Create tournament
     */
    QObject::connect(application,&AbstractApplicationInterface::sendDartsDetails,
            modelsService,&AbstractModelsService::addDartsTournament);
    QObject::connect(modelsService,&AbstractModelsService::tournamentAssembledAndStored,
            application,&AbstractApplicationInterface::tournamentAssembledAndStored);
    /*
     * Create player
     */
    QObject::connect(application,&AbstractApplicationInterface::requestCreatePlayer,
            modelsService,&AbstractModelsService::createPlayer);
    QObject::connect(modelsService,&AbstractModelsService::createPlayerResponse,
            application,&AbstractApplicationInterface::createPlayerResponse);
    /*
     * Delete tournament
     */
    QObject::connect(application,&AbstractApplicationInterface::requestDeleteTournaments,
            modelsService,&AbstractModelsService::deleteTournaments);
    QObject::connect(modelsService,&AbstractModelsService::tournamentsDeletedStatus,
            application,&AbstractApplicationInterface::tournamentsDeletedSuccess);
    /*
     * Delete player{s}
     */
    QObject::connect(application,&AbstractApplicationInterface::requestDeletePlayer,
            modelsService,&AbstractModelsService::deletePlayerFromIndex);
    QObject::connect(application,&AbstractApplicationInterface::requestDeletePlayers,
            modelsService,&AbstractModelsService::deletePlayersFromIndexes);
    QObject::connect(modelsService,&AbstractModelsService::playersDeletedStatus,
            application,&AbstractApplicationInterface::playersDeletedStatus);
    /*
     * Send tournament meta information
     */
    QObject::connect(modelsService,&AbstractModelsService::sendTournamentMeta,
            application,&AbstractApplicationInterface::sendDartsTournamentData);
}

void ConnectDefaultModelsContextInterface::registerTypes()
{
    qRegisterMetaType<QVector<QString>>("QVector<QString>");
    qRegisterMetaType<QVector<QUuid>>("QVector<QUuid>");
    qRegisterMetaType<QVector<int>>("QVector<int>");
}
