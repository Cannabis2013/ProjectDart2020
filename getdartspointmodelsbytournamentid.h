#ifndef GETDARTSPOINTMODELSBYTOURNAMENTID_H
#define GETDARTSPOINTMODELSBYTOURNAMENTID_H

#include "ibinaryservice.h"
#include "idartspointdb.h"

class GetDartsPointModelsByTournamentId :public
        IBinaryService<const QUuid&,
                       const IDartsPointDb*,
                       QVector<const IDartsPointInput*>>
{
public:
    QVector<const IDartsPointInput*> service(const QUuid& tournamentId,
                                             const IDartsPointDb* dbService) override
    {
        QVector<const IDartsPointInput*> list;
        auto models = dbService->dartsInputModels();
        for (const auto& model : models) {
            if(model->tournamentId() == tournamentId)
                list << model;
        }
        return list;
    }
};

#endif // GETDARTSPOINTMODELSBYTOURNAMENTID_H
