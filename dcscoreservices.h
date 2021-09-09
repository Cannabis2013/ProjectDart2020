#ifndef DCSCORESERVICES_H
#define DCSCORESERVICES_H

#include "idcscoresservice.h"
#include "idartssubtractscores.h"
#include "idcaddscore.h"
#include "idcgetscorecand.h"
#include "idccreatescoretuples.h"
#include <idcgetscore.h>
#include <idcupdatetuples.h>
#include "idcsubtractscore.h"

class DCScoreServices
{
public:
    IDCScoresService *scoresService() const
    {
        return _scoresService;
    }
    void setScoresService(IDCScoresService *newScoresService)
    {
        _scoresService = newScoresService;
    }
    IDCCreateCandidateTuples *createCandidatesTuple() const
    {
        return _createCandidateTuples;
    }
    void setCreateCandidateTuples(IDCCreateCandidateTuples *newSubtractService)
    {
        _createCandidateTuples = newSubtractService;
    }
    IDCAddScore *addScoreService() const
    {
        return _addScoreService;
    }
    void setAddScoreService(IDCAddScore *newAddScoreService)
    {
        _addScoreService = newAddScoreService;
    }

    IDCGetScoreCand *getTotalScore() const
    {
        return _calculateCandidateScore;
    }
    void setGetTotalScoreService(IDCGetScoreCand *newCandidateService)
    {
        _calculateCandidateScore = newCandidateService;
    }
    IDCCreateScoreTuples *createScoreTuples() const
    {
        return _createScoreTuples;
    }
    void setCreateScoreTuples(IDCCreateScoreTuples *newCreateScoreTuples)
    {
        _createScoreTuples = newCreateScoreTuples;
    }
    IDCgetScore *getScoreFromInput() const
    {
        return _calculateScore;
    }
    void setGetScoreFromInput(IDCgetScore *newCalculateScore)
    {
        _calculateScore = newCalculateScore;
    }
    IDCUpdateTuples *updateScoreTuples() const
    {
        return _replaceTuples;
    }
    void setReplaceTuples(IDCUpdateTuples *newReplaceTuples)
    {
        _replaceTuples = newReplaceTuples;
    }

    IDCSubtractScore *subtractScore() const
    {
        return _subtractScore;
    }
    void setSubtractScore(IDCSubtractScore *newSubtractScore)
    {
        _subtractScore = newSubtractScore;
    }
private:
    IDCScoresService *_scoresService;
    IDCCreateScoreTuples *_createScoreTuples;
    IDCCreateCandidateTuples *_createCandidateTuples;
    IDCAddScore *_addScoreService;
    IDCGetScoreCand *_calculateCandidateScore;
    IDCgetScore *_calculateScore;
    IDCUpdateTuples *_replaceTuples;
    IDCSubtractScore *_subtractScore;
};
#endif // DSCSCORESERVICESPROVIDER_H
