#include "dartscontext.h"
void DartsContext::addTournament(const QByteArray& json, const QVector<int> &playerIndexes)
{
    QtConcurrent::run([=]{
        auto tournament = tournamentBuilder()->createModel(json);
        auto players = playersContext()->playerModels(playerIndexes);
        setTournamentPlayerDetails()->setDetails(tournament,players);
        dartsDbCtx()->add(tournament);
        auto result = saveToStorage()->save(dartsDbCtx(),dtsJsonBuilder());
        if(result) emit tournamentCreatedOk();
        else emit tournamentCreatedFail();
    });
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
    auto players = playersContext()->playerModels(playerIds);
    return players;
}
void DartsContext::deleteTournaments(const QVector<int> &indexes)
{
    QtConcurrent::run([=]{
        auto tournamentIds = getTournamentIds()->get(indexes,dartsDbCtx());
        removeInputs()->removeByTournamentIds(tournamentIds,inputsDb());
        auto result = saveToStorage()->save(inputsDb(),inputsToJson());
        dartsDbCtx()->remove(indexes);
        auto removeIndexResult = saveToStorage()->save(dartsDbCtx(),dtsJsonBuilder());
        if(result && removeIndexResult) emit tournamentsDeleted();
    });
}
QByteArray DartsContext::tournaments()
{
    return dtsJsonBuilder()->create(dartsDbCtx()->models());
}
void DartsContext::addInput(const QUuid &tournamentId, DIptVals iptVals, std::function<void()> func)
{
    QtConcurrent::run([=,&iptVals]{
        inputsDb()->add(inputBuilder()->create(iptVals,tournamentId));
        removeInputs()->removeByHint(tournamentId,HiddenHint,inputsDb());
        auto result = saveToStorage()->save(inputsDb(),inputsToJson());
        if(result) func();
    });
}
QFuture<bool> DartsContext::resetTournament(const QUuid &tournamentId)
{
    return QtConcurrent::run([=]{
        removeInputs()->removeInputsByTournamentId(tournamentId,inputsDb());
        auto result = saveToStorage()->save(inputsDb(),inputsToJson());
        resetDarts()->reset(tournamentId,dartsDbCtx());
        auto resetFuture = saveToStorage()->save(dartsDbCtx(),dtsJsonBuilder());
        return result && resetFuture;
    });
}
void DartsContext::setTournamentWinner(const QByteArray& json)
{
    QtConcurrent::run([=]{
        auto winnerModel = winnerInfoBuilder()->create(json);
        auto tournament = dynamic_cast<ITournament*>(getTournament()->get(winnerModel.tournamentId,dartsDbCtx()));
        tournament->setWinnerId(winnerModel.winnerId);
        tournament->setWinnerName(winnerModel.winnerName);
        auto result = saveToStorage()->save(dartsDbCtx(),dtsJsonBuilder());
        if(result) emit setDartsTournamentWinnerSucces(json);
    });
}
void DartsContext::updateTournamentIndex(const QUuid &tournament, IDartsIndex *index, std::function<void()> func)
{
    QtConcurrent::run([=]{
        updateIndexes()->update(index,tournament,dartsDbCtx());
        auto result = saveToStorage()->save(dartsDbCtx(),dtsJsonBuilder());
        if(result) func();
    });
}
AbstractDartsInput *DartsContext::input(const QUuid &tournament, const QUuid &player, IDartsIndex *index) const
{
    auto meta = dartsMetaBuilder()->buildMeta(tournament,player);
    auto input = getInputsFromDb()->get(meta,index,inputsDb());
    return input;
}
QByteArray DartsContext::createDartsMetaData(const QUuid &tournamentId)
{
    auto model = getTournament()->get(tournamentId,dartsDbCtx());
    auto json = dtsJsonBuilder()->create(model);
    return json;
}
void DartsContext::hideInput(const QUuid &tournament, const QUuid &playerId, IDartsIndex *index, std::function<void ()> func)
{
    QtConcurrent::run([=]{
        auto meta = dartsMetaBuilder()->buildMeta(tournament,playerId);
        getInputsFromDb()->get(meta,index,inputsDb())->setHint(HiddenHint);
        updateIndexes()->update(index,tournament,dartsDbCtx());
        saveToStorage()->save(dartsDbCtx(),dtsJsonBuilder());
        auto r1 = saveToStorage()->save(dartsDbCtx(),dtsJsonBuilder());
        auto r2 = saveToStorage()->save(inputsDb(),inputsToJson());
        if(r1 && r2) func();
    });
}
void DartsContext::revealInput(const QUuid &tournament, const QUuid &player, IDartsIndex *index, std::function<void()> func)
{
    QtConcurrent::run([=]{
        auto meta = dartsMetaBuilder()->buildMeta(tournament,player);
        updateIndexes()->update(index,tournament,dartsDbCtx());
        getInputsFromDb()->get(meta, index,inputsDb())->setHint(DisplayHint);
        auto r1 = saveToStorage()->save(dartsDbCtx(),dtsJsonBuilder());
        auto r2 = saveToStorage()->save(inputsDb(),inputsToJson());
        if(r1 && r2) func();
    });
}
