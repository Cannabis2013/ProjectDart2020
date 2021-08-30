#ifndef IDPCCALCSCORECANDIDATE_H
#define IDPCCALCSCORECANDIDATE_H

#include <idcscoresservice.h>
#include <idpcmodel.h>

class IDPCCalcScoreCandidate
{
public:
    virtual int getTotalScoreCandidate(const DPCContext::IDPCModel* model, IDCScoresService *scoresService) = 0;
    virtual QVector<int> getTotalScoreCandidate(const QVector<DPCContext::IDPCModel*>& models, IDCScoresService *scoresService) = 0;
};

#endif // IDPCSUBTRACTPLAYERSCORE_H
