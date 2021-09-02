#ifndef DSCSCORESERVICES_H
#define DSCSCORESERVICES_H

#include "idcscoresservice.h"
#include "idartssubtractscores.h"
#include "idartsaddscore.h"
#include "idsccalccandidate.h"
#include "idccreatescoretuples.h"
#include <idccalculatescore.h>
#include <idcreplacetuples.h>

class DSCScoreServices
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
    IDartsAddScore *addScoreService() const
    {
        return _addScoreService;
    }
    void setAddScoreService(IDartsAddScore *newAddScoreService)
    {
        _addScoreService = newAddScoreService;
    }

    IDSCCalcCandidate *calcAccScoreCand() const
    {
        return _calculateCandidateScore;
    }
    void setCalcAccScoreCand(IDSCCalcCandidate *newCandidateService)
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

    IDCCalculateScore *calculateScore() const
    {
        return _calculateScore;
    }
    void setCalculateScore(IDCCalculateScore *newCalculateScore)
    {
        _calculateScore = newCalculateScore;
    }
    IDCReplaceTuples *replaceTuples() const
    {
        return _replaceTuples;
    }
    void setReplaceTuples(IDCReplaceTuples *newReplaceTuples)
    {
        _replaceTuples = newReplaceTuples;
    }

private:
    IDCScoresService *_scoresService;
    IDCCreateScoreTuples *_createScoreTuples;
    IDCCreateCandidateTuples *_createCandidateTuples;
    IDartsAddScore *_addScoreService;
    IDSCCalcCandidate *_calculateCandidateScore;
    IDCCalculateScore *_calculateScore;
    IDCReplaceTuples *_replaceTuples;
};
#endif // DSCSCORESERVICESPROVIDER_H
