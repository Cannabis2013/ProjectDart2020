#ifndef GETORDEREDDARTSSCOREMODELS_H
#define GETORDEREDDARTSSCOREMODELS_H

#include "ibinaryservice.h"
#include "idartsscoreinput.h"
#include "idartsscoredb.h"
#include <quuid.h>

class GetOrderedDartsScoreModels :
        public IBinaryService<const QUuid&,
                              const IDartsScoreDb*,
                              QVector<const IDartsScoreInput*>>
{
    // IBinaryService interface
public:
    QVector<const IDartsScoreInput*> service(const QUuid& tournamentId,
                                                    const IDartsScoreDb* dbService) override
    {
        auto dartsPointModels = dbService->dartsScoreModels();
        QVector<const IDartsScoreInput*> orderedDartsPointModels;
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
        bool operator()(const IDartsScoreInput* _first, const IDartsScoreInput* _second)
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

#endif // GETORDEREDDARTSSCOREMODELS_H
