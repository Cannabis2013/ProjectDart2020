#ifndef IDCCALCSCORE_H
#define IDCCALCSCORE_H

#include "idcscoresservice.h"
#include "DCInputsSLA/idcinputmodel.h"
#include "dcscoremodel.h"

class IDCCreateCandidateTuples
{
public:
    virtual DCContext::DCScoreModel getCandidate(const DCContext::IDCInputModel *model, IDCScoresService *scoresService) = 0;
    virtual QVector<DCContext::DCScoreModel> getTupleCandidates(const QVector<DCContext::IDCInputModel*> &models, IDCScoresService *scoresService) = 0;
};

#endif // IDARTSSUBTRACTSCORES_H
