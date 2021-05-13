#ifndef GETDARTSSCOREMODELSBYPLAYERID_H
#define GETDARTSSCOREMODELSBYPLAYERID_H

#include "ibinaryservice.h"
#include "idartsscoreinput.h"
#include <qvector.h>

class GetDartsScoreModelsByPlayerId :
        public IBinaryService<const QVector<const IDartsScoreInput*>&,
                              const QUuid&,
                              QVector<const IDartsScoreInput*>>
{
    // IBinaryService interface
public:
    QVector<const IDartsScoreInput*> service(const QVector<const IDartsScoreInput*>& models,
                                             const QUuid& playerId) override
    {
        QVector<const IDartsScoreInput*> list;
        for (const auto& model : models) {
            if(model->playerId() == playerId)
                list << model;
        }
        return list;
    }
};

#endif // GETDARTSSCOREMODELSBYPLAYERID_H
