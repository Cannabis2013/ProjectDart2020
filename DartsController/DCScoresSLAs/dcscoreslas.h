#ifndef DCSCORESLAS_H
#define DCSCORESLAS_H

#include "DartsController/DCScoresSLAs/idcscoresservice.h"
#include "DartsController/DCScoresSLAs/idcupdateinputdetails.h"
#include "DartsController/DCScoresSLAs/idcgetscorecand.h"
#include "DartsController/DCScoresSLAs/idcscorebuilder.h"
#include "DartsController/DCScoresSLAs/idcgetscore.h"
#include "DartsController/DCScoresSLAs/idcupdatescoremodels.h"
#include "DartsController/DCScoresSLAs/idcresetscorescoremodels.h"

class DCScoreSLAs
{
public:
    IDCScoresService *scoreController() const;
    void setScoresService(IDCScoresService *service);
    IDCUpdateInputDetails *createCandidatesScore() const;
    void setCreateCandidateScores(IDCUpdateInputDetails *service);
    IDCGetScoreCand *calcRemainingScoreCand() const;
    void setGetTotalScoreService(IDCGetScoreCand *service);
    IDCScoreBuilder *scoreBuilder() const;
    void setScoreBuilder(IDCScoreBuilder *service);
    IDCGetScore *getScoreFromInput() const;
    void setGetScoreFromInput(IDCGetScore *service);
    IDCUpdateScoreModels *updateScoreModels() const;
    void setUpdateScoreModels(IDCUpdateScoreModels *service);
    IDCResetScoreScoreModels *resetScoreModels() const;
    void setResetScoreModels(IDCResetScoreScoreModels *service);
private:
    IDCScoresService *_scoresService;
    IDCScoreBuilder *_createScoreTuples;
    IDCUpdateInputDetails *_createCandidateTuples;
    IDCGetScoreCand *_calculateCandidateScore;
    IDCGetScore *_calculateScore;
    IDCUpdateScoreModels *_replaceTuples;
    IDCResetScoreScoreModels *_resetScoreModels;
};
#endif // DSCSCORESERVICESPROVIDER_H
