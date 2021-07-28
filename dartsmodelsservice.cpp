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
    emit requestAssembleTournament(model->id(),dynamic_cast<const ITournament*>(model)->gameMode());
}
void DartsModelsService::addDartsPoint(const QByteArray &json)
{
    auto model = createPointModel()->create(json);
    dartsPointsDb()->add(model);
    auto models = getInputsFromDb()->inputModels(model->tournamentId(),dartsPointsDb());
    removeInputsFromDb()->remove(models,HiddenHint,dartsPointsDb());
    emit pointAddedToDataContext(json);
}

void DartsModelsService::resetDartsPointTournament(const QUuid &tournamentId)
{
    auto dartsTournamentModel = getTournament()->tournament(tournamentId,dartsTournamentDb());
    removeInputsFromDb()->remove(dartsPointsDb()->models(),tournamentId,dartsPointsDb());
    addToTournamentModel()->add(dartsTournamentModel,QUuid(),QString(),dartsTournamentDb());
    emit tournamentResetSuccess();
}

void DartsModelsService::resetDartsScoreTournament(const QUuid &tournamentId)
{
    auto tournamentModel = getTournament()->tournament(tournamentId,dartsTournamentDb());
    removeInputsFromDb()->remove(dartsScoresDb()->models(),tournamentId,dartsScoresDb());
    addToTournamentModel()->add(tournamentModel,QUuid(),QString(),dartsTournamentDb());
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

void DartsModelsService::createDartsPointIndexes(const QUuid &tournamentId)
{
    auto tournamentModel = getTournament()->tournament(tournamentId,dartsTournamentDb());
    auto indexes = createIndexesFromPoints()->createIndexes(tournamentModel,getInputsFromDb(),sortInputs(),countInputs(),dartsPointsDb());
    auto json = createJsonFromPointIndexes()->createJson(indexes);
    emit sendDartsPointIndexesAsJson(json);
}

void DartsModelsService::createDartsMetaData(const QUuid &tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,dartsTournamentDb());
    auto json = createJsonMetaData()->createJsonDartsMetaData(model,dartsTournamentCreateJson());
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

void DartsModelsService::revealPoint(const QUuid &tournamentId,const QUuid &playerId,const int &roundIndex,const int &attemptIndex)
{
    auto dartsPointModel = getPointFromDb()->get(tournamentId,playerId,roundIndex,attemptIndex,dartsPointsDb());
    dartsPointSetHint()->setDartsPointHint(dartsPointModel,DisplayHint,dartsPointsDb());
    auto jsonModel = createJsonFromDartsPoint()->createJson(dartsPointModel);
    emit revealDartsPointSuccess(jsonModel);
}

void DartsModelsService::hideDartsScore(const QUuid& tournamentId,const QUuid& playerId,const int& roundIndex)
{
    auto model = getScoreFromDb()->get(tournamentId,playerId,roundIndex,dartsScoresDb());
    dartsScoreSetHint()->setDartsScoreHint(model,ModelDisplayHint::HiddenHint,dartsScoresDb());
    auto jsonModel = createJsonFromDartsScore()->createJson(model);
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
    auto input = createScoreModel()->create(json);
    dartsScoresDb()->add(input);
    auto inputs = getInputsFromDb()->inputModels(input->tournamentId(),dartsScoresDb());
    removeInputsFromDb()->remove(inputs,HiddenHint,dartsScoresDb());
    emit scoreAddedToDataContext(json);
}

void DartsModelsService::createAssignedPlayerEntities(const QUuid& tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,dartsTournamentDb());
    auto json = createJsonFromDetails()->createFromAssignedPlayerDetails(model);
    emit sendAssignedPlayerIdsAndNamesAsJson(json);
}

void DartsModelsService::createDartsTournamentWinnerIdAndName(const QUuid& tournamentId)
{
    auto model = getTournament()->tournament(tournamentId,dartsTournamentDb());
    auto json = createJsonFromDetails()->createFromWinnerDetails(model);
    emit sendDartsTournamentWinnerIdAndName(json);
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
    auto indexes = createIndexesFromScoreModels()->createIndexes(tournamentModel,getInputsFromDb(),sortInputs(),countInputs(),dartsScoresDb());
    auto json = createJsonfromScoreIndexes()->createJson(indexes);
    emit sendDartsScoreIndexesAsJson(json);
}
