#ifndef GETDARTSSCOREMODELSBYHINT_H
#define GETDARTSSCOREMODELSBYHINT_H

#include "ibinaryservice.h"
#include "idartsscoreinput.h"
#include <qvector.h>

class GetDartsScoreModelsByHint:
        public IBinaryService<const QVector<const IDartsScoreInput*>&,
                              const int&,
                              QVector<const IDartsScoreInput*>>
{
public:
    QVector<const IDartsScoreInput*> service(const QVector<const IDartsScoreInput*>& models,
                                             const int& hint) override
    {
        QVector<const IDartsScoreInput*> list;
        for (const auto& model : models) {
            if(model->hint()== hint)
                list << model;
        }
        return list;
    }
};

#endif // GETDARTSSCOREMODELSBYHINT_H
