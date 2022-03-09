#include "dartsdisplayplayerinput.h"
#include "TournamentModelsSLAs/idartstournament.h"
#include "IndexesDbSLAs/idartsindex.h"
#include "InputModelsSLAs/idartsinput.h"
#include "SLAs/dartsmodelsservices.h"

bool DartsDisplayPlayerInput::display(QUuid tournamentID, QString name, const QByteArray &indexAsByteArray, DartsModelsServices *services)
{
    auto index = services->indexServices()->indexBuilder()->create(indexAsByteArray);
    auto input = getInputModel(tournamentID,name,index,services);
    updateInputHint(input);
    auto tournament = getTournamentModel(tournamentID,services);
    updateTournamentIndexes(index,tournament);
    auto persisted = persistChanges(services);
    return persisted;
}

DartsDisplayPlayerInput::Model *DartsDisplayPlayerInput::getInputModel(QUuid tournamentID, QString name, IDartsIndex *index, DartsModelsServices *services)
{
    auto inputServices = services->inputServices();
    auto dbContext = inputServices->dbContext();
    auto model = dbContext->model([=](Model *model){
        auto input = dynamic_cast<IDartsInput*>(model);
        if(input->tournamentId() != tournamentID)
            return false;
        else if(input->roundIndex() != index->roundIndex())
            return false;
        else if(input->playerName() != name)
            return false;
        else if(input->attempt() != index->attemptIndex())
            return false;
        else
            return true;
    });
    return model;
}

void DartsDisplayPlayerInput::updateInputHint(Model *model)
{
    auto inputModel = dynamic_cast<IDartsInput*>(model);
    inputModel->setHint(DisplayedHint);
}

DartsDisplayPlayerInput::Model *DartsDisplayPlayerInput::getTournamentModel(QUuid tournamentID, DartsModelsServices *services)
{
    auto dbContext = services->tournamentServices()->dbContext();
    auto tournament = dbContext->model([=](Model *m){return m->id() == tournamentID;});
    return tournament;
}

void DartsDisplayPlayerInput::updateTournamentIndexes(IDartsIndex *index, IModel<QUuid> *model)
{
    auto dartsTournament = dynamic_cast<IDartsTournament*>(model);
    dartsTournament->setTotalTurns(index->totalTurns());
    dartsTournament->setTurnIndex(index->turnIndex());
    dartsTournament->setRoundIndex(index->roundIndex());
    dartsTournament->setSetIndex(index->playerIndex());
    dartsTournament->setAttemptIndex(index->attemptIndex());
}

bool DartsDisplayPlayerInput::persistChanges(DartsModelsServices *services)
{
    auto tournamentDb = services->tournamentServices()->dbContext();
    auto inputDb = services->inputServices()->dbContext();
    auto tournamentSaved = tournamentDb->saveChanges();
    auto inputsSaved = inputDb->saveChanges();
    return tournamentSaved && inputsSaved;
}
