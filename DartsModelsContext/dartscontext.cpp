#include "dartscontext.h"
#include "TournamentModelsSLAs/idartstournament.h"
#include "ByteArrayServices/converttobytearray.h"
#include "Models/DartsPlayer.h"
bool DartsContext::addTournament(const QByteArray& json, const QVector<int> &playerIndexes)
{
    auto tournament = tournamentServices()->createTournament()->create(json,playerIndexes);
    tournamentServices()->dartsDbCtx()->add(tournament);
    return persistenceServices()->persist()->persistTournamentsChanges();
}
bool DartsContext::isConsistent(const QUuid &tournamentId) const
{
    return tournamentServices()->verifyConsistency()->verify(tournamentId);
}
bool DartsContext::tryRepair(const QUuid &tournamentId)
{
    auto r1 = tournamentServices()->tournamentRepair()->repair(tournamentId);
    auto r2 = persistenceServices()->persist()->persistAllChanges();
    return r1 && r2;
}
void DartsContext::setTournamentWinner(const QUuid &tournamentId, const QString &name)
{
    tournamentServices()->setTnmWinner()->setWinner(tournamentId,name);
    persistenceServices()->persist()->persistTournamentsChanges();
}
QByteArray DartsContext::inputs(const QUuid &tournamentID) const
{
    return inputServices()->inputsToJson()->fromInputs(tournamentID);
}
bool DartsContext::deleteTournaments(const QVector<int> &indexes)
{
    tournamentServices()->removeTournaments()->remove(indexes);
    return persistenceServices()->persist()->persistAllChanges();
}
QByteArray DartsContext::tournaments()
{
    return tournamentServices()->dartsJsonBuilder()->fromTournaments();
}
QByteArray DartsContext::tournament(const int &index) const
{
    return tournamentServices()->dartsJsonBuilder()->fromTournament(index);
}
QByteArray DartsContext::tournament(const QString &id) const
{
    return tournamentServices()->dartsJsonBuilder()->fromTournament(id);
}
QByteArray DartsContext::tournament(const QUuid &id) const
{
    return tournamentServices()->dartsJsonBuilder()->fromTournament(id);
}
bool DartsContext::addInput(const QUuid &tournamentId, const QByteArray &byteArray)
{
    inputServices()->addInputToDb()->add(byteArray,tournamentId);
    return persistenceServices()->persist()->persistInputChanges();
}
bool DartsContext::resetTournament(const QUuid &tournamentId)
{
    tournamentServices()->resetDarts()->reset(tournamentId);
    return persistenceServices()->persist()->persistAllChanges();
}
QByteArray DartsContext::createDartsMetaData(const QUuid &tournamentID)
{
    return tournamentServices()->dartsJsonBuilder()->fromTournament(tournamentID);
}
bool DartsContext::updateTournamentIndex(QUuid tournamentID, const QByteArray &indexByteArray)
{
    indexServices()->updateIndex()->update(indexByteArray,tournamentID);
    return persistenceServices()->persist()->persistTournamentsChanges();
}
QByteArray DartsContext::input(const QUuid &tournamentID, const QString &name, const QByteArray &idxBa) const
{
    return inputServices()->inputToJson()->toJson(tournamentID,name,idxBa);
}
bool DartsContext::hideInput(QUuid tournamentID, QString name, const QByteArray &indexByteArray)
{
    inputServices()->setInputHint()->setHidden(tournamentID,name,indexByteArray);
    indexServices()->updateIndex()->update(indexByteArray,tournamentID);
    return persistenceServices()->persist()->persistAllChanges();
}
bool DartsContext::revealInput(QUuid tournamentID, QString name, const QByteArray &indexByteArray)
{
    inputServices()->setInputHint()->setVisible(tournamentID,name,indexByteArray);
    indexServices()->updateIndex()->update(indexByteArray,tournamentID);
    return persistenceServices()->persist()->persistAllChanges();
}
