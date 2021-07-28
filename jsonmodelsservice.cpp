#include "jsonmodelsservice.h"
using namespace ModelsContext;
JsonModelsService::JsonModelsService()
{
    setTournamentServices();
    setScoreInputServices();
    setPointInputServices();
    setInputDbUtilityServices();
    setModelUtilityServices();
    setModelsServices();
}
void JsonModelsService::setModelUtilityServices()
{
    setAddToTournamentModel(new AddPlayerDetailsToTournament);
}
void JsonModelsService::setTournamentServices()
{
    setGetTournament(new GetDartsTournamentFromDb);
    setDartsTournamentCreateJson(new DartsTournamentJsonBuilder);
    setDartsTournamentJsonAddDetails(new AddDetailsToTournamentJson);
    setCreateDartsTournament(new CreateDartsTournamentFromJson);
    setDartsTournamentDb(new DartsTournamentsJsonDb);
    setGetDataFromDartsTournament(new GetDataFromDartsTournament);
    setGetDartsTournamentDataFromJson(new ExtractWinnerInfoFromJson);
    setGetTournamenWinnerModel(new GetTournamentWinner);
    setCreateJsonFromDetails(new CreateJsonFromTournamentDetails);
}
void JsonModelsService::setScoreInputServices()
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
void JsonModelsService::setPointInputServices()
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
void JsonModelsService::setInputDbUtilityServices()
{
    setGetInputsFromDb(new GetInputModelsService);
    setSortInputs(new InputModelsSortService);
    setCountInputs(new InputModelsCountService);
    setRemoveInputsFromDb(new RemoveInputsFromDb);
    setRemoveModelsFromDb(new RemoveModelsFromDb);
}

void JsonModelsService::setModelsServices()
{
    setCreateJsonMetaData(new DartsCreateJsonMetaData);
}
