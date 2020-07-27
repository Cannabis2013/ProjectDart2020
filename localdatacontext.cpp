#include "localdatacontext.h"

LocalDataContext::LocalDataContext(const QString &org, const QString &app)
{
    setTournamentModelContext(new LocalTournamentModelsContext(org,app));
    setPlayerModelsContext(new LocalPlayerModelContext);
    createInitialModels();
}

void LocalDataContext::read()
{

}

void LocalDataContext::write()
{
    /*
     * Persist tournament models
     */
    QJsonObject modelJSON;
    modelJSON["TournamentsData"] = assembleTournamentsJSONArray();
    modelJSON["RoundsData"] = assembleRoundsJSONArray();
    modelJSON["SetsData"] = assembeSetsJSONArray();
    modelJSON["ScoresData"] = assembleScoresJSONArray();
    modelJSON["PlayersData"] = assemblePlayersJSONArray();
    writeJSONToFile(modelJSON,"Models");
}


void LocalDataContext::createTournament(const QString &title,
                                        const int &numberOfThrows,
                                        const int &gameMode,
                                        const int &keyPoint,
                                        const QVariantList &playerIndexes)
{
    auto tournamentID = tournamentModelContext()->createtournament(title,
                                                                   keyPoint,
                                                                   numberOfThrows,
                                                                   gameMode,
                                                                   QUuid(),
                                                                   QUuid());
    QVariantList playerNames;
    for (auto variant : playerIndexes) {
        auto index = variant.toInt();
        auto playerID = playerModelsContext()->playerIDFromIndex(index);
        tournamentModelContext()->assignPlayerToTournament(tournamentID,playerID);

        auto playerUserName = playerModelsContext()->playerUserName(playerID);
        playerNames << QVariant(playerUserName);
    }
    sendStatus(Status::ContextSuccessfullyUpdated,playerNames);
}

void LocalDataContext::createPlayer(const QString &userName, const QString &mail)
{
    playerModelsContext()->createPlayer(userName,mail);
    emit sendStatus(Status::ContextSuccessfullyUpdated,{});
}

void LocalDataContext::addScore(const QUuid &tournament,
                                 const QString &userName,
                                 const int &roundIndex,
                                 const int &setIndex,
                                 const int &throwIndex,
                                 const int &point,
                                 const int &score)
{
    _currentStatus = Status::ContextBusy;
    auto playerID = playerModelsContext()->playerIDFromUserName(userName);
    try {
        auto pointID = tournamentModelContext()->playerPoint(tournament,playerID,roundIndex,throwIndex,HiddenHint);
        tournamentModelContext()->editScore(pointID,point,score,DisplayHint);

    } catch (...) {
        tournamentModelContext()->addScore(tournament,playerID,point,roundIndex,setIndex,throwIndex,score);
    }
    _currentStatus = Status::ContextReady;
    emit sendContextStatus(Status::ContextSuccessfullyUpdated,{userName,score});
}

void LocalDataContext::sendRequestedTournaments()
{
    auto count = tournamentModelContext()->tournamentsCount();
    for (int i = 0; i < count; ++i) {
        auto id = tournamentModelContext()->tournamentIDFromIndex(i);
        auto title = tournamentModelContext()->tournamentTitle(id);
        auto numberOfThrows = tournamentModelContext()->tournamentNumberOfThrows(id);
        auto gameMode = tournamentModelContext()->tournamentGameMode(id);
        auto keyPoint = tournamentModelContext()->tournamentKeyPoint(id);
        auto playersCount = tournamentModelContext()->tournamentAssignedPlayers(id).count();

        emit sendTournament(title,numberOfThrows,gameMode,keyPoint,playersCount);
    }
}

void LocalDataContext::handleSetCurrentTournament(const int &index)
{
    auto tournamentID = tournamentModelContext()->tournamentIDFromIndex(index);
    auto keyPoint = tournamentModelContext()->tournamentKeyPoint(tournamentID);
    auto numberOfThrows = tournamentModelContext()->tournamentNumberOfThrows(tournamentID);
    auto assignedPlayersID = tournamentModelContext()->tournamentAssignedPlayers(tournamentID);
    auto assignedUserNames = playerUserNamesFromPlayersID(assignedPlayersID);
    emit sendInitialControllerValues(tournamentID,keyPoint,numberOfThrows,assignedUserNames);
}

void LocalDataContext::handleInitialIndexesRequest(const QUuid &tournament, const QStringList &assignedPlayers)
{
    auto turnIndex = 0;
    auto roundIndex = 1;
    auto setIndex = 0;
    auto throwIndex = 0;
    auto playersCount = assignedPlayers.count();
    auto numberOfThrows= tournamentModelContext()->tournamentNumberOfThrows(tournament);
    while(1)
    {
        auto userName = assignedPlayers.at(setIndex);
        auto playerId = playerModelsContext()->playerIDFromUserName(userName);
        try {
            tournamentModelContext()->playerPoint(tournament,playerId,roundIndex,throwIndex,LocalDataContext::DisplayHint);
        } catch (...) {
            break;
        }
        if(++throwIndex % numberOfThrows == 0)
        {
            throwIndex = 0;
            setIndex++;
            if(setIndex >= playersCount)
            {
                roundIndex++;
                setIndex = 0;
            }
        }
        turnIndex++;
    }
    if(turnIndex != 0)
    {
        auto totalTurns = tournamentModelContext()->playerPointsCount(LocalDataContext::allHints);
        emit sendInitialControllerIndexes(roundIndex,setIndex,throwIndex,turnIndex,totalTurns);
    }
    else
    {
        emit sendInitialControllerIndexes(1,0,0,0,0);
    }
}

void LocalDataContext::handleSendPlayerDetailsRequest()
{
    auto playersID = playerModelsContext()->players();
    for (auto playerID : playersID) {
        auto userName = playerModelsContext()->playerUserName(playerID);
        auto mailAdress = playerModelsContext()->playerEMail(playerID);
        emit sendPlayerDetail(userName,mailAdress);
    }
}

void LocalDataContext::handleControllerStatusRequest(const QUuid &playerID)
{
    QVariantList arguments;
    auto userName = playerModelsContext()->playerUserName(playerID);
    arguments.append(userName);

    emit sendContextStatus(_currentStatus,arguments);
}

void LocalDataContext::handleScoreCalculationRequest(const QUuid &tournament, const QString &userName, const int &point)
{
    auto playerID = playerModelsContext()->playerIDFromUserName(userName);
    auto score = tournamentModelContext()->score(tournament,playerID);
    emit sendCalculatedScore(point,score);
}

void LocalDataContext::setScoreHint(const QUuid &tournament, const QString &player, const int &roundIndex, const int &throwIndex, const int &hint)
{
    auto playerID = playerModelsContext()->playerIDFromUserName(player);
    QUuid scoreID;
    try {
        scoreID = tournamentModelContext()->playerPoint(tournament,
                                                         playerID,
                                                         roundIndex,
                                                         throwIndex,
                                                         ModelDisplayHint::allHints);
    } catch (...) {
        emit sendContextStatus(Status::ContextUnSuccessfullyUpdated,{});
        return;
    }
    tournamentModelContext()->setScoreHint(scoreID,hint);
    auto scoreValue = tournamentModelContext()->scoreValue(scoreID);
    auto userName = playerModelsContext()->playerUserName(playerID);
    emit sendContextStatus(Status::ContextSuccessfullyUpdated,{userName,scoreValue});
}

QJsonArray LocalDataContext::assembleTournamentsJSONArray()
{
    QJsonArray tournamentsJSON;
    auto tournamentsID = tournamentModelContext()->tournaments();
    for (auto tournamentID : tournamentsID) {
        QJsonObject obj;
        auto id = tournamentID;
        obj["ID"] = id.toString();
        obj["Title"] = tournamentModelContext()->tournamentTitle(id);
        obj["keyPoint"] = tournamentModelContext()->tournamentKeyPoint(id);
        obj["GameMode"] = tournamentModelContext()->tournamentGameMode(id);
        obj["winner"] = tournamentModelContext()->tournamentDeterminedWinner(id).toString();
        obj["throws"] = tournamentModelContext()->tournamentNumberOfThrows(id);
        auto players = tournamentModelContext()->tournamentAssignedPlayers(id);

        QJsonArray playersJSON;
        auto count = players.count();
        for (int j = 0; j < count; ++j) {
            auto playerID = players.at(j).toString();
            QJsonObject playerObj;
            playerObj["ID"] = playerID;
            playersJSON.append(playerObj);
        }
        obj["Players"] = playersJSON;
        tournamentsJSON.append(obj);
    }
    return tournamentsJSON;
}

QJsonArray LocalDataContext::assembleRoundsJSONArray()
{
    QJsonArray roundsJSON;
    auto roundsID = tournamentModelContext()->roundsID();
    for (auto roundID : roundsID) {
        QJsonObject roundJSON;
        roundJSON["ID"] = roundID.toString();
        roundJSON["Index"] = tournamentModelContext()->roundIndex(roundID);
        roundJSON["TournamentID"] = tournamentModelContext()->roundTournament(roundID).toString();
        roundsJSON.append(roundJSON);
    }
    return roundsJSON;
}

QJsonArray LocalDataContext::assembeSetsJSONArray()
{
    QJsonArray setsJSON;
    auto setsID = tournamentModelContext()->setsID();
    for (auto setID : setsID) {
        QJsonObject setJSON;
        setJSON["ID"] = setID.toString();
        setJSON["Index"] = tournamentModelContext()->setIndex(setID);
        setJSON["RoundID"] = tournamentModelContext()->setRound(setID).toString();
        setsJSON.append(setJSON);
    }
    return setsJSON;
}

QJsonArray LocalDataContext::assembleScoresJSONArray()
{
    QJsonArray scoresJSON;
    auto scoresID = tournamentModelContext()->scores();
    for (auto scoreID : scoresID) {
        QJsonObject scoreJSON;
        scoreJSON["ID"] = scoreID.toString();
        scoreJSON["PointValue"] = tournamentModelContext()->scorePointValue(scoreID);
        scoreJSON["Accumulated score"] = tournamentModelContext()->scoreValue(scoreID);
        scoreJSON["SetID"] = tournamentModelContext()->scoreSet(scoreID).toString();
        scoresJSON.append(scoreJSON);
    }
    return scoresJSON;
}

QJsonArray LocalDataContext::assemblePlayersJSONArray()
{
    QJsonArray playersJSON;
    auto players = playerModelsContext()->players();
    for (auto playerID : players) {
        QJsonObject playerJSON;
        playerJSON["ID"] = playerID.toString();
        playerJSON["UserName"] = playerModelsContext()->playerUserName(playerID);
        playerJSON["Mail"] = playerModelsContext()->playerEMail(playerID);
        playersJSON.append(playerJSON);
    }
    return playersJSON;
}

void LocalDataContext::extractTournamentModelsFromJSON(const QJsonArray &arr)
{
    auto context = dynamic_cast<LocalTournamentModelsContext*>(tournamentModelContext());
    auto tournamentsCount = arr.count();
    for (int i = 0; i < tournamentsCount; ++i) {
        auto tournamentJSON = arr[i].toObject();
        auto stringID = tournamentJSON["ID"].toString();
        auto tournamentID = QUuid::fromString(stringID);
        auto title = tournamentJSON["Title"].toString();
        auto keyPoint = tournamentJSON["KeyPoint"].toInt();
        auto gameMode = tournamentJSON["GameMode"].toInt();
        auto throws = tournamentJSON["Throws"].toInt();
        auto winnerStringID = tournamentJSON["WinnerID"].toString();
        auto winnerID = QUuid::fromString(winnerStringID);
        context->buildTournament(tournamentID,title,keyPoint,throws,gameMode,winnerID);
        auto playersJSONArray = tournamentJSON["Players"].toArray();
        auto playersJSONCount = playersJSONArray.count();
        for (int j = 0; j < playersJSONCount; ++j) {
            auto assignedPlayerJSON = playersJSONArray[j].toObject();
            auto stringID = assignedPlayerJSON["ID"].toString();
            auto playerID = QUuid::fromString(stringID);
            tournamentModelContext()->assignPlayerToTournament(tournamentID,playerID);
        }
    }
}

void LocalDataContext::extractRoundModelsFromJSON(const QJsonArray &arr)
{
    auto context = dynamic_cast<LocalTournamentModelsContext*>(tournamentModelContext());
}

void LocalDataContext::extractSetModelsFromJSON(const QJsonArray &arr)
{

}

void LocalDataContext::extractScoreModelsFromJSON(const QJsonArray &arr)
{

}

void LocalDataContext::extractPlayerModelsFromJSON(const QJsonArray &arr)
{

}

QStringList LocalDataContext::playerUserNamesFromPlayersID(const QList<QUuid> playersID)
{
    QStringList userNames;
    for (auto playerID : playersID) {
        auto userName = playerModelsContext()->playerUserName(playerID);
        userNames << userName;
    }
    return userNames;
}


void LocalDataContext::createInitialModels()
{
    auto kent = playerModelsContext()->createPlayer("Kent KillerHertz","");
    auto martin = playerModelsContext()->createPlayer("Martin Hansen","");
    auto william = playerModelsContext()->createPlayer("William Worsøe","");

    /*
    auto firstTournament = tournamentModelContext()->createTournament("Kents turnering",501,3,0x1);
    auto secondTournament = tournamentModelContext()->createTournament("Techno Tonnys turnering",501,3,0x1);

    tournamentModelContext()->tournamentAddPlayer(firstTournament,kent);
    tournamentModelContext()->tournamentAddPlayer(firstTournament,martin);

    tournamentModelContext()->tournamentAddPlayer(secondTournament,kent);
    tournamentModelContext()->tournamentAddPlayer(secondTournament,martin);
    tournamentModelContext()->tournamentAddPlayer(secondTournament,william);
    */
}

void LocalDataContext::handleSendPlayerScoresRequest(const QUuid &tournament)
{
    _currentStatus = Status::ContextBusy;
    auto currentGameMode = tournamentModelContext()->tournamentGameMode(tournament);
    auto keyPoint = tournamentModelContext()->tournamentKeyPoint(tournament);
    emit sendCurrentTournamentKeyPoint(keyPoint);
    auto numberOfThrows = tournamentModelContext()->tournamentNumberOfThrows(tournament);
    auto assignedPlayersID =tournamentModelContext()->tournamentAssignedPlayers(tournament);
    bool isInitial = true;
    for (auto assignedPlayerID : assignedPlayersID) {
        auto roundIndex = 1;
        auto throwIndex = 0;
        auto userName = playerModelsContext()->playerUserName(assignedPlayerID);
        emit sendAssignedPlayerName(userName);
        if(currentGameMode == 0x1)
            emit sendPlayerScore(userName,keyPoint);
        while (1)
        {
            QUuid pointID;
            try {
                pointID = tournamentModelContext()->playerPoint(tournament,
                                      assignedPlayerID,
                                      roundIndex,
                                      throwIndex++,
                                      DisplayHint);

            }  catch (...) {
                break;
            }
            isInitial = false;
            auto score = tournamentModelContext()->scoreValue(pointID);
            emit sendPlayerScore(userName,score);
            if(throwIndex % numberOfThrows == 0)
            {
                throwIndex = 0;
                roundIndex++;
            }
        }
    }
    if(isInitial)
        updateDataContext(tournament,QUuid(),1,0);
    else
    {
        _currentStatus = Status::ContextReady;
        emit sendContextStatus(Status::ContextSuccessfullyUpdated,{});
    }
}

void LocalDataContext::updateDataContext(const QUuid &tournament, const QUuid &player, const int &roundIndex, const int &setIndex)
{
    _currentStatus = Status::ContextBusy;
    QUuid roundID;
    try {
        roundID = tournamentModelContext()->roundID(tournament,roundIndex);
    } catch (...) {
        tournamentModelContext()->addRound(tournament,roundIndex);
    }
    QUuid setID;
    try {
        setID = tournamentModelContext()->setID(tournament,roundIndex,setIndex);
    } catch (...) {
        tournamentModelContext()->addSet(tournament,roundIndex,setIndex);
    }
    auto playerUserName = playerModelsContext()->playerUserName(player);
    _currentStatus = Status::ContextReady;
    emit sendContextStatus(Status::ContextSuccessfullyUpdated,{playerUserName});
}
