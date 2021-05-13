#ifndef GETDARTSSCOREMODELSBYROUNDINDEX_H
#define GETDARTSSCOREMODELSBYROUNDINDEX_H

#include "ibinaryservice.h"
#include "idartsscoreinput.h"
#include <qvector.h>

class GetDartsScoreModelsByRoundIndex:
        public IBinaryService<const QVector<const IDartsScoreInput*>&,
                              const int&,
                              QVector<const IDartsScoreInput*>>
{
public:
    QVector<const IDartsScoreInput*> service(const QVector<const IDartsScoreInput*>& models,
                                             const int& roundIndex) override
    {
        QVector<const IDartsScoreInput*> list;
        for (const auto& model : models) {
            if(model->roundIndex() == roundIndex)
                list << model;
        }
        return list;
    }
};

#endif // GETDARTSSCOREMODELSBYROUNDINDEX_H
