#include "dartsmodelscontext.h"

void DartsModelsContext::addDartsTournament(const QByteArray& json,const QVector<IModel<QUuid>*> &playerModels)
{
    auto model = tournamentBuilder()->buildTournament(json);
    indexesDbContext()->add(indexesBuilder()->buildIndexes(model->id()))->saveChanges(indexesJsonBuilder());
    setTournamentPlayerDetails()->setDetails(model,playerModels);
    tournamentsDbContext()->add(model)->saveChanges(tournamentJsonBuilder());
    emit tournamentCreatedAndPersisted();
}
void DartsModelsContext::deleteTournaments(const QVector<int>& indexes)
{
    auto tournamentIds = getTournamentIds()->fromIndexes(indexes,tournamentsDbContext());
    removeInputsFromDb()->removeByTournamentIds(tournamentIds,inputsDb())->saveChanges(inputJsonBuilder());
    tournamentsDbContext()->remove(indexes)->saveChanges(tournamentJsonBuilder());
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
    auto json = tournamentJsonBuilder()->tournamentsjson(tournamentsDbContext()->models());
    emit sendTournaments(json);
}
void DartsModelsContext::getGameMode(const int &index)
{
    auto model = tournamentsDbContext()->model(index);
    emit requestAssembleTournament(model->id(),dynamic_cast<const ITournament*>(model)->gameMode());
}
void DartsModelsContext::addInput(const QByteArray &json)
{
    auto input = dynamic_cast<IPlayerInput*>(inputBuilder()->createInput(json));
    updateIndexes()->update(indexesBuilder()->buildIndexes(json),indexesDbContext())->saveChanges(indexesJsonBuilder());
    inputsDb()->add(input);
    removeInputsFromDb()->removeByHint(input->tournamentId(),HiddenHint,inputsDb())->saveChanges(inputJsonBuilder());
    emit inputModelAdded(json);
}
void DartsModelsContext::updateTournamentIndexes(const QByteArray &json)
{
    auto indexes = indexesBuilder()->buildIndexes(json);
    auto indexOf = indexesDbContext()->indexOf(indexes);
    indexesDbContext()->replace(indexOf,indexes)->saveChanges(indexesJsonBuilder());
    emit tournamentIndexesUpdated(json);
}
void DartsModelsContext::resetTournament(const QUuid &tournamentId)
{
    removeInputsFromDb()->removeInputsByTournamentId(tournamentId,inputsDb())->saveChanges(inputJsonBuilder());
    auto tournament = dynamic_cast<ITournament*>(getTournament()->tournament(tournamentId,tournamentsDbContext()));
    tournament->setWinnerId(QUuid());
    tournament->setWinnerName(QString());
    tournamentsDbContext()->saveChanges(tournamentJsonBuilder());
    auto indexesModel = getIndexesModel()->indexesModel(tournamentId,indexesDbContext());
    auto indexOf = indexesDbContext()->indexOf(indexesModel);
    indexesDbContext()->replace(indexOf,indexesBuilder()->buildIndexes(tournamentId))->saveChanges(indexesJsonBuilder());
    emit tournamentResetSuccess();
}
void DartsModelsContext::setDartsTournamentWinner(const QByteArray& json)
{
    auto winnerModel = winnerInfoBuilder()->create(json);
    auto tournament = dynamic_cast<ITournament*>(getTournament()->tournament(winnerModel.tournamentId,tournamentsDbContext()));
    tournament->setWinnerId(winnerModel.winnerId);
    tournament->setWinnerName(winnerModel.winnerName);
    tournamentsDbContext()->saveChanges(tournamentJsonBuilder());
    emit setDartsTournamentWinnerSucces(json);
}
void DartsModelsContext::createDartsKeyValues(const QUuid &tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,tournamentsDbContext());
    auto json = tournamentJsonBuilder()->tournamentJson(model);
    emit sendDartsDetails(json);
}

void DartsModelsContext::getIndexes(const QUuid &tournamentId)
{
    auto indexesModel = getIndexesModel()->indexesModel(tournamentId,indexesDbContext());
    emit sendIndexes(indexesJsonBuilder()->indexesModelJson(indexesModel));
}
void DartsModelsContext::createDartsMetaData(const QUuid &tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,tournamentsDbContext());
    auto json = tournamentJsonBuilder()->tournamentJson(model);
    emit sendTournamentMeta(json);
}
void DartsModelsContext::hideInput(const QByteArray &json)
{
    auto meta = metaModelBuilder()->buildMetaModel(json);
    auto indexes = indexesBuilder()->buildIndexes(json);
    updateIndexes()->update(indexes,indexesDbContext())->saveChanges(indexesJsonBuilder());
    auto input = getInputFromDb()->get(meta.tournamentId,meta.playerId,indexes->roundIndex(),indexes->attemptIndex(),inputsDb());
    input->setHint(HiddenHint);
    inputsDb()->saveChanges(inputJsonBuilder());
    emit hideInputSuccess(inputJsonBuilder()->dartsInputJson(input));
}
void DartsModelsContext::revealInput(const QByteArray &json)
{
    auto meta = metaModelBuilder()->buildMetaModel(json);
    auto indexes = indexesBuilder()->buildIndexes(json);
    updateIndexes()->update(indexes,indexesDbContext())->saveChanges(indexesJsonBuilder());
    auto input = getInputFromDb()->get(meta.tournamentId,meta.playerId,indexes->roundIndex(),indexes->attemptIndex(), inputsDb());
    input->setHint(DisplayHint);
    inputsDb()->saveChanges(inputJsonBuilder());
    emit revealInputSuccess(inputJsonBuilder()->dartsInputJson(input));
}
void DartsModelsContext::getPlayerDetails(const QUuid& tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,tournamentsDbContext());
    emit sendAssignedPlayerDetails(tournamentJsonBuilder()->assignedPlayersJson(model));
}
void DartsModelsContext::getTournamentWinnerDetails(const QUuid& tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,tournamentsDbContext());
    auto json = tournamentJsonBuilder()->winnerDetailsJson(model);
    emit sendWinnerDetails(json);
}
void DartsModelsContext::getPlayerInputs(const QUuid& tournamentId)
{
    auto models = getInputsFromDb()->inputModels(tournamentId,DisplayHint,inputsDb());
    auto json = inputJsonBuilder()->dartsInputsJson(models);
    emit sendInputs(json);
}
