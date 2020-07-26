#include "localdatacontext.h"

LocalDataContext::LocalDataContext(const QString &org, const QString &app)
{
    setTournamentModelContext(new LocalTournamentModelsContext(org,app));
    setPlayerModelContext(new LocalPlayerModelContext);

    createInitialModels();
}


void LocalDataContext::createTournament(const QString &title, const int &numberOfThrows, const int &gameMode, const int &keyPoint, const QVariantList &playerIndexes)
{
    auto tournamentID = tournamentModelContext()->createTournament(title,keyPoint,numberOfThrows,gameMode);
    QVariantList playerNames;
    for (auto variant : playerIndexes) {
        auto index = variant.toInt();
        auto playerID = playerModelContext()->playerIDFromIndex(index);
        tournamentModelContext()->tournamentAddPlayer(tournamentID,playerID);

        auto playerUserName = playerModelContext()->playerUserName(playerID);
        playerNames << QVariant(playerUserName);
    }
    sendStatus(Status::ContextSuccessfullyUpdated,playerNames);
}

void LocalDataContext::createPlayer(const QString &userName, const QString &mail)
{
    playerModelContext()->createPlayer(userName,mail);
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
    auto playerID = playerModelContext()->playerIDFromUserName(userName);
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
        auto playerId = playerModelContext()->playerIDFromUserName(userName);
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
    auto playersID = playerModelContext()->players();
    for (auto playerID : playersID) {
        auto userName = playerModelContext()->playerUserName(playerID);
        auto mailAdress = playerModelContext()->playerEMail(playerID);
        emit sendPlayerDetail(userName,mailAdress);
    }
}

void LocalDataContext::handleControllerStatusRequest(const QUuid &playerID)
{
    QVariantList arguments;
    auto userName = playerModelContext()->playerUserName(playerID);
    arguments.append(userName);

    emit sendContextStatus(_currentStatus,arguments);
}

void LocalDataContext::handleScoreCalculationRequest(const QUuid &tournament, const QString &userName, const int &point)
{
    auto playerID = playerModelContext()->playerIDFromUserName(userName);
    auto score = tournamentModelContext()->score(tournament,playerID);
    emit sendCalculatedScore(point,score);
}

void LocalDataContext::setScoreHint(const QUuid &tournament, const QString &player, const int &roundIndex, const int &throwIndex, const int &hint)
{
    auto playerID = playerModelContext()->playerIDFromUserName(player);
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
    auto userName = playerModelContext()->playerUserName(playerID);
    emit sendContextStatus(Status::ContextSuccessfullyUpdated,{userName,scoreValue});
}

QStringList LocalDataContext::playerUserNamesFromPlayersID(const QList<QUuid> playersID)
{
    QStringList userNames;
    for (auto playerID : playersID) {
        auto userName = playerModelContext()->playerUserName(playerID);
        userNames << userName;
    }
    return userNames;
}


void LocalDataContext::createInitialModels()
{
    auto kent = playerModelContext()->createPlayer("Kent KillerHertz","");
    auto martin = playerModelContext()->createPlayer("Martin Hansen","");
    auto william = playerModelContext()->createPlayer("William Worsøe","");

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
        auto userName = playerModelContext()->playerUserName(assignedPlayerID);
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
    auto playerUserName = playerModelContext()->playerUserName(player);
    _currentStatus = Status::ContextReady;
    emit sendContextStatus(Status::ContextSuccessfullyUpdated,{playerUserName});
}
