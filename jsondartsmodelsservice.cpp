#include "jsondartsmodelsservice.h"
using namespace DartsModelsContext;
JsonDartsModelsService::JsonDartsModelsService()
{
    setTournamentServices();
    setScoreInputServices();
    setPointInputServices();
    setInputDbUtilityServices();
    setPlayerRelatedServices();
    setModelUtilityServices();
    setModelsServices();
    setUtilitiyServices();
}
void JsonDartsModelsService::setPlayerRelatedServices()
{
    setGetPlayerModelsFromDb(new GetDartsPlayerModelsFromDb);
    setDartsPlayerJsonBuilder(new DartsPlayerJsonBuilder);
    setPlayerModelBuilder(new DartsPlayerModelBuilder);
    setDartsPlayersDb(new PlayerModelsLocalJsonDb);
    setGetDataFromPlayerModels(new GetDataFromPlayerModels);
}
void JsonDartsModelsService::setModelUtilityServices()
{
    setDartsModelManipulator(new DartsModelManipulator);
}
void JsonDartsModelsService::setTournamentServices()
{
    setGetTournament(new GetDartsTournamentFromDb);
    setTournamentDbManipulator(new DartsTournamentDbManipulator);
    setDartsTournamentCreateJson(new DartsTournamentJsonBuilder);
    setDartsTournamentJsonAddDetails(new AddDetailsToTournamentJson);
    setCreateDartsTournament(new DartsTournamentBuilder);
    setDartsTournamentDb(new DartsTournamentsJsonDb);
    setGetDataFromDartsTournament(new GetDataFromDartsTournament);
    setGetDartsTournamentDataFromJson(new GetDartsTournamentDataFromjson);
}
void JsonDartsModelsService::setScoreInputServices()
{
    using namespace DartsDbContext;
    setDartsScoresDb(new DartsScoreJsonDb);
    setGetScoreFromDb(new GetDartsScoreFromDb);
    setDartsScoreSetHint(new DartsScoreSetHint);
    setCreateIndexesFromScoreModels(new CreateDartsScoreIndexes);
    setCreateJsonFromScoreModels(new DartsCreateJsonFromScores);
    setCreateJsonfromScoreIndexes(new DartsCreateJsonFromScoreIndexes);
    setCreateScoreModel(new DartsCreateScoreModel);
    setCreateJsonFromDartsScore(new DartsCreateJsonFromScoreModel);
}
void JsonDartsModelsService::setPointInputServices()
{
    using namespace DartsDbContext;
    setDartsPointsDb(new DartsPointJsonDb);
    setGetPointFromDb(new GetDartsPointFromDb);
    setDartsPointSetHint(new DartsPointSetHint);
    setCreateIndexesFromPointModels(new DartsCreatePointIndexes);
    setSortPointInputsByIndexes(new SortDartsPointInputsByIndexes);
    setDartsPointsJsonService(new DartsModelsCreateJsonFromPoints);
    setCreateJsonFromPointIndexes(new CreateJsonFromDartsPointIndexes);
    setCreatePointModel(new DartsCreatePointModel);
    setCreateJsonFromDartsPoint(new DartsCreateJsonFromPointModel);
}
void JsonDartsModelsService::setInputDbUtilityServices()
{
    setGetInputsFromDb(new GetInputModelsService);
    setSortInputs(new InputModelsSortService);
    setCountInputs(new InputModelsCountService);
    setRemoveInputsFromDb(new RemoveInputsFromDb);
}

void JsonDartsModelsService::setModelsServices()
{
    setCreateJsonMetaData(new DartsCreateJsonMetaData);
}

void JsonDartsModelsService::setUtilitiyServices()
{
    setDbGetIndexesFromjson(new DbGetIndexesFromJson);
}
