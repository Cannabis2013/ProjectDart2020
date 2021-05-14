#ifndef GETDARTSTOURNAMENTBYID_H
#define GETDARTSTOURNAMENTBYID_H

#include "ibinaryservice.h"
#include "idartstournament.h"
#include "idartstournamentdb.h"

class GetDartsTournamentById :
        public IBinaryService<const QUuid&,
                              const IDartsTournamentDb*,
                              const IDartsTournament*>
{
public:
    const IDartsTournament* service(const QUuid& id,
                                    const IDartsTournamentDb* dbService) override
    {
        auto models = dbService->dartsTournaments();
        for (const auto& model : models) {
            if(model->id() == id)
                return model;
        }
        throw "Darts tournament model not found!";
    }
};

#endif // GETDARTSTOURNAMENTBYID_H
