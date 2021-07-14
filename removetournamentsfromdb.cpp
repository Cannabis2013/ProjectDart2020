#include "removetournamentsfromdb.h"

using namespace DartsModelsContext;

bool DartsModelsContext::RemoveTournamentsFromDb::removeTournamentsByIndexes(const QVector<int> &indexes, IDartsTournamentDb *dbService) const
{
    auto r = true;
    auto startIndex = indexes.count() - 1;
    for (int i = startIndex; i >= 0; --i) {
        auto index = indexes.at(i);
        r = dbService->remove(index) ? r : false;
    }
    return r;
}
