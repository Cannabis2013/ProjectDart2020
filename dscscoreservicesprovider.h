#ifndef DSCSCORESERVICESPROVIDER_H
#define DSCSCORESERVICESPROVIDER_H

#include "idcscoresservice.h"
#include "idartssubtractscores.h"
#include "idartsaddscore.h"
#include "idsccalccandidate.h"
#include "idccreatescoretuples.h"

class DSCScoreServicesProvider
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
    IDartsSubtractScore *subtractService() const
    {
        return _subtractService;
    }
    void setSubtractService(IDartsSubtractScore *newSubtractService)
    {
        _subtractService = newSubtractService;
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

private:
    IDCScoresService *_scoresService;
    IDCCreateScoreTuples *_createScoreTuples;
    IDartsSubtractScore *_subtractService;
    IDartsAddScore *_addScoreService;
    IDSCCalcCandidate *_calculateCandidateScore;

};
#endif // DSCSCORESERVICESPROVIDER_H
