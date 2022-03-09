#include "dartsaddinputtodb.h"
#include "SLAs/dartsmodelsservices.h"
#include "TournamentModelsSLAs/idartstournament.h"
#include "IndexesDbSLAs/idartsindex.h"

bool DartsAddInputToDb::add(const ByteArray &inputAsByteArray, const ByteArray &indexAsByteArray, const QUuid &tournamentID, DartsModelsServices *services)
{
    addInputToDb(inputAsByteArray,services);
    removeHiddenInputs(tournamentID,services);
    updateTournamentIndex(indexAsByteArray,tournamentID,services);
    return persistChanges(services);
}

void DartsAddInputToDb::addInputToDb(const QByteArray &inputAsByteArray, DartsModelsServices *services)
{
    auto dbContext = services->inputServices()->dbContext();
    auto input = createInput(inputAsByteArray,services);
    dbContext->add(input);
}

void DartsAddInputToDb::updateTournamentIndex(const QByteArray &indexAsByteArray, const QUuid &tournamentID, DartsModelsServices *services)
{
    auto index = services->indexServices()->indexBuilder()->create(indexAsByteArray);
    auto tournament = getTournamentModel(tournamentID,services);
    updateTournament(tournament,index);
}

IDartsTournament *DartsAddInputToDb::getTournamentModel(const QUuid &tournamentID, DartsModelsServices *services)
{
    auto dbContext = services->tournamentServices()->dbContext();
    auto model = dbContext->model([=](Model *m){return m->id() == tournamentID;});
    return dynamic_cast<IDartsTournament*>(model);
}

void DartsAddInputToDb::updateTournament(IDartsTournament *tournament, IDartsIndex *index) const
{
    tournament->setTotalTurns(index->totalTurns());
    tournament->setTurnIndex(index->turnIndex());
    tournament->setRoundIndex(index->roundIndex());
    tournament->setSetIndex(index->playerIndex());
    tournament->setAttemptIndex(index->attemptIndex());
}

DartsAddInputToDb::Model *DartsAddInputToDb::createInput(const ByteArray &byteArray, DartsModelsServices *services) const
{
    auto cvtr = services->inputServices()->inputConverter();
    auto model = cvtr->create(byteArray);
    auto input = dynamic_cast<IDartsInput*>(model);
    input->setHint(DisplayHint);
    return input;
}

void DartsAddInputToDb::removeHiddenInputs(const QUuid &tournamentID, DartsModelsServices *services) const
{
    auto dbContext = services->inputServices()->dbContext();
    dbContext->remove([=](Model *model,const int&){
        auto input = dynamic_cast<IDartsInput*>(model);
        return input->tournamentId() == tournamentID && input->hint() == HiddenHint;
    });
}

bool DartsAddInputToDb::persistChanges(DartsModelsServices *services)
{
    auto tournamentsDb = services->tournamentServices()->dbContext();
    auto inputsDb = services->inputServices()->dbContext();
    auto tournamentChangesSaved =tournamentsDb->saveChanges();
    auto inputsChangesSaved = inputsDb->saveChanges();
    return tournamentChangesSaved && inputsChangesSaved;
}
