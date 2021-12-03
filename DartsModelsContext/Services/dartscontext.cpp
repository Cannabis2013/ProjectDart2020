#include "dartscontext.h"
bool DartsContext::addTournament(const QByteArray& json, const QVector<int> &playerIndexes)
{
    auto tournament = tournamentBuilder()->createModel(json);
    auto players = playersContext()->players(playerIndexes);
    setTournamentPlayerDetails()->setDetails(tournament,players);
    dartsDbCtx()->add(tournament);
    return saveToStorage()->save(dartsDbCtx(),dtsJsonBuilder());
}
QByteArray DartsContext::tournament(const int &index) const
{
    auto tournament = dartsDbCtx()->model(index);
    return dtsJsonBuilder()->create(tournament);
}
QByteArray DartsContext::tournament(const QString &id) const
{
    auto tournament = getTournament()->get(QUuid::fromString(id),dartsDbCtx());
    return dtsJsonBuilder()->create(tournament);
}
AbstractDartsTournament *DartsContext::tournament(const QUuid &id) const
{
    return dynamic_cast<AbstractDartsTournament*>(getTournament()->get(id,dartsDbCtx()));
}
bool DartsContext::isConsistent(const QUuid &tournamentId) const
{
    auto tournament = getTournament()->get(tournamentId,dartsDbCtx());
    auto inputs = getInputsFromDb()->get(tournamentId,inputsDb());
    return verifyConsistency()->verify(tournament,inputs,playersContext());
}
void DartsContext::tryRepair(const QUuid &tournamentId)
{
    QtConcurrent::run([=]{
        auto tournament = getTournament()->get(tournamentId,dartsDbCtx());
        auto inputs = getInputsFromDb()->get(tournamentId,inputsDb());
        auto result = tournamentRepair()->repair(tournament,inputs,playersContext());
        auto tnmSaved = saveToStorage()->save(dartsDbCtx(),dtsJsonBuilder());
        auto iptsSaved = saveToStorage()->save(inputsDb(),inputsToJson());
        if(tnmSaved && iptsSaved)
            emit repairCompleted(result, dtsJsonBuilder()->create(tournament));
    });
}
QVector<AbstractDartsInput *> DartsContext::inputs(const QUuid &tournamentId) const
{
    auto inputs = getInputsFromDb()->get(tournamentId,inputsDb());
    return inputs;
}
QVector<IPlayerModel*> DartsContext::players(const QUuid &tournamentId) const
{
    auto tournament = getTournament()->get(tournamentId,dartsDbCtx());
    auto playerIds = dynamic_cast<ITournament*>(tournament)->playerNames();
    auto players = playersContext()->players(playerIds);
    return players;
}
bool DartsContext::deleteTournaments(const QVector<int> &indexes)
{
    auto tournamentIds = getTournamentIds()->get(indexes,dartsDbCtx());
    removeInputs()->removeByTournamentIds(tournamentIds,inputsDb());
    dartsDbCtx()->remove(indexes);
    return saveToStorage()->save({{dartsDbCtx(),dtsJsonBuilder()},{inputsDb(),inputsToJson()}});
}
QByteArray DartsContext::tournaments()
{
    return dtsJsonBuilder()->create(dartsDbCtx()->models());
}
bool DartsContext::addInput(QUuid tournamentId, DIptVals iptVals)
{
    auto player = playersContext()->playerModel(iptVals.playerName);
    inputsDb()->add(inputBuilder()->create(iptVals,tournamentId, player->id()));
    removeInputs()->removeByHint(tournamentId,HiddenHint,inputsDb());
    return saveToStorage()->save(inputsDb(),inputsToJson());
}
bool DartsContext::resetTournament(const QUuid &tournamentId)
{
    removeInputs()->removeInputsByTournamentId(tournamentId,inputsDb());
    resetDarts()->reset(tournamentId,dartsDbCtx());
    return saveToStorage()->save({{dartsDbCtx(),dtsJsonBuilder()},{inputsDb(),inputsToJson()}});
}
bool DartsContext::setTournamentWinner(const QByteArray& json)
{
    auto winnerModel = winnerInfoBuilder()->create(json);
    auto tournament = dynamic_cast<ITournament*>(getTournament()->get(winnerModel.tournamentId,dartsDbCtx()));
    tournament->setWinnerId(winnerModel.winnerId);
    tournament->setWinnerName(winnerModel.winnerName);
    return saveToStorage()->save(dartsDbCtx(),dtsJsonBuilder());
}
bool DartsContext::updateTournamentIndex(QUuid tournament, IDartsIndex *index)
{
    updateIndexes()->update(index,tournament,dartsDbCtx());
    return saveToStorage()->save(dartsDbCtx(),dtsJsonBuilder());
}
AbstractDartsInput *DartsContext::input(const QUuid &tournament, const QString &name, IDartsIndex *index) const
{
    auto playerId = playersContext()->playerModel(name)->id();
    auto meta = dartsMetaBuilder()->buildMeta(tournament,playerId);
    auto input = getInputsFromDb()->get(meta,index,inputsDb());
    return input;
}
QByteArray DartsContext::createDartsMetaData(const QUuid &tournamentId)
{
    auto model = getTournament()->get(tournamentId,dartsDbCtx());
    auto json = dtsJsonBuilder()->create(model);
    return json;
}
bool DartsContext::hideInput(QUuid tournament, QString name, IDartsIndex *index)
{
    auto playerId = playersContext()->playerModel(name)->id();
    auto meta = dartsMetaBuilder()->buildMeta(tournament,playerId);
    getInputsFromDb()->get(meta,index,inputsDb())->setHint(HiddenHint);
    updateIndexes()->update(index,tournament,dartsDbCtx());
    saveToStorage()->save(dartsDbCtx(),dtsJsonBuilder());
    return saveToStorage()->save({{dartsDbCtx(),dtsJsonBuilder()},{inputsDb(),inputsToJson()}});
}
bool DartsContext::revealInput(QUuid tournament, QString name, IDartsIndex *index)
{
    auto playerId = playersContext()->playerModel(name)->id();
    auto meta = dartsMetaBuilder()->buildMeta(tournament,playerId);
    updateIndexes()->update(index,tournament,dartsDbCtx());
    getInputsFromDb()->get(meta, index,inputsDb())->setHint(DisplayHint);
    return saveToStorage()->save({{dartsDbCtx(),dtsJsonBuilder()},{inputsDb(),inputsToJson()}});

}
