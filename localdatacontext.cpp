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

    auto totalScore = tournamentContext()->score(tournament, player);

    try {
        auto pointID = tournamentContext()->playerPoint(tournament,player,roundIndex,legIndex,HiddenHint);
        tournamentContext()->editScore(pointID,point,totalScore,DisplayHint);
        auto playerName = playerModelContext()->playerFullName(player);
        emit sendPlayerScore(playerName,totalScore);

    } catch (...) {
        auto score = tournamentModelContext()->addScore(tournament,player,roundIndex,setIndex,legIndex,point,totalScore);
        auto playerName = playerModelContext()->playerFullName(player);
        emit sendPlayerScore(playerName,score);
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
    tournamentContext()->addRound(tournament,index);

}

void LocalDataContext::appendSet(const QUuid &tournament, const int &roundIndex, const int &setIndex)
{
    tournamentContext()->addSet(tournament,roundIndex,setIndex);
}

void LocalDataContext::recieveStatus(const int &status, const QVariantList &args)
{

}
