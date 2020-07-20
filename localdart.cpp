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

LocalDart::LocalDart(AbstractDataContext *dataContext, DefaultControllerBuilderInterface *builder):
    AbstractDartInterface(dataContext,builder)
{
}

void LocalDart::createTournament(const QString &title,
                                 const int &numberOfThrows,
                                 const int &maxPlayers,
                                 const int &gameMode,
                                 const int &keyPoint,
                                 const QVariantList &playerIndexes)
{
    emit sendTournamentCandidate(title,numberOfThrows,maxPlayers,gameMode,keyPoint, playerIndexes);
}


void LocalDart::handleSendGameModesRequest() const
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

void LocalDart::startGame()
{

}

void LocalDart::stopGame()
{

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
