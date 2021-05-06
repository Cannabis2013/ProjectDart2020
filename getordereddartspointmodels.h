#ifndef GETORDEREDDARTSPOINTMODELS_H
#define GETORDEREDDARTSPOINTMODELS_H

#include "ibinaryservice.h"
#include "idartspointinput.h"
#include "idartspointdb.h"
#include <quuid.h>



class GetOrderedDartsPointsModels :
        public IBinaryService<const QUuid&,
                              const IdartsPointDb<IDartsPointInput<QUuid>>*,
                              QVector<const IDartsPointInput<QUuid>*>>
{
    // IBinaryService interface
public:
    QVector<const IDartsPointInput<QUuid>*> service(const QUuid& tournamentId,
                                                    const IdartsPointDb<IDartsPointInput<QUuid>>* dbService) override
    {
        auto dartsPointModels = dbService->dartsInputModels();
        QVector<const IDartsPointInput<QUuid>*> orderedDartsPointModels;
        for (const auto& dartsPointModel : dartsPointModels) {
            auto modelTournamentId = dartsPointModel->tournamentId();
            if(modelTournamentId == tournamentId)
                orderedDartsPointModels << dartsPointModel;
        }
        std::sort(orderedDartsPointModels.begin(),orderedDartsPointModels.end(),compareCriteria);
        return orderedDartsPointModels;
    }
private:
    struct CompareCriteria {
        bool operator()(const IDartsPointInput<QUuid>* _first, const IDartsPointInput<QUuid>* _second)
        {
            if(_first->roundIndex() < _second->roundIndex())
                return true;
            else if(_first->roundIndex() >= _second->roundIndex())
                return false;
            else if(_first->setIndex() < _second->setIndex())
                return true;
            else
                return false;
        }
    } compareCriteria;
};

#endif // GETORDEREDDARTSPOINTMODELS_H
