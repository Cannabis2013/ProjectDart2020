#include "dartsjsonmodelscontext.h"

DartsJsonModelsContext::DartsJsonModelsContext()
{
    setTournamentServices();
    setInputServices();
    setInputDbUtilityServices();
    setModelUtilityServices();
    fetchTournamentDb();
}
void DartsJsonModelsContext::setModelUtilityServices()
{
    setSetTournamentPlayerDetails(new SetDartsPlayerDetails);
}
void DartsJsonModelsContext::setTournamentServices()
{
    setTournamentsDbContext(new DartsDbContext(new ReadByteArray, new WriteByteArray));
    setGetTournament(new GetDartsTournamentFromDb);
    setTournamentJsonBuilder(new DartsTournamentJsonBuilder);
    setTournamentBuilder(new DartsTournamentBuilder);
    setWinnerInfoBuilder(new ExtractWinnerInfoFromJson);
}

void DartsJsonModelsContext::setIndexesServices()
{
    setRemoveIndexes(new RemoveDartsIndexes);
    setIndexesDbContext(new DartsIndexesDbContext(new ReadByteArray, new WriteByteArray));
    setUpdateIndexes(new UpdateDartsIndexes);
}
void DartsJsonModelsContext::setInputServices()
{
    setInputsDbContext(new DartsInputsDbContext(new ReadByteArray, new WriteByteArray));
    setGetInputFromDb(new GetDartsInputFromDb);
    setSortInputsByIndexes(new SortDartsInputsByIndexes);
    setInputModelBuilder(new DartsInputBuilder);
    setInputJsonBuilder(new DartsInputJsonBuilder);
}
void DartsJsonModelsContext::setInputDbUtilityServices()
{
    setGetInputsFromDb(new GetDartsInputModels);
    setSortInputs(new SortDartsInputs);
    setCountInputs(new CountDartsInputs);
    setRemoveInputsFromDb(new RemoveDartsInputsFromDb);
}

void DartsJsonModelsContext::fetchTournamentDb()
{
    tournamentDb()->fetchModels(tournamentBuilder());
}
