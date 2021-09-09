#ifndef DCSCORESSERVICE_H
#define DCSCORESSERVICE_H

#include "idcscoresservice.h"

class DCScoresService : public IDCScoresService
{
public:
    virtual DartsScoreModels &scoreModels() override
    {
        return _tuples;
    }
    virtual void resetTuples(const IDartsMetaData *metaService) override
    {
        setInitialValues(_tuples,metaService->initialScore());
    }
private:
    void setInitialValues(const DartsScoreModels &tuples, const int &value) const
    {
        for (auto tuple : tuples)
            tuple.totalScore = value;
    }
    DCContext::DCScoreModel createTuple(const QString &name, const QUuid &id, const int &score) const
    {
        return DCContext::DCScoreModel(id,name,score);
    }
    DartsScoreModels _tuples;
};
#endif // DARTSSCORES_H
