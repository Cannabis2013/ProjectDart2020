#include "injectdartsroutines.h"
#include "SLAs/dmcservices.h"
#include "InputServices/dartsinputstojson.h"
#include "InputServices/dartssetipthint.h"
#include "InputServices/dartsaddinputtodb.h"
#include "InputServices/dartsinputtojson.h"
#include "TournamentServices/dartscreatetournament.h"
#include "TournamentServices/dartsremovetournaments.h"
#include "TournamentServices/dartsresettournament.h"
#include "TournamentServices/dartstournamentrepair.h"
#include "TournamentsDbServices/dartsconverttojson.h"
#include "TournamentServices/dartssetwinner.h"
#include "TournamentServices/dartsverifyconsistency.h"
#include "IndexesServices/updatedartsindexes.h"
#include "PersistServices/dartspersist.h"

void InjectDartsRoutines::inject(DMCServices *context)
{
    injectTournamentRoutines(context);
    injectInputRoutines(context);
    injectIndexRoutines(context);
    injectPersistenceRoutines(context);
}

void InjectDartsRoutines::injectTournamentRoutines(DMCServices *context)
{
    auto tnmServices = context->tournamentServices();
    tnmServices->setTournamentRepair(new DartsTournamentRepair(context));
    tnmServices->setDartsJsonBuilder(new DartsConvertToJson(context));
    tnmServices->setVerifyConsistency(new DartsVerifyConsistency(context));
    tnmServices->setSetWinner(new DartsSetWinner(context));
    tnmServices->setCreateTournament(new DartsCreateTournament(context));
    tnmServices->setRemoveTournaments(new DartsRemoveTournaments(context));
    tnmServices->setResetTournament(new DartsResetTournament(context));
}

void InjectDartsRoutines::injectInputRoutines(DMCServices *context)
{
    auto iptServices = context->inputServices();
    iptServices->setCreateJsonFromInputs(new DartsInputsToJson(context));
    iptServices->setSetInputHint(new DartsSetIptHint(context));
    iptServices->setAddInputToDb(new DartsAddInputToDb(context));
    iptServices->setInputToJson(new DartsInputToJson(context));
}

void InjectDartsRoutines::injectIndexRoutines(DMCServices *context)
{
    auto idxServices = context->indexServices();
    idxServices->setUpdateIndexes(new UpdateDartsIndexes(context));
}

void InjectDartsRoutines::injectPersistenceRoutines(DMCServices *context)
{
    auto persServices = context->persistenceServices();
    persServices->setPersist(new DartsPersist(context));
}
