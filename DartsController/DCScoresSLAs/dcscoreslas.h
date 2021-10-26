#ifndef DCSCORESLAS_H
#define DCSCORESLAS_H
#include "DartsController/DCScoresSLAs/idcscoremodels.h"
#include "DartsController/DCScoresSLAs/idcupdateinputdetails.h"
#include "DartsController/DCScoresSLAs/idcgetscorecand.h"
#include "DartsController/DCScoresSLAs/idcscorebuilder.h"
#include "DartsController/DCScoresSLAs/idcgetscore.h"
#include "DartsController/DCScoresSLAs/idcupdatescoremodels.h"
#include "DartsController/DCScoresSLAs/idcresetscorescoremodels.h"
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
    IDCGetScore *getScoreFromInput() const;
    void setGetScoreFromInput(IDCGetScore *service);
    IDCUpdateScoreModels *updateScores() const;
    void setUpdateScoresService(IDCUpdateScoreModels *service);
    IDCResetScoreScoreModels *resetScoreModels() const;
    void setResetScoreModels(IDCResetScoreScoreModels *service);
private:
    IDCScoreModels *_scoresModels;
    IDCScoreBuilder *_createScoreModels;
    IDCUpdateInputDetails *_createCandidateTuples;
    IDCGetScoreCand *_calculateCandidateScore;
    IDCGetScore *_calculateScore;
    IDCUpdateScoreModels *_replaceTuples;
    IDCResetScoreScoreModels *_resetScoreModels;
};
#endif // DSCSCORESERVICESPROVIDER_H
