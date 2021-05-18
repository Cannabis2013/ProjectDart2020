#ifndef GETDARTSPOINTMODELSBYTOURNAMENTID_H
#define GETDARTSPOINTMODELSBYTOURNAMENTID_H

#include "ibinaryservice.h"
#include "idartspointdb.h"

class GetDartsPointModelsByTournamentId :public
        IBinaryService<const QUuid&,
                       const IDartsPointDb*,
                       QVector<const DartsModelsContext::IDartsPointInput*>>
{
public:
    QVector<const DartsModelsContext::IDartsPointInput*> service(const QUuid& tournamentId,
                                             const IDartsPointDb* dbService) override
    {
        QVector<const DartsModelsContext::IDartsPointInput*> list;
        auto models = dbService->dartsInputModels();
        for (const auto& model : models) {
            if(model->tournamentId() == tournamentId)
                list << model;
        }
        return list;
    }
};

#endif // GETDARTSPOINTMODELSBYTOURNAMENTID_H
