#include "dartsmodelsservice.h"

using namespace DartsModelsContext;

void DartsModelsService::addDartsTournament(const QByteArray& json)
{
    auto model = createDartsTournament()->create(json);
    auto playerModels = createPlayerModelsFromJson(json);
    addPlayerIdsAndNAmesToTournament(model,playerModels);
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
    auto models = getInputsFromDb()->inputModels(tournamentId,dartsPointsDb());
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
    setTournamentWinnerId(tournamentId,winnerId,getTournament(),addToTournamentModel());
    auto responseJson = createTournamentWinnerJson(winnerId);
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
    auto playerModel = playerModelBuilder()->createPlayerModel(json);
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
    auto json = dartsPlayerJsonBuilder()->createJson(playerModels);
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
    auto json = dartsPlayerJsonBuilder()->createJson(model->assignedPlayerIds(),model->assignedPlayerNames());
    emit sendAssignedPlayerIdsAndNamesAsJson(json);
}

void DartsModelsService::createDartsTournamentWinnerIdAndName(const QUuid& tournamentId)
{
    auto player = getTournamentWinnerModel(tournamentId);
    auto json = dartsPlayerJsonBuilder()->createJson(player->id(),player->playerName());
    emit sendDartsTournamentWinnerIdAndName(json);
}

const IPlayerModel *DartsModelsService::getTournamentWinnerModel(const QUuid &tournamentId)
{
    auto dartsTournamentModel = getTournament()->tournament(tournamentId,dartsTournamentDb());
    auto player = getPlayerModelsFromDb()->playerModel(dartsTournamentModel->winnerId(),dartsPlayersDb());
    return player;
}

void DartsModelsService::removeInputs(const QUuid &tournamentId, IDartsInputDb *dbService)
{
    auto tournamentInputModels = dbService->models();
    removeInputsFromDb()->remove(tournamentInputModels,tournamentId,dbService);
}

QVector<const IPlayerModel *> DartsModelsService::createPlayerModelsFromJson(const QByteArray &json)
{
    auto playerIndexes = dbGetIndexesFromjson()->dbIndexesFromJson(json);
    auto playerModels = getPlayerModelsFromDb()->playerModels(playerIndexes,dartsPlayersDb());
    return playerModels;
}

void DartsModelsService::addPlayerIdsAndNAmesToTournament(const ITournament *model,
                                                          const QVector<const IPlayerModel*> &playerModels)
{
    auto playerIds = getDataFromPlayerModels()->createPlayerIds(playerModels);
    auto playerNames = getDataFromPlayerModels()->createPlayerNames(playerModels);
    addToTournamentModel()->add(model,playerIds);
    addToTournamentModel()->add(model,playerNames);
}

QByteArray DartsModelsService::createTournamentWinnerJson(const QUuid &winnerId)
{
    auto playerModel = getPlayerModelsFromDb()->playerModel(winnerId,dartsPlayersDb());
    auto responseJson = dartsPlayerJsonBuilder()->createJson(winnerId,playerModel->playerName());
    return responseJson;
}

void DartsModelsService::setTournamentWinnerId(const QUuid &tournamentId, const QUuid &winnerId,
                                               const IGetDartsTournamentFromDb *getTournament,
                                               IAddPlayerDetailsToTournament *dbManipulator) const
{
    auto dartsTournamentModel = getTournament->tournament(tournamentId,dartsTournamentDb());
    dbManipulator->add(dartsTournamentModel,winnerId,dartsTournamentDb());
}

const IPlayerInput* DartsModelsService::createAndAddInput(const QByteArray &json, const IDartsCreateInput *createService, IDartsInputDb *dbService)
{
    auto model = createService->create(json);
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
    auto models = getInputsFromDb()->inputModels(tournamentId,dartsPointsDb());
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
