#ifndef IDCCREATECANDIDATEMODELS_H
#define IDCCREATECANDIDATEMODELS_H

#include "DartsController/DCScoresSLAs/idcscoresservice.h"
#include "DartsController/DCInputSLAs/idcinputmodel.h"
#include "DartsController/DCScoresServices/dcscoremodel.h"

class IDCCreateCandidateModels
{
public:
    virtual DCContext::DCScoreModel getCandidate(const DCContext::IDCInputModel *model, IDCScoresService *scoresService) = 0;
    virtual QVector<DCContext::DCScoreModel> getTupleCandidates(const QVector<DCContext::IDCInputModel*> &models, IDCScoresService *scoresService) = 0;
};

#endif // IDARTSSUBTRACTSCORES_H
