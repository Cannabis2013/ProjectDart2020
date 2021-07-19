#include "dartsmodelsservice.h"

using namespace DartsModelsContext;

void DartsModelsService::addDartsTournament(const QByteArray& json)
{
    auto model = createDartsTournament()->create(json);
    auto playerModels = createPlayerModels()->createPlayerModels(json,dbGetIndexesFromjson(),getPlayerModelsFromDb(),dartsPlayersDb());
    addToTournamentModel()->add(model,playerModels,dartsTournamentDb());
    dartsTournamentDb()->add(model);
    emit tournamentAssembledAndStored();
}

void DartsModelsService::deleteTournaments(const QByteArray& json)
{
    auto indexes = dbGetIndexesFromjson()->dbIndexesFromJson(json);
    auto status = tournamentDbManipulator()->removeTournamentsByIndexes(indexes,dartsTournamentDb());
    emit tournamentsDeletedStatus(status);
}

void DartsModelsService::getOrderedDartsPoints(const QUuid &tournamentId)
{
    auto models = getInputsFromDb()->inputModels(tournamentId,DisplayHint,dartsPointsDb());
    auto orderedDartsPointModels = sortInputs()->sort(models,sortPointInputsByIndexes());
    auto json = dartsPointsJsonService()->createJson(orderedDartsPointModels);
    emit sendOrderedDartsPoints(json);
}

void DartsModelsService::handleRequestTournaments()
{
    auto json = dartsTournamentCreateJson()->createJson(dartsTournamentDb()->models());
    emit sendTournaments(json);
}

void DartsModelsService::handleRequestGameMode(const int &index)
{
    auto model = dartsTournamentDb()->model(index);
    emit requestAssembleTournament(model->id(),model->gameMode());
}
void DartsModelsService::addDartsPoint(const QByteArray &json)
{
    auto model = createAndAddInput(json,createPointModel(),dartsPointsDb());
    removeHiddenInputs(model->tournamentId(),dartsPointsDb());
    auto jsonModel = createJsonFromDartsPoint()->createJson(model);
    emit pointAddedToDataContext(jsonModel);
}

void DartsModelsService::resetDartsPointTournament(const QUuid &tournamentId)
{
    auto dartsTournamentModel = getTournament()->tournament(tournamentId,dartsTournamentDb());
    removeInputs(tournamentId,dartsPointsDb());
    addToTournamentModel()->add(dartsTournamentModel,QUuid(),dartsTournamentDb());
    emit tournamentResetSuccess();
}

void DartsModelsService::resetDartsScoreTournament(const QUuid &tournamentId)
{
    auto tournamentModel = getTournament()->tournament(tournamentId,dartsTournamentDb());
    removeInputs(tournamentId,dartsScoresDb());
    addToTournamentModel()->add(tournamentModel,QUuid(),dartsTournamentDb());
    emit tournamentResetSuccess();
}

void DartsModelsService::setDartsTournamentWinner(const QByteArray& json)
{
    auto tournamentId = getDartsTournamentDataFromJson()->tournamentIdFromJson(json);
    auto winnerId = getDartsTournamentDataFromJson()->winnerIdFromJson(json);
    setTournamentWinnerId()->setTournamentWinner(tournamentId,winnerId,getTournament(),addToTournamentModel(),dartsTournamentDb());
    auto responseJson = createTournamentWinnerJson()->createJson(winnerId,getPlayerModelsFromDb(),dartsPlayerCreateJson(),dartsPlayersDb());
    emit setDartsTournamentWinnerSucces(responseJson);
}

void DartsModelsService::createDartsKeyValues(const QUuid &tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,dartsTournamentDb());
    auto json = dartsTournamentCreateJson() ->createJson(model);
    auto hint = getDataFromDartsTournament()->inputHint(model);
    emit sendDartsDetails(json,hint);
}

void DartsModelsService::createPlayer(const QByteArray &json)
{
    auto playerModel = createPlayerModel()->createPlayerModel(json);
    dartsPlayersDb()->add(playerModel);
    emit createPlayerResponse(true);
}

void DartsModelsService::deletePlayerFromIndex(const QByteArray &json)
{
    auto index = dbGetIndexesFromjson()->dbIndexFromJson(json);
    auto status = playerDbManipulator()->remove(index,dartsPlayersDb());
    emit playersDeletedStatus(status);
}

void DartsModelsService::deletePlayersFromIndexes(const QByteArray &json)
{
    QVector<int> indexes = dbGetIndexesFromjson()->dbIndexesFromJson(json);
    auto status = playerDbManipulator()->remove(indexes,dartsPlayersDb());
    emit playersDeletedStatus(status);
}

void DartsModelsService::handleRequestPlayersDetails()
{
    auto playerModels = dartsPlayersDb()->models();
    auto json = dartsPlayerCreateJson()->createJson(playerModels);
    emit sendPlayers(json);
}

void DartsModelsService::createDartsPointIndexes(const QUuid &tournamentId)
{
    auto tournamentModel = getTournament()->tournament(tournamentId,dartsTournamentDb());
    auto indexes = createIndexesFromPointModels()->createIndexes(tournamentModel,getInputsFromDb(),sortInputs(),
                                                                countInputs(),dartsPointsDb());
    auto json = createJsonFromPointIndexes()->createJson(indexes);
    emit sendDartsPointIndexesAsJson(json);
}

void DartsModelsService::createDartsMetaData(const QUuid &tournamentId)
{
    auto dartsTournamentModel = getTournament()->tournament(tournamentId,dartsTournamentDb());
    auto json = createJsonMetaData()->createJsonDartsMetaData(dartsTournamentModel,getPlayerModelsFromDb(),
                                                              dartsTournamentJsonAddDetails(),dartsTournamentCreateJson(),
                                                              dartsPlayersDb());
    emit sendTournamentMeta(json);
}

void DartsModelsService::hideDartsPoint(const QUuid& tournamentId,const QUuid& playerId,
                                        const int &roundIndex,const int& attemptIndex)
{

    auto model = getPointFromDb()->get(tournamentId,playerId,roundIndex,attemptIndex,dartsPointsDb());
    dartsPointSetHint()->setDartsPointHint(model,HiddenHint,dartsPointsDb());
    auto jsonModel = createJsonFromDartsPoint()->createJson(model);
    emit hideDartsPointSuccess(jsonModel);
}

void DartsModelsService::revealPoint(const QUuid &tournamentId,const QUuid &playerId,
                                     const int &roundIndex,const int &attemptIndex)
{
    auto dartsPointModel = getPointFromDb()->get(tournamentId,playerId,roundIndex,attemptIndex,dartsPointsDb());
    dartsPointSetHint()->setDartsPointHint(dartsPointModel,DisplayHint,dartsPointsDb());
    auto jsonModel = createJsonFromDartsPoint()->createJson(dartsPointModel);
    emit revealDartsPointSuccess(jsonModel);
}

void DartsModelsService::hideDartsScore(const QUuid& tournamentId,const QUuid& playerId,const int& roundIndex)
{
    auto dartsScoreModel = getScoreFromDb()->get(tournamentId,playerId,roundIndex,dartsScoresDb());
    dartsScoreSetHint()->setDartsScoreHint(dartsScoreModel,ModelDisplayHint::HiddenHint,dartsScoresDb());
    auto jsonModel = createJsonFromDartsScore()->createJson(dartsScoreModel);
    emit hideDartsScoreSuccess(jsonModel);
}

void DartsModelsService::revealScore(const QUuid& tournamentId,const QUuid& playerId,const int& roundIndex)
{
    auto dartsScoreModel = getScoreFromDb()->get(tournamentId,playerId,roundIndex,dartsScoresDb());
    dartsScoreSetHint()->setDartsScoreHint(dartsScoreModel,DisplayHint,dartsScoresDb());
    auto jsonModel = createJsonFromDartsScore()->createJson(dartsScoreModel);
    emit revealDartsScoreSuccess(jsonModel);
}

void DartsModelsService::addDartsScore(const QByteArray &json)
{
    auto scoreModel = createAndAddInput(json,createScoreModel(),dartsScoresDb());
    removeHiddenInputs(scoreModel->tournamentId(),dartsScoresDb());
    auto jsonModel = createJsonFromDartsScore()->createJson(scoreModel);
    emit scoreAddedToDataContext(jsonModel);
}

void DartsModelsService::createAssignedPlayerEntities(const QUuid& tournamentId)
{
    // Get playernames
    auto model = getTournament()->tournament(tournamentId,dartsTournamentDb());
    auto json = dartsPlayerCreateJson()->createJson(model->assignedPlayerIds(),model->assignedPlayerNames());
    emit sendAssignedPlayerIdsAndNamesAsJson(json);
}

void DartsModelsService::createDartsTournamentWinnerIdAndName(const QUuid& tournamentId)
{
    auto playerModel = getTournamenWinnerModel()->getWinnerModel(tournamentId,getTournament(),getPlayerModelsFromDb(),dartsTournamentDb(),dartsPlayersDb());
    auto json = dartsPlayerCreateJson()->createJson(playerModel);
    emit sendDartsTournamentWinnerIdAndName(json);
}

void DartsModelsService::removeInputs(const QUuid &tournamentId, IDartsInputDb *dbService)
{
    removeInputsFromDb()->remove(dbService->models(),tournamentId,dbService);
}

const IPlayerInput* DartsModelsService::createAndAddInput(const QByteArray &json, const IDartsCreateInput *createModel, IDartsInputDb *dbService)
{
    auto model = createModel->create(json);
    dbService->add(model);
    return model;
}

void DartsModelsService::removeHiddenInputs(const QUuid &tournamentId, IDartsInputDb *dbService)
{
    auto models = getInputsFromDb()->inputModels(tournamentId,dbService);
    removeInputsFromDb()->remove(models,HiddenHint,dbService);
}

void DartsModelsService::createAssignedPlayerPoints(const QUuid& tournamentId)
{
    auto models = getInputsFromDb()->inputModels(tournamentId,DisplayHint,dartsPointsDb());
    auto json = dartsPointsJsonService()->createJson(models);
    emit sendTournamentDartsPointsAsJson(json);
}

void DartsModelsService::createAssignedPlayerScores(const QUuid &tournamentId)
{
    auto models = getInputsFromDb()->inputModels(tournamentId,DisplayHint,dartsScoresDb());
    auto json = createJsonFromScoreModels()->createJson(models);
    emit sendTournamentDartsScoresAsJson(json);
}

void DartsModelsService::createDartsScoreIndexes(const QUuid &tournamentId)
{
    auto tournamentModel = getTournament()->tournament(tournamentId,dartsTournamentDb());
    auto indexes = createIndexesFromScoreModels()->createIndexes(tournamentModel,
                                                                 getInputsFromDb(),
                                                                 sortInputs(),
                                                                 countInputs(),
                                                                 dartsScoresDb());
    auto json = createJsonfromScoreIndexes()->createJson(indexes);
    emit sendDartsScoreIndexesAsJson(json);
}
