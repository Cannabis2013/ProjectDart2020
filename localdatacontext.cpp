#include "localdatacontext.h"

LocalDataContext::LocalDataContext(const QString &org, const QString &app):
    AbstractPersistence(org,app)
{
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

    auto totalScore = score(tournament, player);

    try {
        auto pointID = playerPoint(tournament,player,roundIndex,legIndex,HiddenHint);
        editScore(pointID,point,totalScore,DisplayHint);
        auto playerName = playerFullName(player);
        emit sendPlayerScore(playerName,totalScore);
        return pointID;

    } catch (...) {
        auto model = pointBuilder()->buildModel(
                    [this,tournament,roundIndex,setIndex,legIndex,point,player,totalScore]
        {
            PointParameters params;
            auto setId = this->setID(tournament,roundIndex,setIndex);
            params.setId = setId;
            params.playerId = player;
            params.pointValue = point;
            params.legIndex = legIndex;
            params.scoreValue = totalScore;

            return params;
        }(),ModelOptions());

        _points.append(model);

        auto playerName = playerFullName(player);
        emit sendPlayerScore(playerName,totalScore);

        return model->id();
    }
}

TournamentModelContext *LocalDataContext::tournamentContext() const
{
    return _tournamentContext;
}

void LocalDataContext::sendPlayerScores(const QUuid &tournament)
{
    auto currentGameMode = tournamentGameMode(tournament);
    auto keyPoint = tournamentKeyPoint(tournament);
    emit sendCurrentTournamentKeyPoint(keyPoint);
    auto numberOfThrows = tournamentNumberOfThrows(tournament);
    auto assignedPlayersID = tournamentAssignedPlayers(tournament);
    for (auto assignedPlayerID : assignedPlayersID) {
        auto roundIndex = 1;
        auto throwIndex = 0;
        auto playerName = playerFullName(assignedPlayerID);
        emit sendAssignedPlayerName(playerName);
        if(currentGameMode == 0x1)
            emit sendPlayerScore(playerName,keyPoint);
        while (1)
        {
            QUuid pointID;
            try {
                pointID = playerPoint(tournament,
                                      assignedPlayerID,
                                      roundIndex,
                                      throwIndex++,
                                      DisplayHint);

            }  catch (...) {
                break;
            }

            auto score = playerScore(pointID);
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
    addRound(tournament,index);
}

void LocalDataContext::appendSet(const QUuid &tournament, const int &roundIndex, const int &setIndex)
{
    addSet(tournament,roundIndex,setIndex);
}

void LocalDataContext::recieveStatus(const int &status, const QVariantList &args)
{

}
