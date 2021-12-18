#include "createdartscontext.h"
#include "InputServices/removedartsinputs.h"
#include "FileIOServices/filejsonio.h"
#include "TournamentServices/dartsmetamodelbuilder.h"
#include "InputServices/getdartsinputs.h"
#include "InputServices/sortdartsinputs.h"
#include "InputServices/sortdartsinputsbyindexes.h"
#include "InputServices/countdartsinputs.h"
#include "InputServices/dartsinputbuilder.h"
#include "InputServices/dartsiptsdbctx.h"
#include "InputServices/dartsinputstojson.h"
#include "IndexesServices/updatedartsindexes.h"
#include "TournamentServices/resetdartstournament.h"
#include "TournamentsDbServices/dartsdbcontext.h"
#include "TournamentServices/getdartstournamentfromdb.h"
#include "TournamentServices/dartwinnermodelbuilder.h"
#include "TournamentServices/setdartsplayerdetails.h"
#include "TournamentsDbServices/dartsjsonbuilder.h"
#include "TournamentServices/dartsbuilder.h"
#include "TournamentServices/GetDartsTournamentIds.h"
#include "TournamentServices/dartsverifyconsistency.h"
#include "TournamentServices/dartstournamentrepair.h"
#include "DbServices/persistdbctx.h"
#include "DbServices/loadfromstorage.h"
#include "IndexesServices/dartsidxbuilder.h"
#include "TournamentServices/jsontodartsmodels.h"
#include "InputServices/createdartsinputvalues.h"
#include "dartscontext.h"
AbsDartsCtx *CreateDartsContext::localJson(AbsPlaCtx *playersContext) const
{
    auto context = new DartsContext(playersContext);
    auto ioDevice = new FileJsonIO("DartsData");
    context->setLoadFromStorage(new LoadFromStorage(ioDevice));
    context->setInputsToJson(new DartsInputsToJson);
    context->setSaveToStorage(new SaveToStorage(ioDevice));
    context->setDartsDbCtx(new DartsDbContext);
    context->setSetTournamentPlayerDetails(new SetDartsPlayerDetails);
    context->setResetTournament(new ResetDartsTournament);
    context->setGetTournament(new GetDartsTournamentFromDb);
    context->setTournamentJsonBuilder(new DartsJsonBuilder);
    context->setTournamentBuilder(new DartsBuilder);
    context->setWinnerInfoBuilder(new DartWinnerModelBuilder);
    context->setCreateMeta(new DartsMetaModelBuilder);
    context->setGetTournamentIds(new GetDartsIds);
    context->setUpdateIndexes(new UpdateDartsIndexes);
    context->setInputsDb(new DartsIptsDbCtx);
    context->setGetInputsFromDb(new GetDartsInputs);
    context->setSortInputsByIndexes(new SortDartsInputsByIndexes);
    context->setInputBuilder(new DartsInputBuilder);
    context->setInputsToJson(new DartsInputsToJson);
    context->setSortInputs(new SortDartsInputs);
    context->setCountInputs(new CountDartsInputs);
    context->setRemoveInputsFromDb(new RemoveDartsInputs);
    context->setVerifyConsistency(new DartsVerifyConsistency);
    context->setTournamentRepair(new DartsTournamentRepair);
    context->setIndexBuilder(new DartsIdxBuilder);
    context->setToDartsModels(new JsonToDartsModels);
    context->setCreateInputValues(new CreateDartsInputValues);
    context->loadFromStorage()->load(context->tnmDbCtx(),context->toDartsModels());
    context->loadFromStorage()->load(context->inputsDb(),context->inputBuilder());
    return context;
}
