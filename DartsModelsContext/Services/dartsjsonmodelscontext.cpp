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
    setTournamentJsonBuilder(new DartsTournamentJsonBuilder);
    setTournamentBuilder(new DartsTournamentBuilder);
    setWinnerInfoBuilder(new ExtractWinnerInfoFromJson);
    setMetaModelBuilder(new DartsMetaModelBuilder);
}

void DartsJsonModelsContext::setIndexesServices()
{
    setIndexesDbContext(new DartsIndexesDbContext(new ReadByteArray, new WriteByteArray));
    setIndexesBuilder(new DartsIndexesBuilder);
    setIndexesJsonBuilder(new DartsIndexesJsonBuilder);
    setRemoveIndexes(new RemoveDartsIndexes);
    setUpdateIndexes(new UpdateDartsIndexes);
    setGetIndexesModel(new GetDartsIndexesModel);
    setResetIndexes(new ResetDartsIndexes);
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
    indexesDbContext()->fetchModels(indexesBuilder());
}
