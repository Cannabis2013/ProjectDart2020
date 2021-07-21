#include "localmodelsservice.h"

using namespace ModelsContext;

void LocalModelsService::addDartsTournament(const QByteArray& json)
{
    auto model = createDartsTournament()->create(json);
    auto playerModels = createPlayerModels()->createPlayerModels(json,getPlayerModelsFromDb(),dartsPlayersDb());
    addToTournamentModel()->add(model,playerModels,dartsTournamentDb());
    dartsTournamentDb()->add(model);
    emit tournamentAssembledAndStored();
}

void LocalModelsService::deleteTournaments(const QVector<int>& indexes)
{
    auto status = removeModelsFromDb()->remove(indexes,dartsTournamentDb());
    emit tournamentsDeletedStatus(status);
}

void LocalModelsService::getOrderedDartsPoints(const QUuid &tournamentId)
{
    auto models = getInputsFromDb()->inputModels(tournamentId,DisplayHint,dartsPointsDb());
    auto orderedDartsPointModels = sortInputs()->sort(models,sortPointInputsByIndexes());
    auto json = dartsPointsJsonService()->createJson(orderedDartsPointModels);
    emit sendOrderedDartsPoints(json);
}

void LocalModelsService::handleRequestTournaments()
{
    auto json = dartsTournamentCreateJson()->createJson(dartsTournamentDb()->models());
    emit sendTournaments(json);
}

void LocalModelsService::handleRequestGameMode(const int &index)
{
    auto model = dartsTournamentDb()->model(index);
    // TODO: Create service that extracts the gamemode value from model
    emit requestAssembleTournament(model->id(),dynamic_cast<const ITournament*>(model)->gameMode());
}
void LocalModelsService::addDartsPoint(const QByteArray &json)
{
    auto model = createAndAddInput(json,createPointModel(),dartsPointsDb());
    removeHiddenInputs(model->tournamentId(),dartsPointsDb());
    auto jsonModel = createJsonFromDartsPoint()->createJson(model);
    emit pointAddedToDataContext(jsonModel);
}

void LocalModelsService::resetDartsPointTournament(const QUuid &tournamentId)
{
    auto dartsTournamentModel = getTournament()->tournament(tournamentId,dartsTournamentDb());
    removeInputs(tournamentId,dartsPointsDb());
    addToTournamentModel()->add(dartsTournamentModel,QUuid(),dartsTournamentDb());
    emit tournamentResetSuccess();
}

void LocalModelsService::resetDartsScoreTournament(const QUuid &tournamentId)
{
    auto tournamentModel = getTournament()->tournament(tournamentId,dartsTournamentDb());
    removeInputs(tournamentId,dartsScoresDb());
    addToTournamentModel()->add(tournamentModel,QUuid(),dartsTournamentDb());
    emit tournamentResetSuccess();
}

void LocalModelsService::setDartsTournamentWinner(const QByteArray& json)
{
    auto tournamentId = getDartsTournamentDataFromJson()->tournamentIdFromJson(json);
    auto winnerId = getDartsTournamentDataFromJson()->winnerIdFromJson(json);
    setTournamentWinnerId()->setTournamentWinner(tournamentId,winnerId,getTournament(),addToTournamentModel(),dartsTournamentDb());
    auto responseJson = createTournamentWinnerJson()->createJson(winnerId,getPlayerModelsFromDb(),dartsPlayerCreateJson(),dartsPlayersDb());
    emit setDartsTournamentWinnerSucces(responseJson);
}

void LocalModelsService::createDartsKeyValues(const QUuid &tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,dartsTournamentDb());
    auto json = dartsTournamentCreateJson() ->createJson(model);
    auto hint = getDataFromDartsTournament()->inputHint(model);
    emit sendDartsDetails(json,hint);
}

void LocalModelsService::createPlayer(const QByteArray &json)
{
    auto playerModel = createPlayerModel()->createPlayerModel(json);
    dartsPlayersDb()->add(playerModel);
    emit createPlayerResponse(true);
}

void LocalModelsService::deletePlayersFromIndexes(const QVector<int> &indexes)
{
    auto status = removeModelsFromDb()->remove(indexes,dartsPlayersDb());
    emit playersDeletedStatus(status);
}

void LocalModelsService::handleRequestPlayersDetails()
{
    auto playerModels = dartsPlayersDb()->models();
    auto json = dartsPlayerCreateJson()->createJson(playerModels);
    emit sendPlayers(json);
}

void LocalModelsService::createDartsPointIndexes(const QUuid &tournamentId)
{
    auto tournamentModel = getTournament()->tournament(tournamentId,dartsTournamentDb());
    auto indexes = createIndexesFromPointModels()->createIndexes(tournamentModel,getInputsFromDb(),sortInputs(),
                                                                countInputs(),dartsPointsDb());
    auto json = createJsonFromPointIndexes()->createJson(indexes);
    emit sendDartsPointIndexesAsJson(json);
}

void LocalModelsService::createDartsMetaData(const QUuid &tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,dartsTournamentDb());
    auto json = createJsonMetaData()->createJsonDartsMetaData(model,getPlayerModelsFromDb(),
                                                              dartsTournamentJsonAddDetails(),dartsTournamentCreateJson(),
                                                              dartsPlayersDb());
    emit sendTournamentMeta(json);
}

void LocalModelsService::hideDartsPoint(const QUuid& tournamentId,const QUuid& playerId,
                                        const int &roundIndex,const int& attemptIndex)
{

    auto model = getPointFromDb()->get(tournamentId,playerId,roundIndex,attemptIndex,dartsPointsDb());
    dartsPointSetHint()->setDartsPointHint(model,HiddenHint,dartsPointsDb());
    auto jsonModel = createJsonFromDartsPoint()->createJson(model);
    emit hideDartsPointSuccess(jsonModel);
}

void LocalModelsService::revealPoint(const QUuid &tournamentId,const QUuid &playerId,
                                     const int &roundIndex,const int &attemptIndex)
{
    auto dartsPointModel = getPointFromDb()->get(tournamentId,playerId,roundIndex,attemptIndex,dartsPointsDb());
    dartsPointSetHint()->setDartsPointHint(dartsPointModel,DisplayHint,dartsPointsDb());
    auto jsonModel = createJsonFromDartsPoint()->createJson(dartsPointModel);
    emit revealDartsPointSuccess(jsonModel);
}

void LocalModelsService::hideDartsScore(const QUuid& tournamentId,const QUuid& playerId,const int& roundIndex)
{
    auto model = getScoreFromDb()->get(tournamentId,playerId,roundIndex,dartsScoresDb());
    dartsScoreSetHint()->setDartsScoreHint(model,ModelDisplayHint::HiddenHint,dartsScoresDb());
    auto jsonModel = createJsonFromDartsScore()->createJson(model);
    emit hideDartsScoreSuccess(jsonModel);
}

void LocalModelsService::revealScore(const QUuid& tournamentId,const QUuid& playerId,const int& roundIndex)
{
    auto dartsScoreModel = getScoreFromDb()->get(tournamentId,playerId,roundIndex,dartsScoresDb());
    dartsScoreSetHint()->setDartsScoreHint(dartsScoreModel,DisplayHint,dartsScoresDb());
    auto jsonModel = createJsonFromDartsScore()->createJson(dartsScoreModel);
    emit revealDartsScoreSuccess(jsonModel);
}

void LocalModelsService::addDartsScore(const QByteArray &json)
{
    auto scoreModel = createAndAddInput(json,createScoreModel(),dartsScoresDb());
    removeHiddenInputs(scoreModel->tournamentId(),dartsScoresDb());
    auto jsonModel = createJsonFromDartsScore()->createJson(scoreModel);
    emit scoreAddedToDataContext(jsonModel);
}

void LocalModelsService::createAssignedPlayerEntities(const QUuid& tournamentId)
{
    // Get playernames
    auto model = getTournament()->tournament(tournamentId,dartsTournamentDb());
    auto json = dartsPlayerCreateJson()->createJson(dynamic_cast<const ITournament*>(model)->assignedPlayerIds(),
                                                    dynamic_cast<const ITournament*>(model)->assignedPlayerNames());
    emit sendAssignedPlayerIdsAndNamesAsJson(json);
}

void LocalModelsService::createDartsTournamentWinnerIdAndName(const QUuid& tournamentId)
{
    auto playerModel = getTournamenWinnerModel()->getWinnerModel(tournamentId,getTournament(),getPlayerModelsFromDb(),dartsTournamentDb(),dartsPlayersDb());
    auto json = dartsPlayerCreateJson()->createJson(playerModel);
    emit sendDartsTournamentWinnerIdAndName(json);
}

void LocalModelsService::removeInputs(const QUuid &tournamentId, IDbService *dbService)
{
    removeInputsFromDb()->remove(dbService->models(),tournamentId,dbService);
}

const IPlayerInput* LocalModelsService::createAndAddInput(const QByteArray &json,
                                                          const IDartsCreateInput *createModel,
                                                          IDbService *dbService)
{
    auto model = createModel->create(json);
    dbService->add(model);
    return model;
}

void LocalModelsService::removeHiddenInputs(const QUuid &tournamentId, IDbService *dbService)
{
    auto models = getInputsFromDb()->inputModels(tournamentId,dbService);
    removeInputsFromDb()->remove(models,HiddenHint,dbService);
}

void LocalModelsService::createAssignedPlayerPoints(const QUuid& tournamentId)
{
    auto models = getInputsFromDb()->inputModels(tournamentId,DisplayHint,dartsPointsDb());
    auto json = dartsPointsJsonService()->createJson(models);
    emit sendTournamentDartsPointsAsJson(json);
}

void LocalModelsService::createAssignedPlayerScores(const QUuid &tournamentId)
{
    auto models = getInputsFromDb()->inputModels(tournamentId,DisplayHint,dartsScoresDb());
    auto json = createJsonFromScoreModels()->createJson(models);
    emit sendTournamentDartsScoresAsJson(json);
}

void LocalModelsService::createDartsScoreIndexes(const QUuid &tournamentId)
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
