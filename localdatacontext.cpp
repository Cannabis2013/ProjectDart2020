#include "localdatacontext.h"

LocalDataContext::LocalDataContext(DefaultDataInterface *tournamentModelsContext, PlayerContextInterface *playerModelsContext):
    AbstractDataContext(tournamentModelsContext,playerModelsContext)
{
    //createInitialModels();
    read();
}

LocalDataContext::~LocalDataContext()
{
    write();
}

void LocalDataContext::read()
{
    QJsonObject JSONObject;
    try {
        JSONObject = readJSONFromFile("Models");
    } catch (...) {
        return;
    }
    auto tournamentsJSONArray = JSONObject["TournamentsData"].toArray();
    auto roundsJSONArray = JSONObject["RoundsData"].toArray();
    auto setsJSONArray = JSONObject["SetsData"].toArray();
    auto scoresJSONArray = JSONObject["ScoresData"].toArray();
    auto playersJSONArray = JSONObject["PlayersData"].toArray();

    extractTournamentModelsFromJSON(tournamentsJSONArray);
    extractRoundModelsFromJSON(roundsJSONArray);
    extractSetModelsFromJSON(setsJSONArray);
    extractScoreModelsFromJSON(scoresJSONArray);
    extractPlayerModelsFromJSON(playersJSONArray);

    // Do inconsistency check

    tournamentModelsContext()->removeInconsistentModels();
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
    auto tournamentID = tournamentModelsContext()->createtournament(title,
                                                                   keyPoint,
                                                                   numberOfThrows,
                                                                   gameMode);
    QVariantList playerNames;
    for (auto variant : playerIndexes) {
        auto index = variant.toInt();
        auto playerID = playerModelsContext()->playerIDFromIndex(index);
        tournamentModelsContext()->assignPlayerToTournament(tournamentID,playerID);

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
        auto pointID = tournamentModelsContext()->playerPoint(tournament,playerID,roundIndex,throwIndex,HiddenHint);
        tournamentModelsContext()->editScore(pointID,point,score,DisplayHint);

    } catch (...) {
        tournamentModelsContext()->addScore(tournament,playerID,point,roundIndex,setIndex,throwIndex,score);
    }
    _currentStatus = Status::ContextReady;
    emit sendContextStatus(Status::ContextSuccessfullyUpdated,{userName,score});
}

void LocalDataContext::sendRequestedTournaments()
{
    auto count = tournamentModelsContext()->tournamentsCount();
    for (int i = 0; i < count; ++i) {
        auto id = tournamentModelsContext()->tournamentIDFromIndex(i);
        auto title = tournamentModelsContext()->tournamentTitle(id);
        auto numberOfThrows = tournamentModelsContext()->tournamentNumberOfThrows(id);
        auto gameMode = tournamentModelsContext()->tournamentGameMode(id);
        auto keyPoint = tournamentModelsContext()->tournamentKeyPoint(id);
        auto playersCount = tournamentModelsContext()->tournamentAssignedPlayers(id).count();

        emit sendTournament(title,numberOfThrows,gameMode,keyPoint,playersCount);
    }
}

void LocalDataContext::handleSetCurrentTournament(const int &index)
{
    auto tournamentID = tournamentModelsContext()->tournamentIDFromIndex(index);
    auto keyPoint = tournamentModelsContext()->tournamentKeyPoint(tournamentID);
    auto numberOfThrows = tournamentModelsContext()->tournamentNumberOfThrows(tournamentID);
    auto assignedPlayersID = tournamentModelsContext()->tournamentAssignedPlayers(tournamentID);
    auto assignedUserNames = playerUserNamesFromPlayersID(assignedPlayersID);
    auto assignedPlayersCount = assignedUserNames.count();
    if(assignedPlayersCount > 0)
        emit sendInitialControllerValues(tournamentID,keyPoint,numberOfThrows,assignedUserNames);
    else
        emit sendStatus(Status::ContextUnSuccessfullyUpdated,{});
}

void LocalDataContext::handleInitialIndexesRequest(const QUuid &tournament, const QVector<QString> &assignedPlayers)
{
    auto turnIndex = 0;
    auto roundIndex = 1;
    auto setIndex = 0;
    auto throwIndex = 0;
    auto playersCount = assignedPlayers.count();
    auto numberOfThrows= tournamentModelsContext()->tournamentNumberOfThrows(tournament);
    while(1)
    {
        auto userName = assignedPlayers.at(setIndex);
        auto playerId = playerModelsContext()->playerIDFromUserName(userName);
        try {
            tournamentModelsContext()->playerPoint(tournament,playerId,roundIndex,throwIndex,LocalDataContext::DisplayHint);
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
        auto totalTurns = tournamentModelsContext()->playerPointsCount(LocalDataContext::allHints);
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

void LocalDataContext::setScoreHint(const QUuid &tournament,
                                    const QString &player,
                                    const int &roundIndex,
                                    const int &throwIndex,
                                    const int &hint)
{
    auto playerID = playerModelsContext()->playerIDFromUserName(player);
    QUuid scoreID;
    try {
        scoreID = tournamentModelsContext()->playerPoint(tournament,
                                                         playerID,
                                                         roundIndex,
                                                         throwIndex,
                                                         ModelDisplayHint::allHints);
    } catch (...) {
        emit sendContextStatus(Status::ContextUnSuccessfullyUpdated,{});
        return;
    }
    tournamentModelsContext()->setScoreHint(scoreID,hint);
    auto scoreValue = tournamentModelsContext()->scoreValue(scoreID);
    auto pointValue = tournamentModelsContext()->scorePointValue(scoreID);
    auto userName = playerModelsContext()->playerUserName(playerID);
    emit sendContextStatus(Status::ContextSuccessfullyUpdated,{userName,pointValue,scoreValue});
}

void LocalDataContext::deleteTournamentsFromIndexes(const QVariantList &indexes)
{
    QVariantList indexesOfDeletedTournaments;
    for (auto variantIndex : indexes) {
        auto index = variantIndex.toInt();
        QUuid tournamentID;
        try {
            tournamentID = tournamentModelsContext()->tournamentIDFromIndex(index);
            indexesOfDeletedTournaments.append(variantIndex);
        } catch (...) {
            emit sendStatus(Status::ContextUnSuccessfullyUpdated,{indexesOfDeletedTournaments});
            return;
        }
        tournamentModelsContext()->deleteTournament(tournamentID);
    }
    emit sendStatus(Status::ContextSuccessfullyUpdated,{indexesOfDeletedTournaments});
}

void LocalDataContext::handlePlayerScoresRequestFromController(const QUuid &tournament,const QVector<QString> &userNames)
{
    QVector<int> userNamesScores;
    for (auto userName : userNames) {
        QUuid playerID;
        try {
            playerID = playerModelsContext()->playerIDFromUserName(userName);
        }  catch (...) {
            throw  "Model inconsistency detected";
        }
        auto score = tournamentModelsContext()->score(tournament,playerID);
        userNamesScores << score;
    }

    emit sendRequestedUserNamesScore(userNamesScores);
}

QJsonArray LocalDataContext::assembleTournamentsJSONArray()
{
    QJsonArray tournamentsJSON;
    auto tournamentsID = tournamentModelsContext()->tournaments();
    for (auto tournamentID : tournamentsID) {
        QJsonObject obj;
        auto id = tournamentID;
        obj["ID"] = id.toString();
        obj["Title"] = tournamentModelsContext()->tournamentTitle(id);
        obj["KeyPoint"] = tournamentModelsContext()->tournamentKeyPoint(id);
        obj["GameMode"] = tournamentModelsContext()->tournamentGameMode(id);
        obj["winner"] = tournamentModelsContext()->tournamentDeterminedWinner(id).toString();
        obj["throws"] = tournamentModelsContext()->tournamentNumberOfThrows(id);
        auto players = tournamentModelsContext()->tournamentAssignedPlayers(id);

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
    auto roundsID = tournamentModelsContext()->roundsID();
    for (auto roundID : roundsID) {
        QJsonObject roundJSON;
        roundJSON["ID"] = roundID.toString();
        roundJSON["Index"] = tournamentModelsContext()->roundIndex(roundID);
        roundJSON["TournamentID"] = tournamentModelsContext()->roundTournament(roundID).toString();
        roundsJSON.append(roundJSON);
    }
    return roundsJSON;
}

QJsonArray LocalDataContext::assembeSetsJSONArray()
{
    QJsonArray setsJSON;
    auto setsID = tournamentModelsContext()->setsID();
    for (auto setID : setsID) {
        QJsonObject setJSON;
        setJSON["ID"] = setID.toString();
        setJSON["Index"] = tournamentModelsContext()->setIndex(setID);
        setJSON["RoundID"] = tournamentModelsContext()->setRound(setID).toString();
        setsJSON.append(setJSON);
    }
    return setsJSON;
}

QJsonArray LocalDataContext::assembleScoresJSONArray()
{
    QJsonArray scoresJSON;
    auto scoresID = tournamentModelsContext()->scores();
    for (auto scoreID : scoresID) {
        QJsonObject scoreJSON;
        scoreJSON["ID"] = scoreID.toString();
        scoreJSON["PointValue"] = tournamentModelsContext()->scorePointValue(scoreID);
        scoreJSON["ScoreValue"] = tournamentModelsContext()->scoreValue(scoreID);
        scoreJSON["SetID"] = tournamentModelsContext()->scoreSet(scoreID).toString();
        scoreJSON["Index"] = tournamentModelsContext()->scoreThrowIndex(scoreID);
        scoreJSON["PlayerID"] = tournamentModelsContext()->scorePlayer(scoreID).toString();
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
        tournamentModelsContext()->buildTournament(tournamentID,title,keyPoint,throws,gameMode,winnerID);
        auto playersJSONArray = tournamentJSON["Players"].toArray();
        auto playersJSONCount = playersJSONArray.count();
        for (int j = 0; j < playersJSONCount; ++j) {
            auto assignedPlayerJSON = playersJSONArray[j].toObject();
            auto stringID = assignedPlayerJSON["ID"].toString();
            auto playerID = QUuid::fromString(stringID);
            tournamentModelsContext()->assignPlayerToTournament(tournamentID,playerID);
        }
    }
}

void LocalDataContext::extractRoundModelsFromJSON(const QJsonArray &arr)
{
    for (auto JSONValue : arr) {
        auto stringID = JSONValue["ID"].toString();
        auto id = QUuid::fromString(stringID);
        auto index = JSONValue["Index"].toInt();
        auto tournamentStringID = JSONValue["TournamentID"].toString();
        auto tournamentID = QUuid::fromString(tournamentStringID);
        tournamentModelsContext()->buildRound(tournamentID,index,id);
    }
}

void LocalDataContext::extractSetModelsFromJSON(const QJsonArray &arr)
{
    for (auto JSONValue : arr) {
        auto stringID = JSONValue["ID"].toString();
        auto id = QUuid::fromString(stringID);
        auto index = JSONValue["Index"].toInt();
        auto roundStringID = JSONValue["RoundID"].toString();
        auto roundID = QUuid::fromString(roundStringID);
        tournamentModelsContext()->buildSet(id,roundID,index);
    }
}

void LocalDataContext::extractScoreModelsFromJSON(const QJsonArray &arr)
{
    for (auto JSONValue : arr) {
        auto stringID = JSONValue["ID"].toString();
        auto id = QUuid::fromString(stringID);
        auto pointValue = JSONValue["PointValue"].toInt();
        auto scoreValue = JSONValue["ScoreValue"].toInt();
        auto setStringID = JSONValue["SetID"].toString();
        auto setID = QUuid::fromString(setStringID);
        auto playerStringID = JSONValue["PlayerID"].toString();
        auto playerID = QUuid::fromString(playerStringID);
        auto throwIndex = JSONValue["Index"].toInt();
        tournamentModelsContext()->buildScoreModel(id,playerID,setID,pointValue,throwIndex,scoreValue);
    }
}

void LocalDataContext::extractPlayerModelsFromJSON(const QJsonArray &arr)
{
    for (auto JSONValue : arr) {
        auto stringID = JSONValue["ID"].toString();
        auto id = QUuid::fromString(stringID);
        auto userName = JSONValue["UserName"].toString();
        auto mail = JSONValue["Mail"].toString();
        playerModelsContext()->buildPlayerModel(id,userName,mail);
    }
}

QVector<QString> LocalDataContext::playerUserNamesFromPlayersID(const QList<QUuid> playersID)
{
    QVector<QString> userNames;
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
    auto currentGameMode = tournamentModelsContext()->tournamentGameMode(tournament);
    auto keyPoint = tournamentModelsContext()->tournamentKeyPoint(tournament);
    emit sendCurrentTournamentKeyPoint(keyPoint);
    auto numberOfThrows = tournamentModelsContext()->tournamentNumberOfThrows(tournament);
    auto assignedPlayersID =tournamentModelsContext()->tournamentAssignedPlayers(tournament);
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
                pointID = tournamentModelsContext()->playerPoint(tournament,
                                      assignedPlayerID,
                                      roundIndex,
                                      throwIndex++,
                                      DisplayHint);

            }  catch (...) {
                break;
            }
            isInitial = false;
            auto score = tournamentModelsContext()->scoreValue(pointID);
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
        roundID = tournamentModelsContext()->roundID(tournament,roundIndex);
    } catch (...) {
        tournamentModelsContext()->addRound(tournament,roundIndex);
    }
    QUuid setID;
    try {
        setID = tournamentModelsContext()->setID(tournament,roundIndex,setIndex);
    } catch (...) {
        tournamentModelsContext()->addSet(tournament,roundIndex,setIndex);
    }
    auto playerUserName = playerModelsContext()->playerUserName(player);
    _currentStatus = Status::ContextReady;
    emit sendContextStatus(Status::ContextSuccessfullyUpdated,{playerUserName});
}
