#ifndef CREATEDARTSCONTEXT_H
#define CREATEDARTSCONTEXT_H
#include "DartsModelsContext/Services/dartscontext.h"
#include "DartsModelsContext/InputServices/removedartsinputs.h"
#include "FileOperationsContext/Services/filejsonio.h"
#include "DartsModelsContext/TournamentServices/dartsmetamodelbuilder.h"
#include "DartsModelsContext/InputServices/getdartsinputs.h"
#include "DartsModelsContext/InputServices/sortdartsinputs.h"
#include "DartsModelsContext/InputServices/sortdartsinputsbyindexes.h"
#include "DartsModelsContext/InputServices/countdartsinputs.h"
#include "DartsModelsContext/InputServices/dartsinputbuilder.h"
#include "DartsModelsContext/InputServices/dartsiptsdbctx.h"
#include "DartsModelsContext/InputServices/dartsinputstojson.h"
#include "DartsModelsContext/IndexesServices/updatedartsindexes.h"
#include "DartsModelsContext/IndexesDbServices/dcidxconverter.h"
#include "DartsModelsContext/TournamentServices/resetdartstournament.h"
#include "DartsModelsContext//TournamentsDbServices/dartsdbcontext.h"
#include "DartsModelsContext/TournamentServices/getdartstournamentfromdb.h"
#include "DartsModelsContext/TournamentServices/dartwinnermodelbuilder.h"
#include "DartsModelsContext/TournamentServices/setdartsplayerdetails.h"
#include "DartsModelsContext/TournamentsDbServices/dartsjsonbuilder.h"
#include "DartsModelsContext/TournamentServices/dartsbuilder.h"
#include "DartsModelsContext/TournamentServices/GetDartsTournamentIds.h"
#include "DartsModelsContext/TournamentServices/dartsverifyconsistency.h"
#include "DartsModelsContext/TournamentServices/dartstournamentrepair.h"
#include "DartsModelsContext/DbServices/persistdbctx.h"
#include "DartsModelsContext/DbServices/loadfromstorage.h"
#include "DartsModelsContext/IndexesServices/dartsidxbuilder.h"
#include "DartsModelsContext/TournamentServices/jsontodartsmodels.h"
#include "DartsModelsContext/InputServices/createdartsinputvalues.h"
class CreateDartsContext
{
public:
    DartsContext *localJson(AbsPlaCtx *playersContext) const
    {
        auto context = new DartsContext;
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
        context->setPlayersContext(playersContext);
        return context;
    }
};
#endif // DARTSMODELSSERVICEWITHJSONDB_H
