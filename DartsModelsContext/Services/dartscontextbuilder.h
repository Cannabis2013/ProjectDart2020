#ifndef DARTSJSONMODELSCONTEXT_H
#define DARTSJSONMODELSCONTEXT_H
#include "DartsModelsContext/Services/dartsctx.h"
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
#include "DartsModelsContext//TournamentsDbServices/dartsdbctx.h"
#include "DartsModelsContext/TournamentServices/getdartstournamentfromdb.h"
#include "DartsModelsContext/TournamentServices/dartwinnermodelbuilder.h"
#include "DartsModelsContext/TournamentServices/setdartsplayerdetails.h"
#include "DartsModelsContext/TournamentsDbServices/dartsjsonbuilder.h"
#include "DartsModelsContext/TournamentServices/dartstournamentbuilder.h"
#include "DartsModelsContext/TournamentServices/GetDartsTournamentIds.h"
#include "DartsModelsContext/TournamentServices/dartsverifyconsistency.h"
#include "DartsModelsContext/TournamentServices/dartstournamentrepair.h"
class DartsContextBuilder
{
public:
    DartsCtx *create() const
    {
        auto mdsCtx = new DartsCtx;
        mdsCtx->setDartsDbCtx(new DartsDbCtx(new ReadByteArray, new WriteByteArray));
        mdsCtx->setSetTournamentPlayerDetails(new SetDartsPlayerDetails);
        mdsCtx->setResetTournament(new ResetDartsTournament);
        mdsCtx->setGetTournament(new GetDartsTournamentFromDb);
        mdsCtx->setTournamentJsonBuilder(new DartsJsonBuilder);
        mdsCtx->setTournamentBuilder(new DartsTournamentBuilder);
        mdsCtx->setWinnerInfoBuilder(new DartWinnerModelBuilder);
        mdsCtx->setMetaModelBuilder(new DartsMetaModelBuilder);
        mdsCtx->setGetTournamentIds(new GetDartsIds);
        mdsCtx->setUpdateIndexes(new UpdateDartsIndexes);
        mdsCtx->setInputsDbContext(new DartsInputsDbContext(new ReadByteArray, new WriteByteArray));
        mdsCtx->setGetInputFromDb(new GetDartsInputFromDb);
        mdsCtx->setSortInputsByIndexes(new SortDartsInputsByIndexes);
        mdsCtx->setInputBuilder(new DartsInputBuilder);
        mdsCtx->setInputJsonBuilder(new DartsInputJsonBuilder);
        mdsCtx->setGetInputsFromDb(new GetDartsInputModels);
        mdsCtx->setSortInputs(new SortDartsInputs);
        mdsCtx->setCountInputs(new CountDartsInputs);
        mdsCtx->setRemoveInputsFromDb(new RemoveDartsInputsFromDb);
        mdsCtx->dartsDbCtx()->fetch(mdsCtx->tournamentBuilder());
        mdsCtx->setVerifyConsistency(new DartsVerifyConsistency);
        mdsCtx->setTournamentRepair(new DartsTournamentRepair);
        mdsCtx->inputsDb()->fetch(mdsCtx->inputBuilder());
        return mdsCtx;
    }
};
#endif // DARTSMODELSSERVICEWITHJSONDB_H
