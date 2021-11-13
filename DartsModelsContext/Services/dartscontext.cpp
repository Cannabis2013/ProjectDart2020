#include "dartscontext.h"

void DartsContext::addTournament(const QByteArray& json, const QVector<int> &playerIndexes)
{
    QtConcurrent::run([=]{
        auto tournament = tournamentBuilder()->createTournament(json);
        auto players = playersContext()->playerModels(playerIndexes);
        setTournamentPlayerDetails()->setDetails(tournament,players);
        auto tournamentFuture = dartsDbContext()->add(tournament)->saveChanges(dartsJsonBuilder());
        if(tournamentFuture.result())
            emit tournamentCreatedAndPersisted();
    });
}
QByteArray DartsContext::tournament(const int &index) const
{
    auto tournament = dartsDbContext()->model(index);
    return dartsJsonBuilder()->tournamentJson(tournament);
}

QByteArray DartsContext::tournament(const QString &id) const
{
    auto tournament = getTournament()->get(QUuid::fromString(id),dartsDbContext());
    return dartsJsonBuilder()->tournamentJson(tournament);
}

QVector<IModel<QUuid> *> DartsContext::assignedPlayers(const QUuid &tournamentId) const
{
    auto tournament = getTournament()->get(tournamentId,dartsDbContext());
    auto playerIds = dynamic_cast<ITournament*>(tournament)->assignedPlayerIds();
    auto players = playersContext()->playerModels(playerIds);
    return players;
}
void DartsContext::deleteTournaments(const QVector<int>& indexes)
{
    QtConcurrent::run([=]{
        auto tournamentIds = getTournamentIds()->get(indexes,dartsDbContext());
        auto removeInputsResult = removeInputs()->removeByTournamentIds(tournamentIds,inputsDb())->saveChanges(inputsJsonBuilder());
        auto removeIndexResult = dartsDbContext()->remove(indexes)->saveChanges(dartsJsonBuilder());
        if(removeInputsResult && removeIndexResult)
            emit tournamentsDeleted();
    });
}
QByteArray DartsContext::tournaments()
{
    return dartsJsonBuilder()->tournamentsjson(dartsDbContext()->models());
}
QFuture<bool> DartsContext::addInput(const QByteArray &json)
{
    return QtConcurrent::run([=]{
        auto tournamentId = dartsMetaBuilder()->buildMeta(json).tournamentId;
        auto input = inputBuilder()->createInput(json);
        inputsDb()->add(input);
        removeInputs()->removeByHint(tournamentId,HiddenHint,inputsDb());
        return inputsDb()->saveChanges(inputsJsonBuilder());
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
    return json;
}
QFuture<bool> DartsContext::updateTournamentIndex(const QUuid &tournament, IDartsIndex *index)
{
    return QtConcurrent::run([=]{
        auto future = updateIndexes()->update(index,tournament,dartsDbContext())->saveChanges(dartsJsonBuilder());
        return future.result();
    });
}

AbstractDartsInput *DartsContext::input(const QUuid &tournament, const QUuid &player, IDartsIndex *index) const
{
    auto meta = dartsMetaBuilder()->buildMeta(tournament,player);
    auto input = getInputFromDb()->get(meta,index,inputsDb());
    return input;
}
QByteArray DartsContext::createDartsValuesJson(const QUuid &tournamentId)
{
    auto darts = getTournament()->get(tournamentId,dartsDbContext());
    auto inputModels = getInputsFromDb()->get(tournamentId,DisplayHint,inputsDb());
    auto sortedInputModels = sortInputs()->sort(inputModels,sortInputsByIndexes());
    JsonBuilder builder(dartsJsonBuilder(),darts,inputsJsonBuilder(),sortedInputModels);
    return builder.get();
}
QByteArray DartsContext::createDartsMetaData(const QUuid &tournamentId)
{
    auto model = getTournament()->get(tournamentId,dartsDbContext());
    auto json = dartsJsonBuilder()->tournamentJson(model);
    return json;
}
QFuture<bool> DartsContext::hideInput(const QUuid &tournament, const QUuid &player, IDartsIndex *index)
{
    return QtConcurrent::run([=]{
        auto meta = dartsMetaBuilder()->buildMeta(tournament,player);
        getInputFromDb()->get(meta,index,inputsDb())->setHint(HiddenHint);
        updateIndexes()->update(index,tournament,dartsDbContext());
        auto indexFuture = dartsDbContext()->saveChanges(dartsJsonBuilder());
        auto inputFuture = inputsDb()->saveChanges(inputsJsonBuilder());
        return indexFuture.result() && inputFuture.result();
    });
}
QFuture<bool> DartsContext::revealInput(const QUuid &tournament, const QUuid &player, IDartsIndex *index)
{
    return QtConcurrent::run([=]{
        auto meta = dartsMetaBuilder()->buildMeta(tournament,player);
        auto indexFuture = updateIndexes()->update(index,tournament,dartsDbContext())->saveChanges(dartsJsonBuilder());
        getInputFromDb()->get(meta, index,inputsDb())->setHint(DisplayHint);
        auto inputFuture = inputsDb()->saveChanges(inputsJsonBuilder());
        return indexFuture.result() && inputFuture.result();
    });
}
