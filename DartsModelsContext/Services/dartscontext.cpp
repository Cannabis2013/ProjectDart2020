#include "dartscontext.h"
bool DartsContext::addTournament(const QByteArray& json, const QVector<int> &playerIndexes)
{
    auto tournament = tournamentBuilder()->createModel(json);
    auto players = playersContext()->players(playerIndexes);
    setTournamentPlayerDetails()->setDetails(tournament,players);
    tnmDbCtx()->add(tournament);
    return saveToStorage()->save(tnmDbCtx(),tnmJsonBuilder());
}
QByteArray DartsContext::tournament(const int &index) const
{
    auto tournament = tnmDbCtx()->model(index);
    return tnmJsonBuilder()->create(tournament);
}
QByteArray DartsContext::tournament(const QString &id) const
{
    auto tournament = getTournament()->get(QUuid::fromString(id),tnmDbCtx());
    return tnmJsonBuilder()->create(tournament);
}
AbstractDartsTournament *DartsContext::tournament(const QUuid &id) const
{
    return dynamic_cast<AbstractDartsTournament*>(getTournament()->get(id,tnmDbCtx()));
}
bool DartsContext::isConsistent(const QUuid &tournamentId) const
{
    auto tournament = getTournament()->get(tournamentId,tnmDbCtx());
    auto inputs = getInputsFromDb()->get(tournamentId,inputsDb());
    return verifyConsistency()->verify(tournament,inputs,playersContext());
}
bool DartsContext::tryRepair(const QUuid &tournamentId)
{
    auto tournament = getTournament()->get(tournamentId,tnmDbCtx());
    auto inputs = getInputsFromDb()->get(tournamentId,inputsDb());
    tournamentRepair()->repair(tournament,inputs,playersContext());
    return saveToStorage()->save({{tnmDbCtx(),tnmJsonBuilder()},{inputsDb(),inputsToJson()}});
}
bool DartsContext::setTournamentWinner(const QUuid &tournamentId, const QString &name)
{
    auto player = playersContext()->player(name);
    auto tournament = getTournament()->get(tournamentId,tnmDbCtx());
    tournament->setWinnerId(player->id());
    tournament->setWinnerName(player->name());
    return saveToStorage()->save(tnmDbCtx(),tnmJsonBuilder());
}
QVector<AbstractDartsInput *> DartsContext::inputs(const QUuid &tournamentId) const
{
    auto inputs = getInputsFromDb()->get(tournamentId,inputsDb());
    return inputs;
}
QVector<IPlayerModel*> DartsContext::players(const QUuid &tournamentId) const
{
    auto tournament = getTournament()->get(tournamentId,tnmDbCtx());
    auto playerIds = dynamic_cast<ITournament*>(tournament)->playerNames();
    auto players = playersContext()->players(playerIds);
    return players;
}
bool DartsContext::deleteTournaments(const QVector<int> &indexes)
{
    auto tournamentIds = getTournamentIds()->get(indexes,tnmDbCtx());
    removeInputs()->removeByTournamentIds(tournamentIds,inputsDb());
    tnmDbCtx()->remove(indexes);
    return saveToStorage()->save({{tnmDbCtx(),tnmJsonBuilder()},{inputsDb(),inputsToJson()}});
}
QByteArray DartsContext::tournaments()
{
    auto tournaments = tnmDbCtx()->models();
    return tnmJsonBuilder()->create(tournaments);
}
bool DartsContext::addInput(QUuid tournamentId, DIptVals iptVals)
{
    auto player = playersContext()->player(iptVals.playerName);
    inputsDb()->add(inputBuilder()->create(iptVals,tournamentId, player->id()));
    removeInputs()->removeByHint(tournamentId,HiddenHint,inputsDb());
    return saveToStorage()->save(inputsDb(),inputsToJson());
}
bool DartsContext::resetTournament(const QUuid &tournamentId)
{
    removeInputs()->removeInputsByTournamentId(tournamentId,inputsDb());
    resetDarts()->reset(tournamentId,tnmDbCtx());
    return saveToStorage()->save({{tnmDbCtx(),tnmJsonBuilder()},{inputsDb(),inputsToJson()}});
}
bool DartsContext::updateTournamentIndex(QUuid tournament, IDartsIndex *index)
{
    updateIndexes()->update(index,tournament,tnmDbCtx());
    return saveToStorage()->save(tnmDbCtx(),tnmJsonBuilder());
}
AbstractDartsInput *DartsContext::input(const QUuid &tournament, const QString &name, IDartsIndex *index) const
{
    auto playerId = playersContext()->player(name)->id();
    auto meta = dartsMetaBuilder()->buildMeta(tournament,playerId);
    auto input = getInputsFromDb()->get(meta,index,inputsDb());
    return input;
}
QByteArray DartsContext::createDartsMetaData(const QUuid &tournamentId)
{
    auto model = getTournament()->get(tournamentId,tnmDbCtx());
    auto json = tnmJsonBuilder()->create(model);
    return json;
}
bool DartsContext::hideInput(QUuid tournament, QString name, IDartsIndex *index)
{
    auto playerId = playersContext()->player(name)->id();
    auto meta = dartsMetaBuilder()->buildMeta(tournament,playerId);
    getInputsFromDb()->get(meta,index,inputsDb())->setHint(HiddenHint);
    updateIndexes()->update(index,tournament,tnmDbCtx());
    saveToStorage()->save(tnmDbCtx(),tnmJsonBuilder());
    return saveToStorage()->save({{tnmDbCtx(),tnmJsonBuilder()},{inputsDb(),inputsToJson()}});
}
bool DartsContext::revealInput(QUuid tournament, QString name, IDartsIndex *index)
{
    auto playerId = playersContext()->player(name)->id();
    auto meta = dartsMetaBuilder()->buildMeta(tournament,playerId);
    updateIndexes()->update(index,tournament,tnmDbCtx());
    getInputsFromDb()->get(meta, index,inputsDb())->setHint(DisplayHint);
    return saveToStorage()->save({{tnmDbCtx(),tnmJsonBuilder()},{inputsDb(),inputsToJson()}});

}
