#include "removetournamentsfromdb.h"
#include <qvector.h>
#include <DartsModelsContext/SLAs/dartsmodelsservices.h>
#include <DartsModelsContext/InputModelsSLAs/idartsinput.h>

bool RemoveTournamentsFromDb::remove(const Indexes &indexes, DartsModelsServices *services)
{
        removeTournaments(indexes,services);
        return persistChanges(services);
}

void RemoveTournamentsFromDb::removeTournaments(const Indexes &indexes, DartsModelsServices *services)
{
        auto tournamentIDs = getTournamentIDs(indexes,services);
        for (const auto &id : qAsConst(tournamentIDs))
                removeTournamentInputs(id,services);
        removeModels(indexes,services);
}

bool RemoveTournamentsFromDb::persistChanges(DartsModelsServices *services)
{
        auto tournamentDb = services->tournamentServices()->dbContext();
        auto inputDb = services->inputServices()->dbContext();
        auto tournamentSaved = tournamentDb->saveChanges();
        auto inputsSaved = inputDb->saveChanges();
        return tournamentSaved && inputsSaved;
}

QVector<QUuid> RemoveTournamentsFromDb::getTournamentIDs(const Indexes &indexes, DartsModelsServices *services)
{
        auto dbContext = services->tournamentServices()->dbContext();
        QVector<QUuid> ids;
        for (const auto &index : indexes)
                ids << dbContext->model(index)->id();
        return ids;
}

void RemoveTournamentsFromDb::removeTournamentInputs(const QUuid &tournamentID, DartsModelsServices *services)
{
        Indexes indexes = getInputIndexes(tournamentID,services);
        removeModels(indexes,services);
}

IDartsRemoveTournaments::Indexes RemoveTournamentsFromDb::getInputIndexes(const QUuid &tournamentID, DartsModelsServices *services)
{
        auto dbContext = services->inputServices()->dbContext();
        auto models = dbContext->models();
        Indexes indexes;
        for (int i = 0; i < models.count(); ++i) {
                auto model = models.at(i);
                auto input = dynamic_cast<IDartsInput*>(model);
                if(input->tournamentId() == tournamentID)
                        indexes << i;
        }
        return indexes;
}

void RemoveTournamentsFromDb::removeModels(const Indexes &indexes, DartsModelsServices *services)
{
    auto dbContext = services->tournamentServices()->dbContext();
    for (int i = indexes.count() - 1; i >= 0; --i)
        dbContext->remove(indexes.at(i));
}
