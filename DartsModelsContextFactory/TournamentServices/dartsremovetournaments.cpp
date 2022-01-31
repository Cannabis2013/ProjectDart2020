#include "dartsremovetournaments.h"

#include "SLAs/dmcservices.h"

DartsRemoveTournaments::DartsRemoveTournaments(DMCServices *services): _services(services)
{
    _tnmServices = _services->tournamentServices();
    _tnmdb = _tnmServices->dartsDbCtx();
    _iptServices = _services->inputServices();
    _iptdb = _iptServices->inputsDb();
}

void DartsRemoveTournaments::remove(const Indexes &indexes)
{
    auto tournamentIDs = getTournamentIDs(indexes);
    for (const auto &id : qAsConst(tournamentIDs))
        removeTournamentInputs(id);
    removeModels(indexes,_tnmdb);
}

QVector<QUuid> DartsRemoveTournaments::getTournamentIDs(const Indexes &indexes)
{
    QVector<QUuid> ids;
    for (const auto &index : indexes)
        ids << _tnmdb->model(index)->id();
    return ids;
}

void DartsRemoveTournaments::removeTournamentInputs(const QUuid &tournamentID)
{

    Indexes indexes = getInputIndexes(tournamentID);
    removeModels(indexes,_iptdb);
}

IDartsRemoveTournaments::Indexes DartsRemoveTournaments::getInputIndexes(const QUuid &tournamentID)
{
    auto models = _iptdb->models();
    Indexes indexes;
    for (int i = 0; i < models.count(); ++i) {
        auto model = models.at(i);
        auto input = dynamic_cast<IDartsInput*>(model);
        if(input->tournamentId() == tournamentID)
            indexes << i;
    }
    return indexes;
}

void DartsRemoveTournaments::removeModels(const Indexes &indexes, DbContext *dbContext)
{
    for (int i = indexes.count() - 1; i >= 0; --i)
        dbContext->remove(indexes.at(i));
}
