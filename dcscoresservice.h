#ifndef DCSCORESSERVICE_H
#define DCSCORESSERVICE_H

#include "idcscoresservice.h"

class DCScoresService : public IDCScoresService
{
public:
    virtual DartsPlayerTuples &tuples() override
    {
        return _tuples;
    }
    virtual void resetTuples(const IDartsMetaData *metaService) override
    {
        setInitialValues(_tuples,metaService->initialScore());
    }
private:
    void setInitialValues(const DartsPlayerTuples &tuples, const int &value) const
    {
        for (auto tuple : tuples)
            tuple.totalScore = value;
    }
    DCContext::DCPTuple createTuple(const QString &name, const QUuid &id, const int &score) const
    {
        return DCContext::DCPTuple(id,name,score);
    }
    DartsPlayerTuples _tuples;
};
#endif // DARTSSCORES_H
