#include "dartsmodelscontext.h"
void DartsModelsContext::addDartsTournament(const QByteArray& json,const QVector<IModel<QUuid>*> &playerModels)
{
    auto model = tournamentBuilder()->createTournament(json);
    setTournamentPlayerDetails()->setDetails(model,playerModels);
    dartsDbContext()->add(model)->saveChanges(dartsJsonBuilder());
    emit tournamentCreatedAndPersisted();
}
void DartsModelsContext::deleteTournaments(const QVector<int>& indexes)
{
    auto tournamentIds = getTournamentIds()->get(indexes,dartsDbContext());
    removeInputs()->removeByTournamentIds(tournamentIds,inputsDb())->saveChanges(inputJsonBuilder());
    dartsDbContext()->remove(indexes)->saveChanges(dartsJsonBuilder());
    emit tournamentsDeletedStatus(true);
}
void DartsModelsContext::getOrderedInputs(const QUuid &tournamentId)
{
    auto models = getInputsFromDb()->inputModels(tournamentId,DisplayHint,inputsDb());
    auto orderedDartsPointModels = sortInputs()->sort(models,sortInputsByIndexes());
    emit sendOrderedInputs(inputJsonBuilder()->dartsInputsJson(orderedDartsPointModels));
}
void DartsModelsContext::getTournaments()
{
    emit sendTournaments(dartsJsonBuilder()->tournamentsjson(dartsDbContext()->models()));
}
void DartsModelsContext::getGameMode(const int &index)
{
    auto model = dartsDbContext()->model(index);
    emit requestAssembleTournament(model->id(),dynamic_cast<const ITournament*>(model)->gameMode());
}
void DartsModelsContext::addInput(const QByteArray &json)
{
    auto meta = dartsMetaBuilder()->buildMeta(json);
    auto input = inputBuilder()->createInput(json);
    inputsDb()->add(input);
    removeInputs()->removeByHint(meta.tournamentId,HiddenHint,inputsDb())->saveChanges(inputJsonBuilder());
    emit inputAdded(json);
}
void DartsModelsContext::resetTournament(const QUuid &tournamentId)
{
    removeInputs()->removeInputsByTournamentId(tournamentId,inputsDb())->saveChanges(inputJsonBuilder());
    resetDartsIndexes()->reset(tournamentId,dartsDbContext());
    resetDarts()->reset(tournamentId,dartsDbContext())->saveChanges(dartsJsonBuilder());
    emit tournamentResetSuccess();
}
void DartsModelsContext::setDartsTournamentWinner(const QByteArray& json)
{
    auto winnerModel = winnerInfoBuilder()->create(json);
    auto tournament = dynamic_cast<ITournament*>(getTournament()->tournament(winnerModel.tournamentId,dartsDbContext()));
    tournament->setWinnerId(winnerModel.winnerId);
    tournament->setWinnerName(winnerModel.winnerName);
    dartsDbContext()->saveChanges(dartsJsonBuilder());
    emit setDartsTournamentWinnerSucces(json);
}
void DartsModelsContext::createDartsKeyValues(const QUuid &tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,dartsDbContext());
    auto json = dartsJsonBuilder()->tournamentJson(model);
    emit sendDartsDetails(json);
}

void DartsModelsContext::setTournamentIndex(const QByteArray &json)
{
    auto meta = dartsMetaBuilder()->buildMeta(json);
    auto index = indexBuilder()->index(json);
    updateIndexes()->update(index,meta,dartsDbContext())->saveChanges(dartsJsonBuilder());
    emit tournamentIndexUpdated(json);
}

void DartsModelsContext::getIndexes(const QUuid &tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,dartsDbContext());
    emit sendIndexes(dartsJsonBuilder()->tournamentJson(model));
}
void DartsModelsContext::createDartsMetaData(const QUuid &tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,dartsDbContext());
    auto json = dartsJsonBuilder()->tournamentJson(model);
    emit sendTournamentMeta(json);
}
void DartsModelsContext::hideInput(const QByteArray &json)
{
    auto meta = dartsMetaBuilder()->buildMeta(json);
    auto inputIndex = indexBuilder()->index(json);
    auto reqIndex = indexBuilder()->reqIndex(json);
    updateIndexes()->update(inputIndex,meta,dartsDbContext())->saveChanges(dartsJsonBuilder());
    getInputFromDb()->get(meta,inputIndex,inputsDb())->setHint(HiddenHint);
    inputsDb()->saveChanges(inputJsonBuilder());
    auto reqInput = getInputFromDb()->get(meta,reqIndex,inputsDb());
    emit hideInputSuccess(inputJsonBuilder()->dartsInputJson(reqInput,meta));
}
void DartsModelsContext::revealInput(const QByteArray &json)
{
    auto meta = dartsMetaBuilder()->buildMeta(json);
    auto inputIndex = indexBuilder()->index(json);
    updateIndexes()->update(inputIndex,meta,dartsDbContext())->saveChanges(dartsJsonBuilder());
    auto input = getInputFromDb()->get(meta, inputIndex,inputsDb())->setHint(DisplayHint);
    inputsDb()->saveChanges(inputJsonBuilder());
    emit revealInputSuccess(inputJsonBuilder()->dartsInputJson(input));
}
void DartsModelsContext::getPlayerDetails(const QUuid& tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,dartsDbContext());
    emit sendAssignedPlayerDetails(dartsJsonBuilder()->assignedPlayersJson(model));
}
void DartsModelsContext::getTournamentWinnerDetails(const QUuid& tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,dartsDbContext());
    emit sendWinnerDetails(dartsJsonBuilder()->winnerDetailsJson(model));
}
void DartsModelsContext::getPlayerInputs(const QUuid& tournamentId)
{
    auto inputModels = getInputsFromDb()->inputModels(tournamentId,DisplayHint,inputsDb());
    auto sortedInputModels = sortInputs()->sort(inputModels,sortInputsByIndexes());
    emit sendInputs(inputJsonBuilder()->dartsInputsJson(sortedInputModels));
}
