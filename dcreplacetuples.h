#ifndef DCREPLACETUPLES_H
#define DCREPLACETUPLES_H

#include "idcreplacetuples.h"

class DCReplaceTuples : public IDCReplaceTuples
{
public:
    virtual void replace(const QVector<DCContext::DCPTuple> &tuples, IDCScoresService *scoresService) const override
    {
        scoresService->tuples().clear();
        for (const auto &tuple : tuples)
            scoresService->tuples().append(tuple);
    }
};

#endif // DCREPLACETUPLES_H
