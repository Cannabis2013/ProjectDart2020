#include "dartsresettournament.h"
#include "SLAs/dartsmodelsservices.h"
#include "TournamentModelsSLAs/idartstournament.h"

DartsResetTournament::DartsResetTournament(DartsModelsServices *services)
{
    _services = services;
    _tnmServices = services->tournamentServices();
    _dartsDb = services->tournamentServices()->dartsDbCtx();
    _iptsDb = _services->inputServices()->inputsDb();
}

void DartsResetTournament::reset(const QUuid &tournamentID) const
{
    removeTournamentInputs(tournamentID);
    resetTournament(tournamentID);
}

void DartsResetTournament::removeTournamentInputs(const QUuid &tournamentID) const
{
    auto models = _iptsDb->models([=](Model *model){
        auto input = dynamic_cast<IDartsInput*>(model);
        return input->tournamentId() == tournamentID;
    });
    for (const auto &model : qAsConst(models)) {
       auto indexOf = _iptsDb->indexOf(model);
       _iptsDb->remove(indexOf);
    }
}

void DartsResetTournament::resetTournament(const QUuid &tournamentID) const
{
    auto model = _dartsDb->model([=](Model *model){return model->id() == tournamentID;});
    auto tournament = dynamic_cast<IDartsTournament*>(model);
    auto indexOf = _dartsDb->indexOf(model);
    auto dartsBuilder = _tnmServices->tournamentBuilder();
    auto initTournament = dartsBuilder->createInitial([=](Model *model){
        auto newTournament = dynamic_cast<IDartsTournament*>(model);
        newTournament->setId(tournamentID);
        newTournament->setPlayerIds(tournament->playerIds());
        newTournament->setPlayerNames(tournament->playerNames());
        newTournament->setKeyPoint(tournament->initialRemaining());
        newTournament->setInputHint(tournament->inputHint());
        newTournament->setTitle(tournament->title());
    });
    _dartsDb->replace(indexOf,initTournament);
    delete tournament;
}
