#ifndef DCSCORESLAS_H
#define DCSCORESLAS_H
#include "DartsController/DCScoresSLAs/idcscoremodels.h"
#include "DartsController/DCScoresSLAs/idcupdateplayerscores.h"
#include "DartsController/DCScoresSLAs/idcgetscorecand.h"
#include "DartsController/DCScoresSLAs/idcscorebuilder.h"
#include "DartsController/DCScoresSLAs/idccalcscore.h"
#include "DartsController/DCScoresSLAs/idcupdatescoremodels.h"
class DCScoreSLAs
{
public:
    IDCScoreModels *scoreModels() const;
    void setScoresModels(IDCScoreModels *service);
    IDCUpdatePlayerScores *updatePlayerScores() const;
    void setCreateCandidateScores(IDCUpdatePlayerScores *service);
    IDCGetScoreCand *calcRemainingScoreCand() const;
    void setGetTotalScoreService(IDCGetScoreCand *service);
    IDCScoreBuilder *scoresBuilder() const;
    void setScoreBuilder(IDCScoreBuilder *service);
    IDCCalcScore *scoreCalculator() const;
    void setGetScoreFromInput(IDCCalcScore *service);
    IDCUpdateScoreModels *updateScores() const;
    void setUpdateScoresService(IDCUpdateScoreModels *service);
private:
    IDCScoreModels *_scoresModels;
    IDCScoreBuilder *_createScoreModels;
    IDCUpdatePlayerScores *_createCandidateTuples;
    IDCGetScoreCand *_calculateCandidateScore;
    IDCCalcScore *_calculateScore;
    IDCUpdateScoreModels *_replaceTuples;
};
#endif // DSCSCORESERVICESPROVIDER_H
