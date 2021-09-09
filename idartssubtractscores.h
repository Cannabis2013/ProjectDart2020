#ifndef IDCCALCSCORE_H
#define IDCCALCSCORE_H

#include <idcscoresservice.h>
#include "idcmodel.h"
#include "dcscoremodel.h"

class IDCCreateCandidateTuples
{
public:
    virtual DCContext::DCScoreModel getCandidate(const DCContext::IDCModel *model, IDCScoresService *scoresService) = 0;
    virtual QVector<DCContext::DCScoreModel> getTupleCandidates(const QVector<DCContext::IDCModel*> &models, IDCScoresService *scoresService) = 0;
};

#endif // IDARTSSUBTRACTSCORES_H
