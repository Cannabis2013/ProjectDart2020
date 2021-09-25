#include "dartsmodelscontext.h"
void DartsModelsContext::addDartsTournament(const QByteArray& json,const QVector<const IModel<QUuid>*> &playerModels)
{
    auto model = createDartsTournament()->create(json,tournamentExtractor());
    addToTournamentModel()->add(model,playerModels,dartsTournamentDb());
    dartsTournamentDb()->add(model);
    emit tournamentCreatedAndPersisted();
}
void DartsModelsContext::deleteTournaments(const QVector<int>& indexes)
{
    auto status = removeModelsFromDb()->remove(indexes,dartsTournamentDb());
    emit tournamentsDeletedStatus(status);
}
void DartsModelsContext::getOrderedInputs(const QUuid &tournamentId)
{
    auto models = getInputsFromDb()->inputModels(tournamentId,DisplayHint,inputsDb());
    auto orderedDartsPointModels = sortInputs()->sort(models,sortInputsByIndexes());
    auto json = inputsToJSon()->toJson(orderedDartsPointModels);
    emit sendOrderedInputs(json);
}
void DartsModelsContext::getTournaments()
{
    auto json = dartsTournamentCreateJson()->createJson(dartsTournamentDb()->models());
    emit sendTournaments(json);
}
void DartsModelsContext::getGameMode(const int &index)
{
    auto model = dartsTournamentDb()->model(index);
    emit requestAssembleTournament(model->id(),dynamic_cast<const ITournament*>(model)->gameMode());
}
void DartsModelsContext::addInput(const QByteArray &json)
{
    auto model = createInputModel()->create(json);
    inputsDb()->add(model);
    auto models = getInputsFromDb()->inputModels(model->tournamentId(),inputsDb());
    removeInputsFromDb()->remove(models,HiddenHint,inputsDb());
    emit inputModelAdded(json);
}
void DartsModelsContext::resetTournament(const QUuid &tournamentId)
{
    auto dartsTournamentModel = getTournament()->tournament(tournamentId,dartsTournamentDb());
    removeInputsFromDb()->remove(inputsDb()->models(),tournamentId,inputsDb());
    addToTournamentModel()->add(dartsTournamentModel,QUuid(),QString(),dartsTournamentDb());
    emit tournamentResetSuccess();
}
void DartsModelsContext::setDartsTournamentWinner(const QByteArray& json)
{
    auto winnerDataModel = extractWinnerInfoFromJson()->createWinnerDataModel(json);
    auto tournamentModel = getTournament()->tournament(winnerDataModel.tournamentId,dartsTournamentDb());
    addToTournamentModel()->add(tournamentModel,winnerDataModel.winnerId,winnerDataModel.winnerName,dartsTournamentDb());
    emit setDartsTournamentWinnerSucces(json);
}
void DartsModelsContext::createDartsKeyValues(const QUuid &tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,dartsTournamentDb());
    auto json = dartsTournamentCreateJson() ->createJson(model);
    emit sendDartsDetails(json);
}
void DartsModelsContext::createIndexes(const QUuid &tournamentId)
{
    auto tournamentModel = getTournament()->tournament(tournamentId,dartsTournamentDb());
    auto indexes = indexesBuilder()->createIndexes(tournamentModel,getInputsFromDb(),sortInputs(), countInputs(),inputsDb());
    auto json = indexesToJson()->toJson(indexes);
    emit sendIndexesAsJson(json);
}
void DartsModelsContext::createDartsMetaData(const QUuid &tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,dartsTournamentDb());
    auto json = createJsonMetaData()->createJsonDartsMetaData(model,dartsTournamentCreateJson());
    emit sendTournamentMeta(json);
}
void DartsModelsContext::hideInput(const QUuid& tournamentId,const QUuid& playerId, const int &roundIndex,const int& attemptIndex)
{
    auto model = getInputFromDb()->get(tournamentId,playerId,roundIndex,attemptIndex,inputsDb());
    dartsPointInputHint()->setHint(model,HiddenHint,inputsDb());
    auto jsonModel = inputToJson()->createJson(model);
    emit hideInputSuccess(jsonModel);
}
void DartsModelsContext::revealInput(const QUuid &tournamentId,const QUuid &playerId,const int &roundIndex,const int &attemptIndex)
{
    auto dartsPointModel = getInputFromDb()->get(tournamentId,playerId,roundIndex,attemptIndex,inputsDb());
    dartsPointInputHint()->setHint(dartsPointModel,DisplayHint,inputsDb());
    auto jsonModel = inputToJson()->createJson(dartsPointModel);
    emit revealInputSuccess(jsonModel);
}
void DartsModelsContext::getPlayerDetails(const QUuid& tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,dartsTournamentDb());
    auto json = createJsonFromDetails()->createFromAssignedPlayerDetails(model);
    emit sendAssignedPlayerDetails(json);
}
void DartsModelsContext::getTournamentWinnerDetails(const QUuid& tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,dartsTournamentDb());
    auto json = createJsonFromDetails()->createFromWinnerDetails(model);
    emit sendWinnerDetails(json);
}
void DartsModelsContext::getPlayerInputs(const QUuid& tournamentId)
{
    auto models = getInputsFromDb()->inputModels(tournamentId,DisplayHint,inputsDb());
    auto json = inputsToJSon()->toJson(models);
    emit sendInputs(json);
}
