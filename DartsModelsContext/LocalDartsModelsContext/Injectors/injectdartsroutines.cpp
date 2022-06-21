#include "injectdartsroutines.h"
#include <DartsModelsContext/Contracts/dartsmodelsroutines.h>
#include <DartsModelsContext/Contracts/dartsmodelsroutines.h>
#include <DartsModelsContext/LocalDartsModelsContext/Routines/addtournamenttodb.h>
#include <DartsModelsContext/LocalDartsModelsContext/Routines/dartsaddinputtodb.h>
#include <DartsModelsContext/LocalDartsModelsContext/Routines/dartsdisplayplayerinput.h>
#include <DartsModelsContext/LocalDartsModelsContext/Routines/dartshideplayerinput.h>
#include <DartsModelsContext/LocalDartsModelsContext/Routines/dartsinputtojson.h>
#include <DartsModelsContext/LocalDartsModelsContext/Routines/dartsresettournament.h>
#include <DartsModelsContext/LocalDartsModelsContext/Routines/dartstournamentrepair.h>
#include <DartsModelsContext/LocalDartsModelsContext/Routines/gettournamentasjson.h>
#include <DartsModelsContext/LocalDartsModelsContext/Routines/gettournamentsasjson.h>
#include <DartsModelsContext/LocalDartsModelsContext/Routines/removetournamentsfromdb.h>
#include <DartsModelsContext/LocalDartsModelsContext/dartscontext.h>
#include <DartsModelsContext/LocalDartsModelsContext/TournamentServices/dartssetwinner.h>
#include <DartsModelsContext/LocalDartsModelsContext/InputServices/dartsinputstobytearray.h>

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
