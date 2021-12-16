#include "dartscontext.h"
bool DartsContext::addTournament(const QByteArray& json, const QVector<int> &playerIndexes)
{
    auto tournament = tournamentBuilder()->createModel(json);
    auto players = playersContext()->players(playerIndexes);
    setTournamentPlayerDetails()->setDetails(tournament,players);
    tnmDbCtx()->add(tournament);
    return saveToStorage()->save(tnmDbCtx(),tnmJsonBuilder());
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
QVector<DIptVals> DartsContext::inputs(const QUuid &tournamentId) const {
    auto inputs = getInputsFromDb()->get(tournamentId,DisplayHint,inputsDb());
    return createInputValues()->create(inputs);
}
QVector<IPlayer*> DartsContext::players(const QUuid &tournamentId) const
{
    auto tournament = getTournament()->get(tournamentId,tnmDbCtx());
    auto playerIds = dynamic_cast<ITournament*>(tournament)->playerNames();
    return playersContext()->players(playerIds);
}
bool DartsContext::deleteTournaments(const QVector<int> &indexes)
{
    auto tournamentIds = getTournamentIds()->get(indexes,tnmDbCtx());
    removeInputs()->removeByTournamentIds(tournamentIds,inputsDb());
    tnmDbCtx()->remove(indexes);
    return saveToStorage()->save({{tnmDbCtx(),tnmJsonBuilder()},{inputsDb(),inputsToJson()}});
}
bool DartsContext::addInput(const QUuid &tournamentId, const DIptVals &ctrlIpt)
{
    auto player = playersContext()->player(ctrlIpt.playerName);
    inputsDb()->add(inputBuilder()->convert(ctrlIpt,tournamentId, player->id()));
    removeInputs()->removeByHint(tournamentId,HiddenHint,inputsDb());
    return saveToStorage()->save(inputsDb(),inputsToJson());
}
bool DartsContext::resetTournament(const QUuid &tournamentId)
{
    removeInputs()->removeInputsByTournamentId(tournamentId,inputsDb());
    resetDarts()->reset(tournamentId,tnmDbCtx());
    return saveToStorage()->save({{tnmDbCtx(),tnmJsonBuilder()},{inputsDb(),inputsToJson()}});
}
bool DartsContext::updateTournamentIndex(QUuid tournament, const TnmVals &idxVals)
{
    auto index = indexBuilder()->create(idxVals);
    updateIndexes()->update(index,tournament,tnmDbCtx());
    return saveToStorage()->save(tnmDbCtx(),tnmJsonBuilder());
}
DIptVals DartsContext::input(const QUuid &tournament, const QString &name, const TnmVals &idxVals) const
{
    auto index = indexBuilder()->create(idxVals);
    auto playerId = playersContext()->player(name)->id();
    auto meta = createMeta()->create(tournament,playerId);
    auto input = getInputsFromDb()->get(meta,index,inputsDb());
    return createInputValues()->create(input);
}
bool DartsContext::hideInput(QUuid tournament, QString name, TnmVals idxVals)
{
    auto idx = indexBuilder()->create(idxVals);
    auto playerId = playersContext()->player(name)->id();
    auto meta = createMeta()->create(tournament,playerId);
    getInputsFromDb()->get(meta,idx,inputsDb())->setHint(HiddenHint);
    updateIndexes()->update(idx,tournament,tnmDbCtx());
    saveToStorage()->save(tnmDbCtx(),tnmJsonBuilder());
    return saveToStorage()->save({{tnmDbCtx(),tnmJsonBuilder()},{inputsDb(),inputsToJson()}});
}
bool DartsContext::revealInput(QUuid tournament, QString name, const TnmVals &idxVals)
{
    auto index = indexBuilder()->create(idxVals);
    auto playerId = playersContext()->player(name)->id();
    auto meta = createMeta()->create(tournament,playerId);
    updateIndexes()->update(index,tournament,tnmDbCtx());
    getInputsFromDb()->get(meta,index,inputsDb())->setHint(DisplayHint);
    return saveToStorage()->save({{tnmDbCtx(),tnmJsonBuilder()},{inputsDb(),inputsToJson()}});
}
