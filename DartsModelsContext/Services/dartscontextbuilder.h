#ifndef DARTSJSONMODELSCONTEXT_H
#define DARTSJSONMODELSCONTEXT_H
#include "DartsModelsContext/Services/dartscontext.h"
#include "DartsModelsContext/InputServices/removedartsinputsfromdb.h"
#include "FileOperationsContext/Services/readbytearray.h"
#include "FileOperationsContext/Services/writebytearray.h"
#include "DartsModelsContext/TournamentServices/dartsmetamodelbuilder.h"
#include "DartsModelsContext/InputServices/getdartsinputmodels.h"
#include "DartsModelsContext/InputServices/sortdartsinputs.h"
#include "DartsModelsContext/InputServices/sortdartsinputsbyindexes.h"
#include "DartsModelsContext/InputServices/countdartsinputs.h"
#include "DartsModelsContext/InputServices/getdartsinputfromdb.h"
#include "DartsModelsContext/InputServices/dartsinputbuilder.h"
#include "DartsModelsContext/InputServices/dartsinputsdbcontext.h"
#include "DartsModelsContext/InputServices/dartsinputjsonbuilder.h"
#include "DartsModelsContext/IndexesServices/updatedartsindexes.h"
#include "DartsModelsContext/IndexesDbServices/dcindexbuilder.h"
#include "DartsModelsContext/TournamentServices/resetdartstournament.h"
#include "DartsModelsContext//TournamentsDbServices/dartsdbcontext.h"
#include "DartsModelsContext/TournamentServices/getdartstournamentfromdb.h"
#include "DartsModelsContext/TournamentServices/dartwinnermodelbuilder.h"
#include "DartsModelsContext/TournamentServices/setdartsplayerdetails.h"
#include "DartsModelsContext/TournamentsDbServices/dartsjsonbuilder.h"
#include "DartsModelsContext/TournamentServices/dartstournamentbuilder.h"
#include "DartsModelsContext/TournamentServices/GetDartsTournamentIds.h"
class DartsContextBuilder
{
public:
    DartsContext *create() const
    {
        auto modelsContext = new DartsContext;
        modelsContext->setDartsDbContext(new DartsDbContext(new ReadByteArray, new WriteByteArray));
        modelsContext->setResetTournament(new ResetDartsTournament);
        modelsContext->setGetTournament(new GetDartsTournamentFromDb);
        modelsContext->setTournamentJsonBuilder(new DartsJsonBuilder);
        modelsContext->setTournamentBuilder(new DartsTournamentBuilder);
        modelsContext->setWinnerInfoBuilder(new DartWinnerModelBuilder);
        modelsContext->setMetaModelBuilder(new DartsMetaModelBuilder);
        modelsContext->setGetTournamentIds(new GetDartsIds);
        modelsContext->setUpdateIndexes(new UpdateDartsIndexes);
        modelsContext->setInputsDbContext(new DartsInputsDbContext(new ReadByteArray, new WriteByteArray));
        modelsContext->setGetInputFromDb(new GetDartsInputFromDb);
        modelsContext->setSortInputsByIndexes(new SortDartsInputsByIndexes);
        modelsContext->setInputBuilder(new DartsInputBuilder);
        modelsContext->setInputJsonBuilder(new DartsInputJsonBuilder);
        modelsContext->setGetInputsFromDb(new GetDartsInputModels);
        modelsContext->setSortInputs(new SortDartsInputs);
        modelsContext->setCountInputs(new CountDartsInputs);
        modelsContext->setRemoveInputsFromDb(new RemoveDartsInputsFromDb);
        modelsContext->dartsDbContext()->fetchModels(modelsContext->tournamentBuilder());
        modelsContext->inputsDb()->fetchModels(modelsContext->inputBuilder());
        return modelsContext;
    }
};
#endif // DARTSMODELSSERVICEWITHJSONDB_H
