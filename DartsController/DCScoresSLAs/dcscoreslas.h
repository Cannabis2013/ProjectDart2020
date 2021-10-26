#ifndef DCSCORESLAS_H
#define DCSCORESLAS_H
#include "DartsController/DCScoresSLAs/idcscoremodels.h"
#include "DartsController/DCScoresSLAs/idcupdateinputdetails.h"
#include "DartsController/DCScoresSLAs/idcgetscorecand.h"
#include "DartsController/DCScoresSLAs/idcscorebuilder.h"
#include "DartsController/DCScoresSLAs/idcgetscore.h"
#include "DartsController/DCScoresSLAs/idcupdatescoremodels.h"
class DCScoreSLAs
{
public:
    IDCScoreModels *scoreModels() const;
    void setScoresModels(IDCScoreModels *service);
    IDCUpdateInputDetails *updatePlayerScores() const;
    void setCreateCandidateScores(IDCUpdateInputDetails *service);
    IDCGetScoreCand *calcRemainingScoreCand() const;
    void setGetTotalScoreService(IDCGetScoreCand *service);
    IDCScoreBuilder *scoresBuilder() const;
    void setScoreBuilder(IDCScoreBuilder *service);
    IDCGetScore *scoreCalculator() const;
    void setGetScoreFromInput(IDCGetScore *service);
    IDCUpdateScoreModels *updateScores() const;
    void setUpdateScoresService(IDCUpdateScoreModels *service);
private:
    IDCScoreModels *_scoresModels;
    IDCScoreBuilder *_createScoreModels;
    IDCUpdateInputDetails *_createCandidateTuples;
    IDCGetScoreCand *_calculateCandidateScore;
    IDCGetScore *_calculateScore;
    IDCUpdateScoreModels *_replaceTuples;
};
#endif // DSCSCORESERVICESPROVIDER_H
