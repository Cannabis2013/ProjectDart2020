#ifndef IDCCREATECANDIDATEMODELS_H
#define IDCCREATECANDIDATEMODELS_H

#include "DartsController/DCScoresSLAs/idcscoresservice.h"
#include "DartsController/DCScoresServices/dcscoremodel.h"

#include "DartsController/DCInputServices/dcinput.h"

class IDCCreateCandidateModels
{
public:
    virtual DCContext::DCScoreModel getCandidate(const DCInput &model, IDCScoresService *scoresService) = 0;
    virtual QVector<DCContext::DCScoreModel> getScoreCandidates(const QVector<DCInput> &models, IDCScoresService *scoresService) = 0;
};

#endif // IDARTSSUBTRACTSCORES_H
