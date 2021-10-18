#ifndef DCSCORESLAS_H
#define DCSCORESLAS_H

#include "DartsController/DCScoresSLAs/idcscoresservice.h"
#include "DartsController/DCScoresSLAs/idccreatecandidatemodels.h"
#include "DartsController/DCScoresSLAs/idcaddscore.h"
#include "DartsController/DCScoresSLAs/idcgetscorecand.h"
#include "DartsController/DCScoresSLAs/idcscorebuilder.h"
#include "DartsController/DCScoresSLAs/idcgetscore.h"
#include "DartsController/DCScoresSLAs/idcupdatescoremodels.h"
#include "DartsController/DCScoresSLAs/idcsubtractscore.h"
#include "DartsController/DCScoresSLAs/idcresetscorescoremodels.h"

class DCScoreSLAs
{
public:
    IDCScoresService *scoresService() const;
    void setScoresService(IDCScoresService *service);
    IDCCreateCandidateModels *createCandidatesScore() const;
    void setCreateCandidateTuples(IDCCreateCandidateModels *service);
    IDCAddScore *addScoreService() const;
    void setAddScoreService(IDCAddScore *service);
    IDCGetScoreCand *getTotalScore() const;
    void setGetTotalScoreService(IDCGetScoreCand *service);
    IDCScoreBuilder *scoreBuilder() const;
    void setScoreBuilder(IDCScoreBuilder *service);
    IDCGetScore *getScoreFromInput() const;
    void setGetScoreFromInput(IDCGetScore *service);
    IDCUpdateScoreModels *updateScoreModels() const;
    void setUpdateScoreModels(IDCUpdateScoreModels *service);
    IDCSubtractScore *subtractScore() const;
    void setSubtractScore(IDCSubtractScore *service);
    IDCResetScoreScoreModels *resetScoreModels() const;
    void setResetScoreModels(IDCResetScoreScoreModels *service);
private:
    IDCScoresService *_scoresService;
    IDCScoreBuilder *_createScoreTuples;
    IDCCreateCandidateModels *_createCandidateTuples;
    IDCAddScore *_addScoreService;
    IDCGetScoreCand *_calculateCandidateScore;
    IDCGetScore *_calculateScore;
    IDCUpdateScoreModels *_replaceTuples;
    IDCSubtractScore *_subtractScore;
    IDCResetScoreScoreModels *_resetScoreModels;
};
#endif // DSCSCORESERVICESPROVIDER_H
