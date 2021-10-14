#include "dartsmodelscontext.h"

void DartsModelsContext::addDartsTournament(const QByteArray& json,const QVector<IModel<QUuid>*> &playerModels)
{
    auto model = tournamentBuilder()->createTournament(json);
    indexesDbContext()->add(indexesBuilder()->indexesModel(model->id()));
    indexesDbContext()->saveChanges(indexesJsonBuilder());
    setTournamentPlayerDetails()->setDetails(model,playerModels);
    tournamentDb()->add(model);
    tournamentDb()->saveChanges(tournamentJsonBuilder());
    emit tournamentCreatedAndPersisted();
}
void DartsModelsContext::deleteTournaments(const QVector<int>& indexes)
{
    auto tournamentIds = getTournamentIds()->fromIndexes(indexes,tournamentDb());
    removeInputsFromDb()->removeByTournamentIds(tournamentIds,inputsDb())->saveChanges(inputJsonBuilder());
    tournamentDb()->remove(indexes)->saveChanges(tournamentJsonBuilder());
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
    auto json = tournamentJsonBuilder()->tournamentsjson(tournamentDb()->models());
    emit sendTournaments(json);
}
void DartsModelsContext::getGameMode(const int &index)
{
    auto model = tournamentDb()->model(index);
    emit requestAssembleTournament(model->id(),dynamic_cast<const ITournament*>(model)->gameMode());
}
void DartsModelsContext::addInput(const QByteArray &json)
{
    auto input = dynamic_cast<IPlayerInput*>(inputModelBuilder()->createInput(json));
    updateIndexes()->update(indexesBuilder()->indexesModel(json),indexesDbContext())->saveChanges(indexesJsonBuilder());
    inputsDb()->add(input);
    removeInputsFromDb()->removeByHint(input->tournamentId(),HiddenHint,inputsDb())->saveChanges(inputJsonBuilder());
    emit inputModelAdded(json);
}
void DartsModelsContext::updateTournamentIndexes(const QByteArray &json)
{
    emit tournamentIndexesUpdated(json);
}
void DartsModelsContext::resetTournament(const QUuid &tournamentId)
{
    removeInputsFromDb()->removeInputsByTournamentId(tournamentId,inputsDb());
    inputsDb()->saveChanges(inputJsonBuilder());
    auto tournament = dynamic_cast<ITournament*>(getTournament()->tournament(tournamentId,tournamentDb()));
    tournament->setWinnerId(QUuid());
    tournament->setWinnerName(QString());
    tournamentDb()->saveChanges(tournamentJsonBuilder());
    emit tournamentResetSuccess();
}
void DartsModelsContext::setDartsTournamentWinner(const QByteArray& json)
{
    auto winnerModel = winnerInfoBuilder()->create(json);
    auto tournament = dynamic_cast<ITournament*>(getTournament()->tournament(winnerModel.tournamentId,tournamentDb()));
    tournament->setWinnerId(winnerModel.winnerId);
    tournament->setWinnerName(winnerModel.winnerName);
    tournamentDb()->saveChanges(tournamentJsonBuilder());
    emit setDartsTournamentWinnerSucces(json);
}
void DartsModelsContext::createDartsKeyValues(const QUuid &tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,tournamentDb());
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
    auto model = getTournament()->tournament(tournamentId,tournamentDb());
    auto json = tournamentJsonBuilder()->tournamentJson(model);
    emit sendTournamentMeta(json);
}
void DartsModelsContext::hideInput(const QUuid& tournamentId,const QUuid& playerId, const int &roundIndex,const int& attemptIndex)
{
    auto model = getInputFromDb()->get(tournamentId,playerId,roundIndex,attemptIndex,inputsDb());
    dynamic_cast<IPlayerInput*>(model)->setHint(HiddenHint);
    inputsDb()->saveChanges(inputJsonBuilder());
    emit hideInputSuccess(inputJsonBuilder()->dartsInputJson(model));
}
void DartsModelsContext::revealInput(const QUuid &tournamentId,const QUuid &playerId,const int &roundIndex,const int &attemptIndex)
{
    auto input = getInputFromDb()->get(tournamentId,playerId,roundIndex,attemptIndex,inputsDb());
    dynamic_cast<IPlayerInput*>(input)->setHint(DisplayHint);
    inputsDb()->saveChanges(inputJsonBuilder());
    emit revealInputSuccess(inputJsonBuilder()->dartsInputJson(input));
}
void DartsModelsContext::getPlayerDetails(const QUuid& tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,tournamentDb());
    emit sendAssignedPlayerDetails(tournamentJsonBuilder()->assignedPlayersJson(model));
}
void DartsModelsContext::getTournamentWinnerDetails(const QUuid& tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,tournamentDb());
    auto json = tournamentJsonBuilder()->winnerDetailsJson(model);
    emit sendWinnerDetails(json);
}
void DartsModelsContext::getPlayerInputs(const QUuid& tournamentId)
{
    auto models = getInputsFromDb()->inputModels(tournamentId,DisplayHint,inputsDb());
    auto json = inputJsonBuilder()->dartsInputsJson(models);
    emit sendInputs(json);
}
