#include "dartsctx.h"
void DartsCtx::addTournament(const QByteArray& json, const QVector<int> &playerIndexes)
{
    auto tournament = tournamentBuilder()->createTournament(json);
    auto players = playersContext()->playerModels(playerIndexes);
    setTournamentPlayerDetails()->setDetails(tournament,players);
    dartsDbCtx()->add(tournament);
    RunLater::run<bool>(dartsDbCtx()->saveChanges(dartsJsonBuilder()),[=](const bool &result){
        if(result) emit tournamentCreatedOk();
        else emit tournamentCreatedFail();
    });
}
QByteArray DartsCtx::tournament(const int &index) const
{
    auto tournament = dartsDbCtx()->model(index);
    return dartsJsonBuilder()->tournamentJson(tournament);
}
QByteArray DartsCtx::tournament(const QString &id) const
{
    auto tournament = getTournament()->get(QUuid::fromString(id),dartsDbCtx());
    return dartsJsonBuilder()->tournamentJson(tournament);
}
AbstractDartsTournament *DartsCtx::tournament(const QUuid &id) const
{
    return dynamic_cast<AbstractDartsTournament*>(getTournament()->get(id,dartsDbCtx()));
}
bool DartsCtx::isConsistent(const QUuid &tournamentId) const
{
    auto tournament = getTournament()->get(tournamentId,dartsDbCtx());
    auto inputs = getInputsFromDb()->get(tournamentId,inputsDb());
    return verifyConsistency()->verify(tournament,inputs,playersContext());
}
void DartsCtx::tryRepair(const QUuid &tournamentId)
{
    QtConcurrent::run([=]{
        auto tournament = getTournament()->get(tournamentId,dartsDbCtx());
        auto inputs = getInputsFromDb()->get(tournamentId,inputsDb());
        auto result = tournamentRepair()->repair(tournament,inputs,playersContext());
        auto tFuture = dartsDbCtx()->saveChanges(dartsJsonBuilder());
        auto iFuture = inputsDb()->saveChanges(inputsJsonBuilder());
        if(tFuture.result() && iFuture.result())
        {
            auto json = dartsJsonBuilder()->tournamentJson(tournament);
            emit repairCompleted(result, json);
        }});
}
QVector<IModel<QUuid> *> DartsCtx::tournamentInputs(const QUuid &tournamentId) const
{
    auto inputs = getInputsFromDb()->get(tournamentId,inputsDb());
    return inputs;
}
QVector<IModel<QUuid> *> DartsCtx::assignedPlayers(const QUuid &tournamentId) const
{
    auto tournament = getTournament()->get(tournamentId,dartsDbCtx());
    auto playerIds = dynamic_cast<ITournament*>(tournament)->playerNames();
    auto players = playersContext()->playerModels(playerIds);
    return players;
}
void DartsCtx::deleteTournaments(const QVector<int> &indexes)
{
    QtConcurrent::run([=]{
        auto tournamentIds = getTournamentIds()->get(indexes,dartsDbCtx());
        auto removeInputsResult = removeInputs()->removeByTournamentIds(tournamentIds,inputsDb())->saveChanges(inputsJsonBuilder());
        auto removeIndexResult = dartsDbCtx()->remove(indexes)->saveChanges(dartsJsonBuilder());
        if(removeInputsResult.result() && removeIndexResult.result())
            emit tournamentsDeleted();

    });
}
QByteArray DartsCtx::tournaments()
{
    return dartsJsonBuilder()->tournamentsjson(dartsDbCtx()->models());
}
void DartsCtx::addInput(const QUuid &tournamentId, AbstractDartsInput *input, std::function<void()> func)
{
    inputsDb()->add(input);
    removeInputs()->removeByHint(tournamentId,HiddenHint,inputsDb());
    RunLater::run<bool>(inputsDb()->saveChanges(inputsJsonBuilder()),func);
}
QFuture<bool> DartsCtx::resetTournament(const QUuid &tournamentId)
{
    return QtConcurrent::run([=]{
        auto inputFuture = removeInputs()->removeInputsByTournamentId(tournamentId,inputsDb())->saveChanges(inputsJsonBuilder());
        auto resetFuture = resetDarts()->reset(tournamentId,dartsDbCtx())->saveChanges(dartsJsonBuilder());
        return inputFuture.result() && resetFuture.result();
    });
}
void DartsCtx::setTournamentWinner(const QByteArray& json)
{
    auto winnerModel = winnerInfoBuilder()->create(json);
    auto tournament = dynamic_cast<ITournament*>(getTournament()->get(winnerModel.tournamentId,dartsDbCtx()));
    tournament->setWinnerId(winnerModel.winnerId);
    tournament->setWinnerName(winnerModel.winnerName);
    dartsDbCtx()->saveChanges(dartsJsonBuilder());
    emit setDartsTournamentWinnerSucces(json);
}
QFuture<bool> DartsCtx::updateTournamentIndex(const QUuid &tournament, IDartsIndex *index)
{
    return QtConcurrent::run([=]{
        auto future = updateIndexes()->update(index,tournament,dartsDbCtx())->saveChanges(dartsJsonBuilder());
        return future.result();
    });
}
AbstractDartsInput *DartsCtx::input(const QUuid &tournament, const QUuid &player, IDartsIndex *index) const
{
    auto meta = dartsMetaBuilder()->buildMeta(tournament,player);
    auto input = getInputFromDb()->get(meta,index,inputsDb());
    return input;
}
QByteArray DartsCtx::createDartsMetaData(const QUuid &tournamentId)
{
    auto model = getTournament()->get(tournamentId,dartsDbCtx());
    auto json = dartsJsonBuilder()->tournamentJson(model);
    return json;
}
void DartsCtx::hideInput(const QUuid &tournament, const QUuid &playerId, IDartsIndex *index, std::function<void ()> func)
{
    auto meta = dartsMetaBuilder()->buildMeta(tournament,playerId);
    getInputFromDb()->get(meta,index,inputsDb())->setHint(HiddenHint);
    updateIndexes()->update(index,tournament,dartsDbCtx());
    RunLater::run<bool>(dartsDbCtx()->saveChanges(dartsJsonBuilder()),[=](const bool &r1){
        RunLater::run<bool>(inputsDb()->saveChanges(inputsJsonBuilder()),[=](const bool &r2){
            if(r1 && r2)func();
        });
    });
}
void DartsCtx::revealInput(const QUuid &tournament, const QUuid &player, IDartsIndex *index, std::function<void()> func)
{
    auto meta = dartsMetaBuilder()->buildMeta(tournament,player);
    updateIndexes()->update(index,tournament,dartsDbCtx());
    RunLater::run<bool>(dartsDbCtx()->saveChanges(dartsJsonBuilder()),[=](const bool &result){
        if(!result) return;
        getInputFromDb()->get(meta, index,inputsDb())->setHint(DisplayHint);
        RunLater::run<bool>(inputsDb()->saveChanges(inputsJsonBuilder()),[=](const bool &result){
            if(!result) return;
            func();
        });
    });
}
