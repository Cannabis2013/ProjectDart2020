#include "localdatacontext.h"

LocalDataContext::LocalDataContext(DefaultDataInterface *tournamentModelsContext, PlayerContextInterface *playerModelsContext):
    AbstractDataContext(tournamentModelsContext,playerModelsContext)
{
    createInitialModels();
    //read();
}

LocalDataContext::~LocalDataContext()
{
    //write();
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


void LocalDataContext::handleCreateTournamentRequest(const QString &title,
                                                     const int &numberOfThrows,
                                                     const int &gameMode,
                                                     const int &winCondition,
                                                     const int &keyPoint,
                                                     const QVariantList &playerIndexes)
{
    auto tournamentID = tournamentModelsContext()->createTournament(title,
                                                                    keyPoint,
                                                                    numberOfThrows,
                                                                    gameMode,
                                                                    winCondition);
    QVariantList playerNames;
    for (auto variant : playerIndexes) {
        auto index = variant.toInt();
        auto playerID = playerModelsContext()->playerIDFromIndex(index);
        tournamentModelsContext()->assignPlayerToTournament(tournamentID,playerID);

        auto playerUserName = playerModelsContext()->playerUserName(playerID);
        playerNames << QVariant(playerUserName);
    }
    transmitResponse(DataContextResponse::UpdateSuccessfull,playerNames);
}

void LocalDataContext::handleCreatePlayerRequest(const QString &playerName, const QString &mail)
{
    try {
        playerModelsContext()->playerIDFromName(playerName);
        emit transmitResponse(DataContextResponse::UpdateUnSuccessfull,{});
        return;
    }  catch (...) {}
    playerModelsContext()->createPlayer(playerName,mail);
    emit transmitResponse(DataContextResponse::UpdateSuccessfull,{});
}

void LocalDataContext::handleDeletePlayerRequest(const int &index)
{
    try {
        auto playerID = playerModelsContext()->playerIDFromIndex(index);
        playerModelsContext()->deletePlayerByID(playerID);
        transmitResponse(DataContextResponse::UpdateSuccessfull,{});
    }  catch (...) {
        transmitResponse(DataContextResponse::UpdateUnSuccessfull,{});
    }
}

void LocalDataContext::handleTournamentsRequest()
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

void LocalDataContext::handleTournamentDetailsRequest(const int &index)
{
    try {
        auto tournamentID = tournamentModelsContext()->tournamentIDFromIndex(index);
        auto keyPoint = tournamentModelsContext()->tournamentKeyPoint(tournamentID);
        auto conditionKeyCode = tournamentModelsContext()->tournamentWinningKeyCondition(tournamentID);
        auto numberOfThrows = tournamentModelsContext()->tournamentNumberOfThrows(tournamentID);
        auto assignedPlayersID = tournamentModelsContext()->tournamentAssignedPlayers(tournamentID);
        auto assignedUserNames = playerUserNamesFromPlayersID(assignedPlayersID);
        auto assignedPlayersCount = assignedUserNames.count();
        QVariantList arguments = {tournamentID,keyPoint,conditionKeyCode,numberOfThrows,assignedUserNames, assignedPlayersCount};
        emit sendResponseToContext(DataContextResponse::DataRequestSuccess,arguments);
    } catch (...) {
        emit sendResponseToContext(DataContextResponse::DataRequestFailed,{});
    }
}

void LocalDataContext::handleInitialIndexValuesRequest(const QUuid &tournament, const QStringList &assignedPlayers)
{
    auto turnIndex = 0;
    auto roundIndex = 1;
    auto setIndex = 0;
    auto throwIndex = 0;
    auto playersCount = assignedPlayers.count();
    auto numberOfThrows= tournamentModelsContext()->tournamentNumberOfThrows(tournament);
    while(1)
    {
        auto playerName = assignedPlayers.at(setIndex);
        auto playerId = playerModelsContext()->playerIDFromName(playerName);
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
        emit sendResponseToContext(
                                   DataContextResponse::DataRequestSuccess,{roundIndex,setIndex,throwIndex,turnIndex,totalTurns});
    }
    else
    {
        emit sendResponseToContext(
                                   DataContextResponse::DataRequestSuccess,{1,0,0,0,0});
    }
}

void LocalDataContext::handleSendPlayerDetailsRequest()
{
    auto playersID = playerModelsContext()->players();
    for (auto playerID : playersID) {
        auto playerName = playerModelsContext()->playerUserName(playerID);
        auto mailAdress = playerModelsContext()->playerEMail(playerID);
        emit sendPlayerDetail(playerName,mailAdress);
    }
}

void LocalDataContext::setScoreHint(const QUuid &tournament,
                                    const QUuid &player,
                                    const int &roundIndex,
                                    const int &throwIndex,
                                    const int &hint)
{
    QUuid scoreID;
    try {
        scoreID = tournamentModelsContext()->playerPoint(tournament,
                                                         player,
                                                         roundIndex,
                                                         throwIndex,
                                                         ModelDisplayHint::allHints);
    } catch (...) {
        emit sendResponseToContext(DataContextResponse::UpdateUnSuccessfull,{});
        return;
    }
    tournamentModelsContext()->setScoreHint(scoreID,hint);
    auto scoreValue = tournamentModelsContext()->scoreValue(scoreID);
    auto pointValue = tournamentModelsContext()->scorePointValue(scoreID);
    auto playerName = playerModelsContext()->playerUserName(player);
    emit sendResponseToContext(DataContextResponse::UpdateSuccessfull,{playerName,pointValue,scoreValue});
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
            emit transmitResponse(DataContextResponse::UpdateUnSuccessfull,{indexesOfDeletedTournaments});
            return;
        }
        tournamentModelsContext()->removeTournament(tournamentID);
    }
    emit transmitResponse(DataContextResponse::UpdateSuccessfull,{indexesOfDeletedTournaments});
}

void LocalDataContext::sendUserNameScores(const QUuid &tournament,const QStringList &userNames)
{
    QList<int> userNamesScores;
    for (auto playerName : userNames) {
        QUuid playerID;
        try {
            playerID = playerModelsContext()->playerIDFromName(playerName);
        }  catch (...) {
            throw  "Model inconsistency detected";
        }
        auto score = tournamentModelsContext()->score(tournament,playerID);
        userNamesScores << score;
    }

    QVariant argument;
    argument.setValue<QList<int>>(userNamesScores);
    emit sendResponseToContext(DataContextResponse::DataRequestSuccess,{argument});
}

void LocalDataContext::handleRequestFromContext(const int &request, const QList<QVariant> &args)
{
    if(request == ControllerRequest::RequestBasicValues)
    {
        auto index = args.at(0).toInt();
        handleTournamentDetailsRequest(index);
    }
    else if(request == ControllerRequest::RequestIndexValues)
    {
        auto tournamentID = args.at(0).toUuid();
        auto assignedUserNames = args.at(1).toStringList();
        handleInitialIndexValuesRequest(tournamentID,assignedUserNames);
    }
    else if(request == ControllerRequest::RequestPlayerScores)
    {
        auto tournamentID = args[0].toUuid();
        auto userNames = args[1].toStringList();
        sendUserNameScores(tournamentID,userNames);
    }
    else if(request == ControllerRequest::RequestStorePoint)
    {
        auto tournamentID = args[0].toUuid();
        auto playerName = args[1].toString();
        auto playerID = playerModelsContext()->playerIDFromName(playerName);
        auto roundIndex = args[2].toInt();
        auto setIndex = args[3].toInt();
        auto throwIndex = args[4].toInt();
        auto pointValue = args[5].toInt();
        auto scoreValue = args[6].toInt();

        tournamentModelsContext()->addScore(tournamentID,playerID,pointValue,roundIndex,setIndex,throwIndex,scoreValue);

        emit sendResponseToContext(DataContextResponse::UpdateSuccessfull,{});
    }
    else if(request == ControllerRequest::RequestUpdateModelState)
    {
        auto tournamentID = args[0].toUuid();
        auto playerName = args[1].toString();
        auto playerID = playerModelsContext()->playerIDFromName(playerName);
        auto roundIndex = args[2].toInt();
        auto setIndex = args[3].toInt();
        updateDataContext(tournamentID,playerID,roundIndex,setIndex);
        emit sendResponseToContext(DataContextResponse::UpdateSuccessfull,{playerName});
    }
    else if(request == ControllerRequest::RequestSetModelHint)
    {
        auto tournamentID = args[0].toUuid();
        auto playerName = args[1].toString();
        auto playerID = playerModelsContext()->playerIDFromName(playerName);
        auto roundIndex = args[2].toInt();
        auto throwIndex = args[3].toInt();
        auto hint = args[4].toInt();

        setScoreHint(tournamentID,playerID,roundIndex,throwIndex,hint);
    }
    else if(request == ControllerRequest::RequestResetTournament)
    {
        auto tournamentID = args[0].toUuid();
        tournamentModelsContext()->removeModelsRelatedToTournament(tournamentID);
        emit sendResponseToContext(DataContextResponse::UpdateSuccessfull,{});
    }
}

void LocalDataContext::handleResponseFromContext(const int &response, const QList<QVariant> &args)
{
    if(response == ControllerResponse::DataProvidedSuccess)
    {
        auto tournamentID = args[0].toUuid();
        transmitPlayerScores(tournamentID);
        _currentStatus = ContextStatus::ContextReady;
    }
}

void LocalDataContext::handlePlayerScoresRequest()
{
    _currentStatus = ContextStatus::ContextBusy;
    emit sendRequestToContext(DataContextRequests::RequestCurrentTournament,{});
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
        auto playerName = JSONValue["UserName"].toString();
        auto mail = JSONValue["Mail"].toString();
        playerModelsContext()->buildPlayerModel(id,playerName,mail);
    }
}

QStringList LocalDataContext::playerUserNamesFromPlayersID(const QList<QUuid> playersID)
{
    QStringList userNames;
    for (auto playerID : playersID) {
        auto playerName = playerModelsContext()->playerUserName(playerID);
        userNames << playerName;
    }
    return userNames;
}

void LocalDataContext::createInitialModels()
{
    auto kent = playerModelsContext()->createPlayer("Kent KillerHertz","");
    auto martin = playerModelsContext()->createPlayer("Martin Hansen","");
    auto william = playerModelsContext()->createPlayer("William Worsøe","");

    auto firstTournament = tournamentModelsContext()->createTournament("Kents turnering",501,3,0x1,0x2B);
    auto secondTournament = tournamentModelsContext()->createTournament("Techno Tonnys turnering",501,3,0x1,0x2B);

    tournamentModelsContext()->assignPlayerToTournament(firstTournament,kent);
    tournamentModelsContext()->assignPlayerToTournament(firstTournament,martin);
    tournamentModelsContext()->assignPlayerToTournament(secondTournament,kent);
    tournamentModelsContext()->assignPlayerToTournament(secondTournament,martin);
    tournamentModelsContext()->assignPlayerToTournament(secondTournament,william);

}

void LocalDataContext::transmitPlayerScores(const QUuid &tournament)
{
    _currentStatus = ContextStatus::ContextBusy;
    auto currentGameMode = tournamentModelsContext()->tournamentGameMode(tournament);
    auto keyPoint = tournamentModelsContext()->tournamentKeyPoint(tournament);
    emit sendCurrentTournamentKeyPoint(keyPoint);
    auto numberOfThrows = tournamentModelsContext()->tournamentNumberOfThrows(tournament);
    auto assignedPlayersID =tournamentModelsContext()->tournamentAssignedPlayers(tournament);
    bool isInitial = true;
    for (auto assignedPlayerID : assignedPlayersID) {
        auto roundIndex = 1;
        auto throwIndex = 0;
        auto playerName = playerModelsContext()->playerUserName(assignedPlayerID);
        emit sendAssignedPlayerName(playerName);
        if(currentGameMode == 0x1)
            emit sendPlayerScore(playerName,keyPoint);
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
            int score;
            try {
                score = tournamentModelsContext()->scoreValue(pointID);
            } catch (const char *msg) {
                throw msg;
            }
            emit sendPlayerScore(playerName,score);
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
        _currentStatus = ContextStatus::ContextReady;
    emit transmitResponse(DataContextResponse::EndOfTransmission,{});
}

void LocalDataContext::updateDataContext(const QUuid &tournament, const QUuid &player, const int &roundIndex, const int &setIndex)
{
    _currentStatus = ContextStatus::ContextBusy;
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

    _currentStatus = ContextStatus::ContextReady;
}
