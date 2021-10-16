#ifndef IDCCREATECANDIDATEMODELS_H
#define IDCCREATECANDIDATEMODELS_H

#include "DartsController/DCScoresSLAs/idcscoresservice.h"
#include "DartsController/DCInputSLAs/idcinput.h"
#include "DartsController/DCScoresServices/dcscoremodel.h"

class IDCCreateCandidateModels
{
public:
    virtual DCContext::DCScoreModel getCandidate(const IDCInput *model, IDCScoresService *scoresService) = 0;
    virtual QVector<DCContext::DCScoreModel> getScoreCandidates(const QVector<IDCInput*> &models, IDCScoresService *scoresService) = 0;
};

#endif // IDARTSSUBTRACTSCORES_H
