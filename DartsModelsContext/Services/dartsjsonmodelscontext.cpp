#include "dartsjsonmodelscontext.h"
DartsJsonModelsContext::DartsJsonModelsContext()
{
    setTournamentServices();
    setIndexesServices();
    setInputServices();
    setInputDbUtilityServices();
    setModelUtilityServices();
    fetchAll();
}
void DartsJsonModelsContext::setModelUtilityServices()
{
    setSetTournamentPlayerDetails(new SetDartsPlayerDetails);
}
void DartsJsonModelsContext::setTournamentServices()
{
    setDartsDbContext(new DartsDbContext(new ReadByteArray, new WriteByteArray));
    setResetTournament(new ResetDartsTournament);
    setGetTournament(new GetDartsTournamentFromDb);
    setTournamentJsonBuilder(new DartsJsonBuilder);
    setTournamentBuilder(new DartsTournamentBuilder);
    setWinnerInfoBuilder(new DartWinnerModelBuilder);
    setMetaModelBuilder(new DartsMetaModelBuilder);
    setGetTournamentIds(new GetDartsIds);
}

void DartsJsonModelsContext::setIndexesServices()
{
    setIndexBuilder(new DartsIndexBuilder);
    setUpdateIndexes(new UpdateDartsIndexes);
}
void DartsJsonModelsContext::setInputServices()
{
    setInputsDbContext(new DartsInputsDbContext(new ReadByteArray, new WriteByteArray));
    setGetInputFromDb(new GetDartsInputFromDb);
    setSortInputsByIndexes(new SortDartsInputsByIndexes);
    setInputBuilder(new DartsInputBuilder);
    setInputJsonBuilder(new DartsInputJsonBuilder);
}
void DartsJsonModelsContext::setInputDbUtilityServices()
{
    setGetInputsFromDb(new GetDartsInputModels);
    setSortInputs(new SortDartsInputs);
    setCountInputs(new CountDartsInputs);
    setRemoveInputsFromDb(new RemoveDartsInputsFromDb);
}
void DartsJsonModelsContext::fetchAll()
{
    dartsDbContext()->fetchModels(tournamentBuilder());
    inputsDb()->fetchModels(inputBuilder());
}
