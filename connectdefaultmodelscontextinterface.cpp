#include "connectdefaultmodelscontextinterface.h"

void ConnectDefaultModelsContextInterface::service(AbstractApplicationInterface *application,
                                                                     AbstractModelsService* modelsContext)
{

    /*
     * Get all tournaments
     */
    QObject::connect(application,&AbstractApplicationInterface::requestTournaments,
            modelsContext,&AbstractModelsService::handleRequestTournaments);
    QObject::connect(modelsContext,&AbstractModelsService::sendTournament,
            application,&AbstractApplicationInterface::sendRequestedTournament);
    QObject::connect(modelsContext,&AbstractModelsService::sendTournaments,
            application,&AbstractApplicationInterface::sendTournaments);
    /*
     * Get all players
     */
    QObject::connect(application,&AbstractApplicationInterface::requestPlayers,
            modelsContext,&AbstractModelsService::handleRequestPlayersDetails);
    QObject::connect(modelsContext,&AbstractModelsService::sendPlayers,
            application,&AbstractApplicationInterface::sendPlayers);
    /*
     * Create tournament
     */
    QObject::connect(application,&AbstractApplicationInterface::sendDartsDetails,
            modelsContext,&AbstractModelsService::addDartsTournament);
    QObject::connect(modelsContext,&AbstractModelsService::tournamentAssembledAndStored,
            application,&AbstractApplicationInterface::tournamentAssembledAndStored);
    /*
     * Create player
     */
    QObject::connect(application,&AbstractApplicationInterface::requestCreatePlayer,
            modelsContext,&AbstractModelsService::createPlayer);
    QObject::connect(modelsContext,&AbstractModelsService::createPlayerResponse,
            application,&AbstractApplicationInterface::createPlayerResponse);
    /*
     * Delete tournament
     */
    QObject::connect(application,&AbstractApplicationInterface::requestDeleteTournaments,
            modelsContext,&AbstractModelsService::deleteTournaments);
    QObject::connect(modelsContext,&AbstractModelsService::tournamentsDeletedStatus,
            application,&AbstractApplicationInterface::tournamentsDeletedSuccess);
    /*
     * Delete player{s}
     */
    QObject::connect(application,&AbstractApplicationInterface::requestDeletePlayer,
            modelsContext,&AbstractModelsService::deletePlayerFromIndex);
    QObject::connect(application,&AbstractApplicationInterface::requestDeletePlayers,
            modelsContext,&AbstractModelsService::deletePlayersFromIndexes);
    QObject::connect(modelsContext,&AbstractModelsService::playersDeletedStatus,
            application,&AbstractApplicationInterface::playersDeletedStatus);
    /*
     * Send tournament meta information
     */
    QObject::connect(modelsContext,&AbstractModelsService::sendTournamentMeta,
            application,&AbstractApplicationInterface::sendDartsTournamentData);
}

void ConnectDefaultModelsContextInterface::registerTypes()
{
    qRegisterMetaType<QVector<QString>>("QVector<QString>");
    qRegisterMetaType<QVector<QUuid>>("QVector<QUuid>");
    qRegisterMetaType<QVector<int>>("QVector<int>");
}
