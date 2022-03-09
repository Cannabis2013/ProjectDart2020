#include "updatedartsindexes.h"
#include "SLAs/dartsmodelsservices.h"
#include "TournamentModelsSLAs/idartstournament.h"

UpdateDartsIndexes::UpdateDartsIndexes(DartsModelsServices *services): _services(services)
{
    _idxServices = services->indexServices();
    _dartsDb = services->tournamentServices()->dbContext();
}

void UpdateDartsIndexes::update(const QByteArray &byteAray, const Uuid &tournamentID) const
{
    auto model = _dartsDb->model([=](Model *model){return model->id() == tournamentID;});
    auto index = _idxServices->indexBuilder()->create(byteAray);
    updateTournament(index,model);
}

void UpdateDartsIndexes::updateTournament(IDartsIndex *index, IModel<QUuid> *model) const
{
    auto dartsTournament = dynamic_cast<IDartsTournament*>(model);
    dartsTournament->setTotalTurns(index->totalTurns());
    dartsTournament->setTurnIndex(index->turnIndex());
    dartsTournament->setRoundIndex(index->roundIndex());
    dartsTournament->setSetIndex(index->playerIndex());
    dartsTournament->setAttemptIndex(index->attemptIndex());
}
