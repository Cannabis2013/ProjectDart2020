#ifndef GETDARTSTOURNAMENTBYINDEXSERVICE_H
#define GETDARTSTOURNAMENTBYINDEXSERVICE_H

#include "ibinaryservice.h"
#include "idartstournament.h"
#include "idartstournamentdb.h"

class GetDartsTournamentByIndexService :
        public IBinaryService<const int&,
                              const IDartsTournamentDb*,
                              const IDartsTournament*>
{
    // IBinaryService interface
public:
    const IDartsTournament* service(const int& index,
                                    const IDartsTournamentDb* dbService) override
    {
        auto model = dbService->dartsTournamentModelFromIndex(index);
        return model;
    }
};

#endif // GETDARTSTOURNAMENTBYINDEXSERVICE_H
