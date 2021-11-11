#include "dartscontext.h"
void DartsContext::addTournament(const QByteArray& json)
{
    auto tournament = tournamentBuilder()->createTournament(json);
    auto players = _playersContext->playerModels(json);
    setTournamentPlayerDetails()->setDetails(tournament,players);
    dartsDbContext()->add(tournament)->saveChanges(dartsJsonBuilder());
    emit tournamentCreatedAndPersisted();
}
void DartsContext::setPlayerModelsContext(PlayerModelsContext *context)
{
    _playersContext = context;
}

void DartsContext::deleteTournaments(const QVector<int>& indexes)
{
    auto tournamentIds = getTournamentIds()->get(indexes,dartsDbContext());
    removeInputs()->removeByTournamentIds(tournamentIds,inputsDb())->saveChanges(inputsJsonBuilder());
    dartsDbContext()->remove(indexes)->saveChanges(dartsJsonBuilder());
    emit tournamentsDeletedStatus(true);
}
void DartsContext::getTournaments()
{
    emit sendTournaments(dartsJsonBuilder()->tournamentsjson(dartsDbContext()->models()));
}
QFuture<QByteArray> DartsContext::addInput(const QByteArray &json)
{
    return QtConcurrent::run([=]{
        auto tournamentId = dartsMetaBuilder()->buildMeta(json).tournamentId;
        inputsDb()->add(inputBuilder()->createInput(json));
        removeInputs()->removeByHint(tournamentId,HiddenHint,inputsDb());
        auto future = inputsDb()->saveChanges(inputsJsonBuilder());
        if(future.result())
            return json;
        return QByteArray();
    });
}
QFuture<bool> DartsContext::resetTournament(const QUuid &tournamentId)
{
    return QtConcurrent::run([=]{
        auto inputFuture = removeInputs()->removeInputsByTournamentId(tournamentId,inputsDb())->saveChanges(inputsJsonBuilder());
        if(inputFuture.result())
        {
            auto resetFuture = resetDarts()->reset(tournamentId,dartsDbContext())->saveChanges(dartsJsonBuilder());
            return resetFuture.result();
        }
        return false;
    });
}
void DartsContext::setTournamentWinner(const QByteArray& json)
{
    auto winnerModel = winnerInfoBuilder()->create(json);
    auto tournament = dynamic_cast<ITournament*>(getTournament()->get(winnerModel.tournamentId,dartsDbContext()));
    tournament->setWinnerId(winnerModel.winnerId);
    tournament->setWinnerName(winnerModel.winnerName);
    dartsDbContext()->saveChanges(dartsJsonBuilder());
    emit setDartsTournamentWinnerSucces(json);
}
QByteArray DartsContext::createDartsKeyValues(const QUuid &tournamentId)
{
    auto model = getTournament()->get(tournamentId,dartsDbContext());
    auto json = dartsJsonBuilder()->tournamentJson(model);
    emit sendDartsDetails(json);
}
QFuture<bool> DartsContext::updateTournamentIndex(const QByteArray &json)
{
    return QtConcurrent::run([=]{
        auto meta = dartsMetaBuilder()->buildMeta(json);
        auto index = indexBuilder()->index(json);
        auto future = updateIndexes()->update(index,meta,dartsDbContext())->saveChanges(dartsJsonBuilder());
        if(future.result())
            return true;
        return false;
    });
}
QByteArray DartsContext::createDartsValuesJson(const QUuid &tournamentId)
{
    auto darts = getTournament()->get(tournamentId,dartsDbContext());
    auto inputModels = getInputsFromDb()->get(tournamentId,DisplayHint,inputsDb());
    auto sortedInputModels = sortInputs()->sort(inputModels,sortInputsByIndexes());
    JsonBuilder builder;
    builder.add(dartsJsonBuilder()->tournamentJsonObject(darts),"index");
    builder.add(dartsJsonBuilder()->assignedPlayersJson(darts),"players");
    builder.add(inputsJsonBuilder()->jsonArray(sortedInputModels),"inputs");
    builder.add(dartsJsonBuilder()->winnerDetailsJson(darts),"winnerDetails");
    return builder.toByteArray();
}
QByteArray DartsContext::createDartsMetaData(const QUuid &tournamentId)
{
    auto model = getTournament()->get(tournamentId,dartsDbContext());
    auto json = dartsJsonBuilder()->tournamentJson(model);
    return json;
}
QFuture<QByteArray> DartsContext::hideInput(const QByteArray &json)
{
    return QtConcurrent::run([=]{
        auto meta = dartsMetaBuilder()->buildMeta(json);
        auto inputIndex = indexBuilder()->index(json);
        auto reqIndex = indexBuilder()->reqIndex(json);
        getInputFromDb()->get(meta,inputIndex,inputsDb())->setHint(HiddenHint);
        updateIndexes()->update(inputIndex,meta,dartsDbContext());
        auto indexFuture = dartsDbContext()->saveChanges(dartsJsonBuilder());
        auto inputFuture = inputsDb()->saveChanges(inputsJsonBuilder());
        if(indexFuture.result() && inputFuture.result())
        {
            auto reqInput = getInputFromDb()->get(meta,reqIndex,inputsDb());
            auto response = inputsJsonBuilder()->json(reqInput,meta);
            return response;
        }
        return QByteArray();
    });
}
QFuture<QByteArray> DartsContext::revealInput(const QByteArray &json)
{
    return QtConcurrent::run([=]{
        auto meta = dartsMetaBuilder()->buildMeta(json);
        auto inputIndex = indexBuilder()->index(json);
        auto indexFuture = updateIndexes()->update(inputIndex,meta,dartsDbContext())->saveChanges(dartsJsonBuilder());
        if(indexFuture.result())
        {
            auto input = getInputFromDb()->get(meta, inputIndex,inputsDb())->setHint(DisplayHint);
            auto inputFuture = inputsDb()->saveChanges(inputsJsonBuilder());
            auto response = inputsJsonBuilder()->json(input);
            return response;
        }
        return QByteArray();
    });
}
