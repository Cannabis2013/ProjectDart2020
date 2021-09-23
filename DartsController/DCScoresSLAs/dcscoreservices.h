#ifndef DCSCORESERVICES_H
#define DCSCORESERVICES_H

#include "DartsController/DCScoresSLAs/idcscoresservice.h"
#include "DartsController/DCScoresSLAs/idccreatecandidatemodels.h"
#include "DartsController/DCScoresSLAs/idcaddscore.h"
#include "DartsController/DCScoresSLAs/idcgetscorecand.h"
#include "DartsController/DCScoresSLAs/idccreatescoretuples.h"
#include "DartsController/DCScoresSLAs/idcgetscore.h"
#include "DartsController/DCScoresSLAs/idcupdatescoremodels.h"
#include "DartsController/DCScoresSLAs/idcsubtractscore.h"
#include "DartsController/DCScoresSLAs/idcresetscorescoremodels.h"

class DCScoreServices
{
public:
    IDCScoresService *scoresService() const;
    void setScoresService(IDCScoresService *newScoresService);
    IDCCreateCandidateModels *createCandidatesTuple() const;
    void setCreateCandidateTuples(IDCCreateCandidateModels *newSubtractService);
    IDCAddScore *addScoreService() const;
    void setAddScoreService(IDCAddScore *newAddScoreService);
    IDCGetScoreCand *getTotalScore() const;
    void setGetTotalScoreService(IDCGetScoreCand *newCandidateService);
    IDCCreateScoreTuples *createScoreTuples() const;
    void setCreateScoreModelsService(IDCCreateScoreTuples *newCreateScoreTuples);
    IDCGetScore *getScoreFromInput() const;
    void setGetScoreFromInput(IDCGetScore *newCalculateScore);
    IDCUpdateScoreModels *updateScoreModels() const;
    void setUpdateScoreModels(IDCUpdateScoreModels *newReplaceTuples);
    IDCSubtractScore *subtractScore() const;
    void setSubtractScore(IDCSubtractScore *newSubtractScore);
    IDCResetScoreScoreModels *resetScoreModels() const;
    void setResetScoreModels(IDCResetScoreScoreModels *newResetScoreModels);
private:
    IDCScoresService *_scoresService;
    IDCCreateScoreTuples *_createScoreTuples;
    IDCCreateCandidateModels *_createCandidateTuples;
    IDCAddScore *_addScoreService;
    IDCGetScoreCand *_calculateCandidateScore;
    IDCGetScore *_calculateScore;
    IDCUpdateScoreModels *_replaceTuples;
    IDCSubtractScore *_subtractScore;
    IDCResetScoreScoreModels *_resetScoreModels;
};
#endif // DSCSCORESERVICESPROVIDER_H
