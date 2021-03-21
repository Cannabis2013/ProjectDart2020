#include "remotemodelscontext.h"



RemoteModelsContext::RemoteModelsContext()
{
    _netMng->setParserService(new UrlParser);
}

void RemoteModelsContext::transmitResponse(const int &response, const QVariantList &args)
{
}

void RemoteModelsContext::handleRequestForAddFTPTournament(const QString &title,
                                                           const QVector<int> &data,
                                                           const QVector<int> &playerIndexes)
{

}

void RemoteModelsContext::handleAssignPlayersToTournament(const QUuid &tournament, const QList<QUuid> &playersID)
{
}

void RemoteModelsContext::handleDeleteTournaments(const QVector<int> &indexes)
{
}

void RemoteModelsContext::handleRequestAssignedPlayers(const QUuid &tournament)
{
}

void RemoteModelsContext::handleTransmitPlayerScores(const QUuid &tournament)
{
}

void RemoteModelsContext::handleRequestTournaments()
{
    _netMng->sendGetRequest("GetTournaments",
                            QString(),
                            {},
                            this,
                            SLOT(handleRecievedTournaments(QNetworkReply*)));
}

void RemoteModelsContext::handleRequestTournamentGameMode(const int &index)
{
}

void RemoteModelsContext::assembleTournamentMetaDataFromId(const QUuid &tournament)
{
}

void RemoteModelsContext::handleAddScore(const QUuid &tournament, const QUuid &player, const QVector<int> &dataValues, const bool &isWinnerDetermined)
{
}

void RemoteModelsContext::handleRequestSetScoreHint(const QUuid &tournament, const QUuid &player, const int &roundIndex, const int &throwIndex, const int &hint)
{
}

void RemoteModelsContext::handleResetTournament(const QUuid &tournament)
{
}

void RemoteModelsContext::handleRequestFTPDetails(const QUuid &tournament)
{
}

void RemoteModelsContext::handleCreatePlayer(const QString &name, const QString &mail)
{
}

void RemoteModelsContext::handleDeletePlayerFromIndex(const int &index)
{
}

void RemoteModelsContext::handleDeletePlayersFromIndexes(const QVector<int> &playerIndexes)
{
}

void RemoteModelsContext::handleRequestPlayersDetails()
{
}

void RemoteModelsContext::handleRequestPersistTournamentState()
{
}

void RemoteModelsContext::handleRecievedTournaments(QNetworkReply *reply)
{
    Q_UNUSED(reply);
    cout << "Reply recieved. Data " << reply->readAll().toStdString() << endl;
}
