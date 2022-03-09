#include "dartsresettournament.h"
#include "SLAs/dartsmodelsservices.h"
#include "TournamentModelsSLAs/idartstournament.h"

bool DartsResetTournament::reset(const QUuid &tournamentID, DartsModelsServices *services)
{
    removeTournamentInputs(tournamentID,services);
    resetTournament(tournamentID,services);
    return persistChanges(services);
}

void DartsResetTournament::removeTournamentInputs(const QUuid &tournamentID, DartsModelsServices *services) const
{
    auto dbContext = services->inputServices()->dbContext();
    auto models = dbContext->models([=](Model *model, const int &){
        auto input = dynamic_cast<IDartsInput*>(model);
        return input->tournamentId() == tournamentID;
    });
    for (const auto &model : qAsConst(models)) {
       auto indexOf = dbContext->indexOf(model);
       dbContext->remove(indexOf);
    }
}

void DartsResetTournament::resetTournament(const QUuid &tournamentID, DartsModelsServices *services) const
{
    auto tournamentServices = services->tournamentServices();
    auto dbContext = tournamentServices->dbContext();
    auto model = dbContext->model([=](Model *model){return model->id() == tournamentID;});
    auto tournament = dynamic_cast<IDartsTournament*>(model);
    auto indexOf = dbContext->indexOf(model);
    auto dartsBuilder = tournamentServices->tournamentBuilder();
    auto initTournament = dartsBuilder->createInitial([=](Model *model){
        auto initTournament = dynamic_cast<IDartsTournament*>(model);
        initTournament->setId(tournamentID);
        initTournament->setPlayerIds(tournament->playerIds());
        initTournament->setPlayerNames(tournament->playerNames());
        initTournament->setKeyPoint(tournament->initialRemaining());
        initTournament->setInputHint(tournament->inputHint());
        initTournament->setTitle(tournament->title());
    });
    dbContext->replace(indexOf,initTournament);
    delete tournament;
}

bool DartsResetTournament::persistChanges(DartsModelsServices *services)
{
    auto tournamentDb = services->tournamentServices()->dbContext();
    auto inputDb = services->inputServices()->dbContext();
    auto tournamentSaved = tournamentDb->saveChanges();
    auto inputsSaved = inputDb->saveChanges();
    return tournamentSaved && inputsSaved;
}
