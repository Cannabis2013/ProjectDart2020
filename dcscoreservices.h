#ifndef DCSCORESERVICES_H
#define DCSCORESERVICES_H

#include "idcscoresservice.h"
#include "idartssubtractscores.h"
#include "idcaddscore.h"
#include "idcgetscorecand.h"
#include "idccreatescoretuples.h"
#include <idcgetscore.h>
#include <idcupdatescoremodels.h>
#include "idcsubtractscore.h"
#include "idcresetscorescoremodels.h"

class DCScoreServices
{
public:
    IDCScoresService *scoresService() const;
    void setScoresService(IDCScoresService *newScoresService);
    IDCCreateCandidateTuples *createCandidatesTuple() const;
    void setCreateCandidateTuples(IDCCreateCandidateTuples *newSubtractService);
    IDCAddScore *addScoreService() const;
    void setAddScoreService(IDCAddScore *newAddScoreService);

    IDCGetScoreCand *getTotalScore() const;
    void setGetTotalScoreService(IDCGetScoreCand *newCandidateService);
    IDCCreateScoreTuples *createScoreTuples() const;
    void setCreateScoreTuples(IDCCreateScoreTuples *newCreateScoreTuples);
    IDCgetScore *getScoreFromInput() const;
    void setGetScoreFromInput(IDCgetScore *newCalculateScore);
    IDCUpdateScoreModels *updateScoreTuples() const;
    void setReplaceScoreModels(IDCUpdateScoreModels *newReplaceTuples);

    IDCSubtractScore *subtractScore() const;
    void setSubtractScore(IDCSubtractScore *newSubtractScore);
    IDCResetScoreScoreModels *resetScoreModels() const;
    void setResetScoreModels(IDCResetScoreScoreModels *newResetScoreModels);
private:
    IDCScoresService *_scoresService;
    IDCCreateScoreTuples *_createScoreTuples;
    IDCCreateCandidateTuples *_createCandidateTuples;
    IDCAddScore *_addScoreService;
    IDCGetScoreCand *_calculateCandidateScore;
    IDCgetScore *_calculateScore;
    IDCUpdateScoreModels *_replaceTuples;
    IDCSubtractScore *_subtractScore;
    IDCResetScoreScoreModels *_resetScoreModels;
};
#endif // DSCSCORESERVICESPROVIDER_H
