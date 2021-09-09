#include "jsonmodelsservice.h"
using namespace ModelsContext;
JsonModelsService::JsonModelsService()
{
    setTournamentServices();
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
    setGetDartsTournamentDataFromJson(new ExtractWinnerInfoFromJson);
    setGetTournamenWinnerModel(new GetTournamentWinner);
    setCreateJsonFromDetails(new CreateJsonFromTournamentDetails);
}
void JsonModelsService::setPointInputServices()
{
    using namespace DartsDbContext;
    setInputsDbService(new DartsInputsJsonDb);
    setGetInputFromDb(new GetDartsPointFromDb);
    setDartsPointSetHint(new DartsPointSetHint);
    setIndexesBuilder(new DartsCreateIndexes);
    setSortInputsByIndexes(new SortDartsPointInputsByIndexes);
    setInputsToJsonService(new DartsModelsCreateJsonFromPoints);
    setIndexesToJsonService(new CreateJsonFromDartsPointIndexes);
    setCreatePointModel(new DartsCreateInputModel);
    setInputToJsonService(new DartsCreateJsonFromPointModel);
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
