#include "localdatacontext.h"

LocalDataContext::LocalDataContext(const QString &org, const QString &app):
    AbstractPersistence(org,app)
{
    setTournamentModelContext(new LocalTournamentModelContext("MHApp","Dart2020"));
    setPlayerModelContext(new LocalPlayerModelContext);
    //createTournament("Kents turnering",5,501,3,0x1);
    //createTournament("Techno Tonnys turnering",5,501,3,0x1);
}

void LocalDataContext::read()
{
}

void LocalDataContext::write()
{
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
        auto playerName = playerModelContext()->playerFullName(player);
        emit sendPlayerScore(playerName,totalScore);

    } catch (...) {
        auto score = tournamentModelContext()->addScore(tournament,player,roundIndex,setIndex,legIndex,point,totalScore);
        auto playerName = playerModelContext()->playerFullName(player);
        emit sendPlayerScore(playerName,score);
    }
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
}

void LocalDataContext::sendPlayerScores(const QUuid &tournament)
{
    auto currentGameMode = tournamentModelContext()->tournamentGameMode(tournament);
    auto keyPoint = tournamentModelContext()->tournamentKeyPoint(tournament);
    emit sendCurrentTournamentKeyPoint(keyPoint);
    auto numberOfThrows = tournamentModelContext()->tournamentNumberOfThrows(tournament);
    auto assignedPlayersID =tournamentModelContext()->tournamentAssignedPlayers(tournament);
    for (auto assignedPlayerID : assignedPlayersID) {
        auto roundIndex = 1;
        auto throwIndex = 0;
        auto playerName = playerModelContext()->playerFullName(assignedPlayerID);
        emit sendAssignedPlayerName(playerName);
        if(currentGameMode == 0x1)
            emit sendPlayerScore(playerName,keyPoint);
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
            emit sendPlayerScore(playerName,score);
            if(throwIndex % numberOfThrows == 0)
            {
                throwIndex = 0;
                roundIndex++;
            }
        }
    }
}

void LocalDataContext::appendRound(const QUuid &tournament, const int &index)
{
    tournamentModelContext()->addRound(tournament,index);

}

void LocalDataContext::appendSet(const QUuid &tournament, const int &roundIndex, const int &setIndex)
{
    tournamentModelContext()->addSet(tournament,roundIndex,setIndex);
}

void LocalDataContext::recieveStatus(const int &status, const QVariantList &args)
{

}
