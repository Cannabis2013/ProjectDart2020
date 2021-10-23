#include "dartsmodelscontext.h"
void DartsModelsContext::addDartsTournament(const QByteArray& json,const QVector<IModel<QUuid>*> &playerModels)
{
    auto model = tournamentBuilder()->buildTournament(json);
    indexesDbContext()->add(indexBuilder()->index(model->id()))->saveChanges(indexesJsonBuilder());
    setTournamentPlayerDetails()->setDetails(model,playerModels);
    dartsDbContext()->add(model)->saveChanges(tournamentJsonBuilder());
    emit tournamentCreatedAndPersisted();
}
void DartsModelsContext::deleteTournaments(const QVector<int>& indexes)
{
    auto tournamentIds = getTournamentIds()->fromIndexes(indexes,dartsDbContext());
    removeInputsFromDb()->removeByTournamentIds(tournamentIds,inputsDb())->saveChanges(inputJsonBuilder());
    dartsDbContext()->remove(indexes)->saveChanges(tournamentJsonBuilder());
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
    emit sendTournaments(tournamentJsonBuilder()->tournamentsjson(dartsDbContext()->models()));
}
void DartsModelsContext::getGameMode(const int &index)
{
    auto model = dartsDbContext()->model(index);
    emit requestAssembleTournament(model->id(),dynamic_cast<const ITournament*>(model)->gameMode());
}
void DartsModelsContext::addInput(const QByteArray &json)
{
    auto input = dynamic_cast<IPlayerInput*>(inputBuilder()->createInput(json));
    updateIndexes()->update(indexBuilder()->index(json),indexesDbContext())->saveChanges(indexesJsonBuilder());
    inputsDb()->add(input);
    removeInputsFromDb()->removeByHint(input->tournamentId(),HiddenHint,inputsDb())->saveChanges(inputJsonBuilder());
    emit inputModelAdded(json);
}
void DartsModelsContext::updateTournamentIndexes(const QByteArray &json)
{
    auto indexes = indexBuilder()->index(json);
    auto indexOf = indexesDbContext()->indexOf(indexes);
    indexesDbContext()->replace(indexOf,indexes)->saveChanges(indexesJsonBuilder());
    emit tournamentIndexesUpdated(json);
}
void DartsModelsContext::resetTournament(const QUuid &tournamentId)
{
    removeInputsFromDb()->removeInputsByTournamentId(tournamentId,inputsDb())->saveChanges(inputJsonBuilder());
    resetDarts()->reset(tournamentId,dartsDbContext())->saveChanges(tournamentJsonBuilder());
    resetIndexes()->reset(tournamentId,indexBuilder(),indexesDbContext())->saveChanges(indexesJsonBuilder());
    emit tournamentResetSuccess();
}
void DartsModelsContext::setDartsTournamentWinner(const QByteArray& json)
{
    auto winnerModel = winnerInfoBuilder()->create(json);
    auto tournament = dynamic_cast<ITournament*>(getTournament()->tournament(winnerModel.tournamentId,dartsDbContext()));
    tournament->setWinnerId(winnerModel.winnerId);
    tournament->setWinnerName(winnerModel.winnerName);
    dartsDbContext()->saveChanges(tournamentJsonBuilder());
    emit setDartsTournamentWinnerSucces(json);
}
void DartsModelsContext::createDartsKeyValues(const QUuid &tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,dartsDbContext());
    auto json = tournamentJsonBuilder()->tournamentJson(model);
    emit sendDartsDetails(json);
}

void DartsModelsContext::getIndexes(const QUuid &tournamentId)
{
    auto indexesModel = getIndexesModel()->indexes(tournamentId,indexesDbContext());
    emit sendIndexes(indexesJsonBuilder()->indexesJson(indexesModel));
}
void DartsModelsContext::createDartsMetaData(const QUuid &tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,dartsDbContext());
    auto json = tournamentJsonBuilder()->tournamentJson(model);
    emit sendTournamentMeta(json);
}
void DartsModelsContext::hideInput(const QByteArray &json)
{
    auto meta = dartsMetaBuilder()->buildMeta(json);
    auto inputIndex = indexBuilder()->index(json);
    auto reqIndex = indexBuilder()->reqIndex(json);
    updateIndexes()->update(inputIndex,indexesDbContext())->saveChanges(indexesJsonBuilder());
    auto input = getInputFromDb()->get(meta,inputIndex,inputsDb());
    input->setHint(HiddenHint);
    auto reqInput = getInputFromDb()->get(meta,reqIndex,inputsDb());
    inputsDb()->saveChanges(inputJsonBuilder());
    emit hideInputSuccess(inputJsonBuilder()->dartsInputJson(reqInput,meta));
}
void DartsModelsContext::revealInput(const QByteArray &json)
{
    auto meta = dartsMetaBuilder()->buildMeta(json);
    auto indexes = indexBuilder()->index(json);
    updateIndexes()->update(indexes,indexesDbContext())->saveChanges(indexesJsonBuilder());
    auto input = getInputFromDb()->get(meta, indexes, inputsDb());
    input->setHint(DisplayHint);
    inputsDb()->saveChanges(inputJsonBuilder());
    emit revealInputSuccess(inputJsonBuilder()->dartsInputJson(input));
}
void DartsModelsContext::getPlayerDetails(const QUuid& tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,dartsDbContext());
    emit sendAssignedPlayerDetails(tournamentJsonBuilder()->assignedPlayersJson(model));
}
void DartsModelsContext::getTournamentWinnerDetails(const QUuid& tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,dartsDbContext());
    emit sendWinnerDetails(tournamentJsonBuilder()->winnerDetailsJson(model));
}
void DartsModelsContext::getPlayerInputs(const QUuid& tournamentId)
{
    auto inputModels = getInputsFromDb()->inputModels(tournamentId,DisplayHint,inputsDb());
    auto sortedInputModels = sortInputs()->sort(inputModels,sortInputsByIndexes());
    emit sendInputs(inputJsonBuilder()->dartsInputsJson(sortedInputModels));
}
