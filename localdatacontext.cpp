#include "localdatacontext.h"

LocalDataContext::LocalDataContext(const QString &org, const QString &app):
    AbstractPersistence(org,app)
{
    setTournamentModelContext(new LocalTournamentModelContext("MHApp","Dart2020"));
    setPlayerModelContext(new LocalPlayerModelContext);


    createInitialModels();
}

void LocalDataContext::read()
{
}

void LocalDataContext::write()
{
}

void LocalDataContext::createTournament(const QString &title, const int &numberOfThrows, const int &maxPlayers, const int &gameMode, const int &keyPoint, const QVariantList &playerIndexes)
{
    auto tournamentID = tournamentModelContext()->createTournament(title,maxPlayers,keyPoint,numberOfThrows,gameMode);
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
                                 const QUuid &player,
                                 const int &roundIndex,
                                 const int &setIndex,
                                 const int &legIndex,
                                 const int &point)
{
    auto totalScore = tournamentModelContext()->score(tournament, player);

    try {
        auto pointID = tournamentModelContext()->playerPoint(tournament,player,roundIndex,legIndex,HiddenHint);
        tournamentModelContext()->editScore(pointID,point,totalScore,DisplayHint);
        auto userName = playerModelContext()->playerUserName(player);
        emit sendPlayerScore(userName,totalScore);

    } catch (...) {
        auto score = tournamentModelContext()->addScore(tournament,player,roundIndex,setIndex,legIndex,point,totalScore);
        auto userName = playerModelContext()->playerUserName(player);
        emit sendPlayerScore(userName,score);
    }
}

void LocalDataContext::sendRequestedTournaments()
{
    auto count = tournamentModelContext()->tournamentsCount();
    for (int i = 0; i < count; ++i) {
        auto id = tournamentModelContext()->tournamentIDFromIndex(i);
        auto title = tournamentModelContext()->tournamentTitle(id);
        auto numberOfThrows = tournamentModelContext()->tournamentNumberOfThrows(id);
        auto maxPlayers = tournamentModelContext()->tournamentMaximumAllowedPlayers(id);
        auto gameMode = tournamentModelContext()->tournamentGameMode(id);
        auto keyPoint = tournamentModelContext()->tournamentKeyPoint(id);
        auto playersCount = tournamentModelContext()->tournamentAssignedPlayers(id).count();

        emit sendTournament(title,numberOfThrows,maxPlayers,gameMode,keyPoint,playersCount);
    }
}

void LocalDataContext::handleSetCurrentTournament(const int &index)
{
    auto tournamentID = tournamentModelContext()->tournamentIDFromIndex(index);
    auto keyPoint = tournamentModelContext()->tournamentKeyPoint(tournamentID);
    auto numberOfThrows = tournamentModelContext()->tournamentNumberOfThrows(tournamentID);
    auto assignedPlayers = tournamentModelContext()->tournamentAssignedPlayers(tournamentID);
    emit sendInitialControllerValues(tournamentID,keyPoint,numberOfThrows,assignedPlayers);
}

void LocalDataContext::handleInitialIndexesRequest(const QUuid &tournament, const QList<QUuid> *assignedPlayers)
{
    auto turnIndex = 0;
    auto roundIndex = 1;
    auto setIndex = 0;
    auto throwIndex = 0;
    auto playersCount = assignedPlayers->count();
    auto numberOfThrows= tournamentModelContext()->tournamentNumberOfThrows(tournament);
    while(1)
    {
        auto playerID = assignedPlayers->at(setIndex);
        try {
            tournamentModelContext()->playerPoint(tournament,playerID,roundIndex,throwIndex,LocalDataContext::DisplayHint);
        } catch (const char *msg) {
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
        emit sendInitialControllerIndexes(0,0,0,0,0);
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

void LocalDataContext::createInitialModels()
{
    auto kent = playerModelContext()->createPlayer("Kent KillerHertz","");
    auto martin = playerModelContext()->createPlayer("Martin Hansen","");
    auto william = playerModelContext()->createPlayer("William Worsøe","");

    auto firstTournament = tournamentModelContext()->createTournament("Kents turnering",5,501,3,0x1);
    auto secondTournament = tournamentModelContext()->createTournament("Techno Tonnys turnering",5,501,3,0x1);

    tournamentModelContext()->tournamentAddPlayer(firstTournament,kent);
    tournamentModelContext()->tournamentAddPlayer(firstTournament,martin);

    tournamentModelContext()->tournamentAddPlayer(secondTournament,kent);
    tournamentModelContext()->tournamentAddPlayer(secondTournament,martin);
    tournamentModelContext()->tournamentAddPlayer(secondTournament,william);
}

void LocalDataContext::handleSendPlayerScoresRequest(const QUuid &tournament)
{
    auto currentGameMode = tournamentModelContext()->tournamentGameMode(tournament);
    auto keyPoint = tournamentModelContext()->tournamentKeyPoint(tournament);
    emit sendCurrentTournamentKeyPoint(keyPoint);
    auto numberOfThrows = tournamentModelContext()->tournamentNumberOfThrows(tournament);
    auto assignedPlayersID =tournamentModelContext()->tournamentAssignedPlayers(tournament);
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

            auto score = tournamentModelContext()->playerScore(pointID);
            emit sendPlayerScore(userName,score);
            if(throwIndex % numberOfThrows == 0)
            {
                throwIndex = 0;
                roundIndex++;
            }
        }
    }
}

void LocalDataContext::updateDataContext(const QUuid &tournament, const int &roundIndex, const int &setIndex)
{
    QUuid roundID;
    try {
        roundID = tournamentModelContext()->roundID(tournament,roundIndex);
    } catch (const char *msg) {
        appendRound(tournament,roundIndex);
    }
    QUuid setID;
    try {
        setID = tournamentModelContext()->setID(tournament,roundIndex,setIndex);
    } catch (const char *msg) {
        appendSet(tournament,roundIndex,setIndex);
    }
    emit sendContextStatus(Status::ContextSuccessfullyUpdated);
}

void LocalDataContext::appendRound(const QUuid &tournament, const int &index)
{
    tournamentModelContext()->addRound(tournament,index);

}

void LocalDataContext::appendSet(const QUuid &tournament, const int &roundIndex, const int &setIndex)
{
    tournamentModelContext()->addSet(tournament,roundIndex,setIndex);
}
