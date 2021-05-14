#ifndef DELETETOURNAMENTSBYINDEXESSERVICE_H
#define DELETETOURNAMENTSBYINDEXESSERVICE_H

#include "ibinaryservice.h"
#include "idartstournamentdb.h"

class DeleteTournamentsByIndexesService : public
        IBinaryService<const QVector<int>&,IDartsTournamentDb*,bool>
{
public:
    bool service(const QVector<int>& indexes, IDartsTournamentDb* dbService) override
    {
        auto orderedList = indexes;
        std::sort(orderedList.begin(),orderedList.end());
        for (int i = orderedList.count() - 1; i >= 0; --i)
            dbService->removeDartsTournamentModelByIndex(i);
        return true;
    }
};

#endif // DELETETOURNAMENTSBYINDEXESSERVICE_H
