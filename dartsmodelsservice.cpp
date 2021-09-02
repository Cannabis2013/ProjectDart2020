#include "dartsmodelsservice.h"
using namespace ModelsContext;
void DartsModelsService::addDartsTournament(const QByteArray& json,const QVector<const IModel<QUuid>*> &playerModels)
{
    auto model = createDartsTournament()->create(json);
    addToTournamentModel()->add(model,playerModels,dartsTournamentDb());
    dartsTournamentDb()->add(model);
    emit tournamentCreatedAndPersisted();
}

void DartsModelsService::deleteTournaments(const QVector<int>& indexes)
{
    auto status = removeModelsFromDb()->remove(indexes,dartsTournamentDb());
    emit tournamentsDeletedStatus(status);
}

void DartsModelsService::getOrderedInputs(const QUuid &tournamentId)
{
    auto models = getInputsFromDb()->inputModels(tournamentId,DisplayHint,inputsDb());
    auto orderedDartsPointModels = sortInputs()->sort(models,sortPointInputsByIndexes());
    auto json = dartsPointsJsonService()->createJson(orderedDartsPointModels);
    emit sendOrderedInputs(json);
}

void DartsModelsService::getTournaments()
{
    auto json = dartsTournamentCreateJson()->createJson(dartsTournamentDb()->models());
    emit sendTournaments(json);
}

void DartsModelsService::getGameMode(const int &index)
{
    auto model = dartsTournamentDb()->model(index);
    emit requestAssembleTournament(model->id(),dynamic_cast<const ITournament*>(model)->gameMode());
}
void DartsModelsService::addInput(const QByteArray &json)
{
    auto model = createPointModel()->create(json);
    inputsDb()->add(model);
    auto models = getInputsFromDb()->inputModels(model->tournamentId(),inputsDb());
    removeInputsFromDb()->remove(models,HiddenHint,inputsDb());
    emit pointAddedToDataContext(json);
}

void DartsModelsService::resetDartsPointTournament(const QUuid &tournamentId)
{
    auto dartsTournamentModel = getTournament()->tournament(tournamentId,dartsTournamentDb());
    removeInputsFromDb()->remove(inputsDb()->models(),tournamentId,inputsDb());
    addToTournamentModel()->add(dartsTournamentModel,QUuid(),QString(),dartsTournamentDb());
    emit tournamentResetSuccess();
}

void DartsModelsService::setDartsTournamentWinner(const QByteArray& json)
{
    auto winnerDataModel = extractWinnerInfoFromJson()->createWinnerDataModel(json);
    auto tournamentModel = getTournament()->tournament(winnerDataModel.tournamentId,dartsTournamentDb());
    addToTournamentModel()->add(tournamentModel,winnerDataModel.winnerId,winnerDataModel.winnerName,dartsTournamentDb());
    emit setDartsTournamentWinnerSucces(json);
}

void DartsModelsService::createDartsKeyValues(const QUuid &tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,dartsTournamentDb());
    auto json = dartsTournamentCreateJson() ->createJson(model);
    auto hint = getDataFromDartsTournament()->inputHint(model);
    emit sendDartsDetails(json,hint);
}

void DartsModelsService::createIndexes(const QUuid &tournamentId)
{
    auto tournamentModel = getTournament()->tournament(tournamentId,dartsTournamentDb());
    auto indexes = createControllerIndexes()->createIndexes(tournamentModel,getInputsFromDb(),sortInputs(),
                                                            countInputs(),inputsDb());
    auto json = createJsonFromPointIndexes()->createJson(indexes);
    emit sendIndexesAsJson(json);
}

void DartsModelsService::createDartsMetaData(const QUuid &tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,dartsTournamentDb());
    auto json = createJsonMetaData()->createJsonDartsMetaData(model,dartsTournamentCreateJson());
    emit sendTournamentMeta(json);
}

void DartsModelsService::hideInput(const QUuid& tournamentId,const QUuid& playerId,
                                        const int &roundIndex,const int& attemptIndex)
{

    auto model = getPointFromDb()->get(tournamentId,playerId,roundIndex,attemptIndex,inputsDb());
    dartsPointSetHint()->setDartsPointHint(model,HiddenHint,inputsDb());
    auto jsonModel = createJsonFromDartsPoint()->createJson(model);
    emit hideInputSuccess(jsonModel);
}

void DartsModelsService::revealInput(const QUuid &tournamentId,const QUuid &playerId,const int &roundIndex,const int &attemptIndex)
{
    auto dartsPointModel = getPointFromDb()->get(tournamentId,playerId,roundIndex,attemptIndex,inputsDb());
    dartsPointSetHint()->setDartsPointHint(dartsPointModel,DisplayHint,inputsDb());
    auto jsonModel = createJsonFromDartsPoint()->createJson(dartsPointModel);
    emit revealInputSuccess(jsonModel);
}

void DartsModelsService::getPlayerDetails(const QUuid& tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,dartsTournamentDb());
    auto json = createJsonFromDetails()->createFromAssignedPlayerDetails(model);
    emit sendAssignedPlayerDetails(json);
}

void DartsModelsService::getTournamentWinnerDetails(const QUuid& tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,dartsTournamentDb());
    auto json = createJsonFromDetails()->createFromWinnerDetails(model);
    emit sendWinnerDetails(json);
}

void DartsModelsService::getPlayerInputs(const QUuid& tournamentId)
{
    auto models = getInputsFromDb()->inputModels(tournamentId,DisplayHint,inputsDb());
    auto json = dartsPointsJsonService()->createJson(models);
    emit sendInputs(json);
}
