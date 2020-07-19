#include "localdart.h"

void LocalDart::read()
{
}

void LocalDart::write()
{

}


void LocalDart::requestPlayerDetails()
{
    /*
     * TODO: Reimplement this method
     */
}


void LocalDart::requestTournaments()
{
    /*
     * TODO: Reimplement this method
     */
}

void LocalDart::assignPlayers(const QVariantList &list, const QString &tournament)
{
    /*
     * TODO: Reimplement this method
     */
}

void LocalDart::createIni5tialModels() const
{
    /*
     * TODO: Reimplement this method
    auto kent = dataContext()->playerIDFromFullName("Kent KillerHertz");
    auto martin = dataContext()->playerIDFromFullName("Martin Hansen");
    auto william = dataContext()->playerIDFromFullName("William Worsøe");

    auto count = dataContext()->tournamentsCount();

    for (int i = 0; i < count; ++i) {
        auto tournamentID = dataContext()->tournamentIDFromIndex(i);
        if(i == 0)
        {
            dataContext()->tournamentAddPlayer(tournamentID,kent);
            dataContext()->tournamentAddPlayer(tournamentID,martin);
        }
        else if(i == 1)
        {
            dataContext()->tournamentAddPlayer(tournamentID,kent);
            dataContext()->tournamentAddPlayer(tournamentID,martin);
            dataContext()->tournamentAddPlayer(tournamentID,william);
        }
    }
    */
}

void LocalDart::createPlayer(const QString &firstName, const QString &lastName, const QString &email)
{
    /*
     * TODO: Reimplement this method
     */
}

void LocalDart::createTournament(const QString &title, const int &numberOfThrows, const int &maxPlayers, const int &gameMode, const int &keyPoint)
{

}


void LocalDart::gameModes() const
{
    QStringList resultingList;

    QString first = printVariable(FirstToPost);
    QString second = printVariable(RoundBased);
    QString third = printVariable(CircularDart);

    resultingList << first << second << third;

    emit sendGameModes(resultingList);
}

void LocalDart::handleStatusRequest()
{

}

void LocalDart::addPoint(const int &value)
{

}

void LocalDart::handleGameStatusRecieved(const int &status)
{

}

void LocalDart::startGame()
{

}

void LocalDart::stopGame()
{

}

void LocalDart::forwardScoreFromDataContext(const QUuid &player, const int &score)
{
    /*
     * TODO: Reimplement this method
     */
}

int LocalDart::gameModeFromString(const QString &gameMode) const
{
    if(gameMode == printVariable(FirstToPost))
        return FirstToPost;
    else if(gameMode == printVariable(RoundBased))
        return RoundBased;
    else if(gameMode == printVariable(CircularDart))
        return CircularDart;
    else
        return -1;
}
