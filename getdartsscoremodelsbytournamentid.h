#ifndef GETDARTSSCOREMODELSBYTOURNAMENTID_H
#define GETDARTSSCOREMODELSBYTOURNAMENTID_H

#include "ibinaryservice.h"
#include "idartsscoreinput.h"
#include <qvector.h>

class GetDartsScoreModelsByTournamentId :
        public IBinaryService<const QVector<const IDartsScoreInput*>&,
                              const QUuid&,
                              QVector<const IDartsScoreInput*>>
{
public:
    QVector<const IDartsScoreInput*> service(const QVector<const IDartsScoreInput*>& models,
                                             const QUuid& tournamentId) override
    {
        QVector<const IDartsScoreInput*> list;
        for (const auto& model : models) {
            if(model->tournamentId() == tournamentId)
                list << model;
        }
        return list;
    }
};

#endif // GETDARTSSCOREMODELSBYTOURNAMENTID_H
