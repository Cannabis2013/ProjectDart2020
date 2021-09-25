#include "dartsjsonmodelscontext.h"
DartsJsonModelsContext::DartsJsonModelsContext()
{
    setTournamentServices();
    setPointInputServices();
    setInputDbUtilityServices();
    setModelUtilityServices();
    setModelsServices();
}
void DartsJsonModelsContext::setModelUtilityServices()
{
    setAddToTournamentModel(new AddPlayerDetailsToTournament);
}
void DartsJsonModelsContext::setTournamentServices()
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
void DartsJsonModelsContext::setPointInputServices()
{
    using namespace DartsDbContext;
    setInputsDbService(new DartsInputsJsonDb);
    setGetInputFromDb(new DMCGetInputFromDb);
    setDartsPointSetHint(new DMCSetInputHint);
    setIndexesBuilder(new DMCCreateIndexes);
    setSortInputsByIndexes(new SortDartsPointInputsByIndexes);
    setInputsToJsonService(new DMCInputsToJson);
    setIndexesToJsonService(new DMCIndexesToJson);
    setCreatePointModel(new DMCCreateInput);
    setInputToJsonService(new DMCInputToJson);
}
void DartsJsonModelsContext::setInputDbUtilityServices()
{
    setGetInputsFromDb(new DMCGetInputModels);
    setSortInputs(new DMCSortInputs);
    setCountInputs(new DMCCountInputs);
    setRemoveInputsFromDb(new DMCRemoveInputsFromDb);
    setRemoveModelsFromDb(new RemoveModelsFromDb);
}

void DartsJsonModelsContext::setModelsServices()
{
    setCreateJsonMetaData(new DartsCreateJsonMetaData);
}
