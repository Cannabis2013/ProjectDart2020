#include "jsonmodelsservice.h"
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
    setExtractWinnerInfoService(new ExtractWinnerInfoFromJson);
    setGetTournamenWinnerModel(new GetTournamentWinner);
    setCreateJsonFromDetails(new CreateJsonFromTournamentDetails);
    setTournamentExtractor(new DartsTournamentExtractor);
}
void JsonModelsService::setPointInputServices()
{
    using namespace DartsDbContext;
    setInputsDbService(new DartsInputsJsonDb);
    setGetInputFromDb(new GetDartsPointFromDb);
    setDartsPointSetHint(new DartsPointSetHint);
    setIndexesBuilder(new DartsCreateIndexes);
    setSortInputsByIndexes(new SortDartsPointInputsByIndexes);
    setInputsToJsonService(new DartsInputModelsToJson);
    setIndexesToJsonService(new DartsInputIndexesToJson);
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
