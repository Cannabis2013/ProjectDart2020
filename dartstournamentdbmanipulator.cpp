#include "dartstournamentdbmanipulator.h"

using namespace DartsModelsContext;

DartsTournamentDbManipulator::Id DartsModelsContext::DartsTournamentDbManipulator::addDartsTournamentToDb(const Tournament *tournament, DbService *dbService)
{
    dbService->add(tournament);
    return tournament->id();
}

bool DartsModelsContext::DartsTournamentDbManipulator::removeTournamentsByIndexes(const QVector<int> &indexes, DbService *dbService) const
{
    auto r = true;
    auto startIndex = indexes.count() - 1;
    for (int i = startIndex; i >= 0; --i) {
        auto index = indexes.at(i);
        r = dbService->remove(index) ? r : false;
    }
    return r;
}
