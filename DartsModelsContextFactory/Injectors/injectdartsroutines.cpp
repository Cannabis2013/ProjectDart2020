#include "injectdartsroutines.h"
#include "SLAs/dartsmodelsservices.h"
#include "InputServices/dartsinputstobytearray.h"
#include "Routines/dartshideplayerinput.h"
#include "Routines/dartsaddinputtodb.h"
#include "TournamentsDbServices/dartsconverttojson.h"
#include "SLAs/dartsmodelsroutines.h"
#include "dartscontext.h"
#include "Routines/addtournamenttodb.h"
#include "Routines/removetournamentsfromdb.h"
#include "Routines/dartsresettournament.h"
#include "Routines/dartsdisplayplayerinput.h"
#include "Routines/dartsinputtojson.h"

void InjectDartsRoutines::inject(DartsContext *context)
{
    injectTournamentRoutines(context);
    injectInputRoutines(context);
}

void InjectDartsRoutines::injectTournamentRoutines(DartsModelsRoutines *context)
{
    context->setAddTournamentToDb(new AddTournamentToDb);
    context->setRemoveTournaments(new RemoveTournamentsFromDb);
    context->setResetTournament(new DartsResetTournament);
}

void InjectDartsRoutines::injectInputRoutines(DartsModelsRoutines *context)
{
    context->setCreateJsonFromInputs(new DartsInputsToByteArray);
    context->setHidePlayerInput(new DartsHidePlayerInput);
    context->setDisplayPlayerInput(new DartsDisplayPlayerInput);
    context->setAddInputToDb(new DartsAddInputToDb);
    context->setInputToJson(new DartsInputToJson);
}
