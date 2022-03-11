#include "dartscontext.h"

bool DartsContext::addTournament(const QByteArray& json, const QVector<int> &playerIndexes)
{
    return addTournamentToDb()->add(json,playerIndexes,this);
}

bool DartsContext::isConsistent(const QUuid &tournamentId) const
{
    return tournamentServices()->verifyConsistency()->verify(tournamentId,this);
}

bool DartsContext::tryRepair(const QUuid &tournamentId)
{
    return tournamentRepair()->repair(tournamentId,this);
}

bool DartsContext::setTournamentWinner(const QUuid &tournamentId, const QString &name)
{
    return setTnmWinner()->setWinner(tournamentId,name,this);
}

QByteArray DartsContext::inputs(const QUuid &tournamentID) const
{
    return inputsToJson()->fromInputs(tournamentID,this);
}

bool DartsContext::deleteTournaments(const QVector<int> &indexes)
{
    return removeTournaments()->remove(indexes,this);
}

QByteArray DartsContext::tournaments()
{
    return getTournamentsAsJson()->tournamentsToJson(this);
}

QByteArray DartsContext::tournament(const int &index) const
{
    return getTournamentAsJson()->tournamentToJson(index,this);
}

QByteArray DartsContext::tournament(const QString &id) const
{
    return getTournamentAsJson()->tournamentToJson(id,this);
}

QByteArray DartsContext::tournament(const QUuid &id) const
{
    return getTournamentAsJson()->tournamentToJson(id,this);
}

bool DartsContext::addInput(const QUuid &tournamentID, const QByteArray &inputAsByteArray, const QByteArray &indexByteArray)
{
    return addInputToDb()->add(inputAsByteArray,indexByteArray,tournamentID,this);
}

bool DartsContext::resetTournament(const QUuid &tournamentId)
{
    return resetDarts()->reset(tournamentId,this);
}

QByteArray DartsContext::createDartsMetaData(const QUuid &tournamentID)
{
    return getTournamentAsJson()->tournamentToJson(tournamentID,this);
}

QByteArray DartsContext::input(const QUuid &tournamentID, const QString &name, const QByteArray &idxBa) const
{
    return inputToJson()->toJson(tournamentID,name,idxBa,this);
}

bool DartsContext::hideInput(QUuid tournamentID, QString name, const QByteArray &indexByteArray)
{
    return hidePlayerInput()->hide(tournamentID,name,indexByteArray,this);
}

bool DartsContext::revealInput(QUuid tournamentID, QString name, const QByteArray &indexByteArray)
{
    return displayPlayerInput()->display(tournamentID,name,indexByteArray,this);
}
