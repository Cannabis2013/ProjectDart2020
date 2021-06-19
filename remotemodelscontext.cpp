#include "remotemodelscontext.h"

RemoteModelsContext::RemoteModelsContext()
{
    _netMng->setParserService(new UrlParser);
}

void RemoteModelsContext::addDartsTournament(const QByteArray& json)
{
    _netMng->sendPostRequest("AddFtpTournament",
                             json,
                             QString(),
                             {},
                             this,
                             SLOT(handleAddFTPTournamentReply()));
}

void RemoteModelsContext::deleteTournaments(const QByteArray &json)
{
    _netMng->sendPostRequest("DeleteTournamentsFromIndexes",
                             json,QString(),{},this,
                             SLOT(handleDeleteTournamentsReply()));
}

void RemoteModelsContext::getOrderedDartsPoints(const QUuid &tournamentId)
{
    auto formattedTournamentId  = tournamentId.toString(QUuid::WithoutBraces);
    _netMng->sendGetRequest("AssembleOrderedFtpPlayerScores",
                            QString(),{{"tournamentId",formattedTournamentId}},
                            this,SLOT(recieveFtpScores()));
}

void RemoteModelsContext::handleRequestTournaments()
{
    _netMng->sendGetRequest("GetTournaments",
                            QString(),
                            {},
                            this,
                            SLOT(handleRecievedTournamentsReply()));
}

void RemoteModelsContext::handleRequestGameMode(const int &index)
{
    _netMng->sendGetRequest("GetTournamentGameModeAndId",
                            QString(),{{"index",QString::number(index)}},this,
                            SLOT(handleRequestGameModeReply()));
}

void RemoteModelsContext::assembleDartsTournamentDataFromId(const QUuid &tournamentId)
{
    auto formattedTournamentId  = tournamentId.toString(QUuid::WithoutBraces);
    _netMng->sendGetRequest("GetFtpTournamentMeta",
                            QString(),{{"tournamentId",formattedTournamentId}},
                            this,SLOT(handleFtpTournamentMetaReply()));
}

void RemoteModelsContext::addDartsPoint(const QByteArray &json)
{
    auto jsonDocument = QJsonDocument::fromJson(json).object();
    auto winnerStringId = jsonDocument.value("winnerId").toString();
    _netMng->sendPostRequest("AddFtpScore",
                             json,QString(),{{"winnerId",winnerStringId}},this,
                             SLOT(handleAddFtpScoreReply()));

}

void RemoteModelsContext::resetDartsPointTournament(const QUuid &tournament)
{
    auto tournamentId = tournament.toString(QUuid::WithoutBraces);
    _netMng->sendPostRequest("ResetFtpTournament",QByteArray(),QString(),{{"tournamentId",tournamentId}},this,SLOT(tournamentResetReply()));
}

void RemoteModelsContext::assembleDartsKeyValues(const QUuid &tournament)
{
    _netMng->sendGetRequest("GetFtpDetails",
                            QString(),{{"tournamentId",tournament.toString(QUuid::WithoutBraces)}},this,
                            SLOT(handleRequestFtpDetailsReply()));
}

void RemoteModelsContext::createPlayer(const QByteArray &json)
{
    _netMng->sendPostRequest("CreatePlayer",
                             json,QString(),{},this,
                             SLOT(handleCreatePlayerResponse()));
}

void RemoteModelsContext::deletePlayerFromIndex(const QByteArray &json)
{
}

void RemoteModelsContext::deletePlayersFromIndexes(const QByteArray &json)
{
    _netMng->sendPostRequest("DeletePlayers",
                             json,QString(),{},this,
                             SLOT(deletePlayersReply()));
}

void RemoteModelsContext::handleRequestPlayersDetails()
{
    _netMng->sendGetRequest("GetPlayers",
                            QString(),
                            {},
                            this,
                            SLOT(handleRequestPlayersReply()));
}

void RemoteModelsContext::assembleDartsPointIndexes(const QUuid &tournament)
{
    auto tournamentId = tournament.toString(QUuid::WithoutBraces);
    _netMng->sendGetRequest("GetFtpIndexesAndScores",
                            QString(),{{"tournamentId",tournamentId}},
                            this,SLOT(handleFtpIndexesAndScores()));
}

void RemoteModelsContext::handleRecievedTournamentsReply()
{
    if(!_netMng->reply()->isOpen())
        emit emit sendTournaments({});
    auto byteData = _netMng->reply()->readAll();
    auto jsonDocument = QJsonDocument::fromJson(byteData);
    auto jsonObject = jsonDocument.object();
    auto responseCode = jsonObject.value("response");
    if(responseCode == ResponseCode::Error)
        return;
    auto tournaments = jsonObject.value("payLoad").toArray();
    emit sendTournaments(QJsonDocument(tournaments).toJson());
}

void RemoteModelsContext::handleAddFTPTournamentReply()
{
    if(!_netMng->reply()->isOpen())
        return;
    auto byteData = _netMng->reply()->readAll();
    auto jsonDocument = QJsonDocument::fromJson(byteData);
    auto jsonObject = jsonDocument.object();
    auto responseCode = jsonObject.value("response");
    if(responseCode == ResponseCode::Error)
        return;
    else
        emit tournamentAssembledAndStored();
}

void RemoteModelsContext::handleDeleteTournamentsReply()
{
    if(!_netMng->reply()->isOpen())
        return;
    auto byteData = _netMng->reply()->readAll();
    auto jsonDocument = QJsonDocument::fromJson(byteData);
    auto jsonObject = jsonDocument.object();
    auto responseCode = jsonObject.value("response");
    if(responseCode == ResponseCode::Error)
        emit tournamentsDeletedStatus(false);
    else
        emit tournamentsDeletedStatus(true);
}


void RemoteModelsContext::handleRequestPlayersReply()
{
    if(!_netMng->reply()->isOpen())
        emit sendPlayers({});
    auto byteData = _netMng->reply()->readAll();
    auto jsonDocument = QJsonDocument::fromJson(byteData);
    auto jsonObject = jsonDocument.object();
    auto responseCode = jsonObject.value("response");
    if(responseCode == ResponseCode::Error)
        return;
    QVariantList list;
    auto players = jsonObject.value("payLoad").toArray();
    for (auto i = players.constBegin(); i != players.constEnd(); ++i) {
        auto obj = (*i).toObject();
        auto name = obj.value("playerName").toString();
        auto mail = obj.value("mail").toString();
        list += {name,mail};
    }
    emit sendPlayers(list);
}

void RemoteModelsContext::handleCreatePlayerResponse()
{
    if(!_netMng->reply()->isOpen())
        emit createPlayerResponse(false);
    auto byteData = _netMng->reply()->readAll();
    auto jsonDocument = QJsonDocument::fromJson(byteData);
    auto jsonObject = jsonDocument.object();
    auto responseCode = jsonObject.value("response").toInt();
    if(responseCode == ResponseCode::Error)
        emit createPlayerResponse(false);
    else
        emit createPlayerResponse(true);
}

void RemoteModelsContext::handleRequestGameModeReply()
{
    if(!_netMng->reply()->isOpen())
        emit createPlayerResponse(false);
    auto byteData = _netMng->reply()->readAll();
    auto jsonDocument = QJsonDocument::fromJson(byteData);
    auto jsonObject = jsonDocument.object();
    auto payLoad = jsonObject.value("payLoad").toObject();
    auto gameMode = payLoad.value("gameMode").toInt();
    auto tournamentId = payLoad.value("tournamentId").toString();
    emit requestAssembleTournament(tournamentId,gameMode);
}

void RemoteModelsContext::handleRequestFtpDetailsReply()
{
    if(!_netMng->reply()->isOpen())
        emit createPlayerResponse(false);
    auto byteData = _netMng->reply()->readAll();
    auto jsonDocument = QJsonDocument::fromJson(byteData);
    auto jsonObject = jsonDocument.object();
    auto responseCode = jsonObject.value("response");
    if(responseCode != 0x2)
    {
        auto msg = jsonObject.value("message").toString();
        throw msg;
    }
    auto payLoad = jsonObject.value("payLoad").toObject();
    auto ftpDetails = payLoad.value("ftpDetails").toObject();
    auto json = QJsonDocument(ftpDetails).toJson();
    emit sendDartsDetails(json,0);
}

void RemoteModelsContext::handleFtpIndexesAndScores()
{
    if(!_netMng->reply()->isOpen())
    {
        throw "msg";
    }
    auto byteData = _netMng->reply()->readAll();
    auto jsonDocument = QJsonDocument::fromJson(byteData);
    auto jsonObject = jsonDocument.object();
    auto responseCode = jsonObject.value("response");
    if(responseCode != 0x2)
    {
        auto msg = jsonObject.value("message").toString();
        throw msg;
    }
    auto payLoad = jsonObject.value("payLoad").toObject();
    auto json = QJsonDocument(payLoad).toJson();
    emit sendDartsPointIndexesAsJson(json);
}

void RemoteModelsContext::handleFtpTournamentMetaReply()
{
    if(!_netMng->reply()->isOpen())
        emit createPlayerResponse(false);
    auto byteData = _netMng->reply()->readAll();
    auto jsonObject = QJsonDocument::fromJson(byteData).object();
    auto payLoad = jsonObject.value("payLoad").toObject();
    auto json = QJsonDocument(payLoad).toJson();
    emit sendTournamentMeta(json);
}

void RemoteModelsContext::handleAddFtpScoreReply()
{
    auto reply = _netMng->reply();
    if(!reply->isOpen())
        emit scoreNotAddedToDataContext(reply->errorString());
    auto byteData = _netMng->reply()->readAll();
    auto jsonDocument = QJsonDocument::fromJson(byteData);
    auto jsonObject = jsonDocument.object();
    auto responseCode = jsonObject.value("response").toInt();
    if(responseCode == ResponseCode::Error)
        emit scoreNotAddedToDataContext("Something went wrong!");
    auto payLoad = jsonObject.value("payLoad").toObject();
    auto json = QJsonDocument(payLoad).toJson();
    emit scoreAddedToDataContext(json);
}

void RemoteModelsContext::handleSetScoreHintReply()
{
    auto reply = _netMng->reply();
    if(!reply->isOpen())
    {
        // TODO : Implement error functionality here
        return;
    }
    auto byteData = _netMng->reply()->readAll();
    auto jsonDocument = QJsonDocument::fromJson(byteData);
    auto jsonObject = jsonDocument.object();
    auto responseCode = jsonObject.value("response").toInt();
    auto payLoad = jsonObject.value("payLoad").toObject();
    if(responseCode == ResponseCode::Error)
        throw "Error!";
    auto json = QJsonDocument(payLoad).toJson();
    //emit scoreHintUpdated(json);
}

void RemoteModelsContext::tournamentResetReply()
{
    auto reply = _netMng->reply();
    if(!reply->isOpen())
    {
        // TODO : Implement error functionality here
        emit tournamentResetFailed();
        return;
    }
    auto byteData = _netMng->reply()->readAll();
    auto jsonDocument = QJsonDocument::fromJson(byteData);
    auto jsonObject = jsonDocument.object();
    auto responseCode = jsonObject.value("response").toInt();
    if(responseCode == ResponseCode::Error)
        emit tournamentResetFailed();
    else
        emit tournamentResetSuccess();
}

void RemoteModelsContext::deletePlayersReply()
{
    if(!_netMng->reply()->isOpen())
        emit playersDeletedStatus(false);
    auto byteData = _netMng->reply()->readAll();
    auto jsonDocument = QJsonDocument::fromJson(byteData);
    auto jsonObject = jsonDocument.object();
    auto responseCode = jsonObject.value("response").toInt();
    if(responseCode == ResponseCode::Error)
        emit playersDeletedStatus(false);
    else
        emit playersDeletedStatus(true);
}

void RemoteModelsContext::recieveFtpScores()
{
    if(!_netMng->reply()->isOpen())
    {
        // TODO: Implement generic failure handling
        throw "Not implemented";
    }
    auto byteData = _netMng->reply()->readAll();
    auto jsonDocument = QJsonDocument::fromJson(byteData);
    auto jsonObject = jsonDocument.object();
    auto responseCode = jsonObject.value("response").toInt();
    if(responseCode == ResponseCode::Error)
        throw "Recieve ftp scores: error";
    auto payLoad = jsonObject.value("payLoad").toArray();
    auto json = QJsonDocument(payLoad).toJson();
    emit sendOrderedDartsPoints(json);
}

void RemoteModelsContext::resetDartsScoreTournament(const QUuid &tournamentId)
{

}

void RemoteModelsContext::setDartsTournamentWinner(const QByteArray &)
{

}


void RemoteModelsContext::hideDartsPoint(const QUuid &, const QUuid &, const int &, const int &)
{
}

void RemoteModelsContext::revealPoint(const QUuid &, const QUuid &, const int &, const int &)
{
}

void RemoteModelsContext::hideDartsScore(const QUuid &, const QUuid &, const int &)
{
}

void RemoteModelsContext::revealScore(const QUuid &, const QUuid &, const int &)
{
}

void RemoteModelsContext::addDartsScore(const QByteArray &json)
{
}


void RemoteModelsContext::assembleAssignedPlayerEntities(const QUuid &)
{
}

void RemoteModelsContext::assembleAssignedPlayerPoints(const QUuid &)
{
}

void RemoteModelsContext::assembleDartsTournamentWinnerIdAndName(const QUuid &)
{
}


void RemoteModelsContext::assembleAssignedPlayerScores(const QUuid &)
{
}

void RemoteModelsContext::assembleDartsScoreIndexes(const QUuid &tournament)
{
}
