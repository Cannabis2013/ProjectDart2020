#include "injectdartsroutines.h"

#include <DartsModelsContext/dartscontext.h>
#include <DartsModelsContext/SLAs/dartsmodelsroutines.h>
#include <DartsModelsContext/SLAs/dartsmodelsroutines.h>
#include <LocalDartsModelsContext/Routines/addtournamenttodb.h>
#include <LocalDartsModelsContext/Routines/dartsaddinputtodb.h>
#include <LocalDartsModelsContext/Routines/dartsdisplayplayerinput.h>
#include <LocalDartsModelsContext/Routines/dartshideplayerinput.h>
#include <LocalDartsModelsContext/Routines/dartsinputtojson.h>
#include <LocalDartsModelsContext/Routines/dartsresettournament.h>
#include <LocalDartsModelsContext/Routines/dartstournamentrepair.h>
#include <LocalDartsModelsContext/Routines/gettournamentasjson.h>
#include <LocalDartsModelsContext/Routines/gettournamentsasjson.h>
#include <LocalDartsModelsContext/Routines/removetournamentsfromdb.h>

#include <LocalDartsModelsContext/TournamentServices/dartssetwinner.h>

#include <LocalDartsModelsContext/InputServices/dartsinputstobytearray.h>
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
    context->setSetWinner(new DartsSetWinner);
    context->setGetTournamentAsJson(new GetTournamentAsJson);
    context->setGetTournamentsAsJson(new GetTournamentsAsJson);
    context->setTournamentRepair(new DartsTournamentRepair);
}

void InjectDartsRoutines::injectInputRoutines(DartsModelsRoutines *context)
{
    context->setCreateJsonFromInputs(new DartsInputsToByteArray);
    context->setHidePlayerInput(new DartsHidePlayerInput);
    context->setDisplayPlayerInput(new DartsDisplayPlayerInput);
    context->setAddInputToDb(new DartsAddInputToDb);
    context->setInputToJson(new DartsInputToJson);
}
