#include "dartstournamentinjector.h"
#include "TournamentsSLAs/dartsslas.h"
#include "TournamentServices/GetDartsTournamentIds.h"
#include "TournamentServices/dartsbuilder.h"
#include "TournamentServices/dartsjsonconverter.h"
#include "TournamentServices/dartsmetamodelbuilder.h"
#include "TournamentServices/dartstournamentrepair.h"
#include "TournamentServices/dartsverifyconsistency.h"
#include "TournamentServices/dartwinnermodelbuilder.h"
#include "TournamentServices/getdartstournamentfromdb.h"
#include "TournamentServices/jsontodartsmodels.h"
#include "TournamentServices/resetdartstournament.h"
#include "TournamentServices/setdartsplayerdetails.h"
#include "TournamentsDbServices/dartsdbcontext.h"
#include "TournamentsDbServices/dartsjsonbuilder.h"
#include "DbServices/convertdartsmodels.h"
#include "TournamentServices/dartssetwinner.h"
void DartsTournamentInjector::injectServices(DartsSLAs *context)
{
    context->setDartsConverter(new DartsJsonConverter);
    context->setDartsDbCtx(new DartsDbContext);
    context->setResetTournament(new ResetDartsTournament);
    context->setSetTournamentPlayerDetails(new SetDartsPlayerDetails);
    context->setTournamentsToJson(new ConvertDartsModels);
    context->setWinnerInfoBuilder(new DartWinnerModelBuilder);
    context->setCreateMeta(new DartsMetaModelBuilder);
    context->setTournamentRepair(new DartsTournamentRepair);
    context->setGetTournament(new GetDartsTournamentFromDb);
    context->setDartsJsonBuilder(new DartsJsonBuilder);
    context->setTournamentBuilder(new DartsBuilder);
    context->setGetTournamentIds(new GetDartsIds);
    context->setJsonToTournaments(new JsonToDartsModels);
    context->setVerifyConsistency(new DartsVerifyConsistency);
    context->setSetWinner(new DartsSetWinner);
}
