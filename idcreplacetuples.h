#ifndef IDCREPLACETUPLES_H
#define IDCREPLACETUPLES_H

#include "dctuple.h"
#include "idcscoresservice.h"

class IDCReplaceTuples
{
public:
    virtual void replace(const QVector<DCContext::DCPTuple> &tuples, IDCScoresService *scoresService) const = 0;
};
#endif // IDCREPLACETUPLES_H
