#ifndef DPSCORESSERVICES_H
#define DPSCORESSERVICES_H

#include "DCScoresSLAs/idcscoresservice.h"
#include "idcgetplayerscore.h"
#include "idccalcscorecandidate.h"

class DPScoresServices
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
    IDCGetPlayerScore *getPlayerScore() const
    {
        return _getPlayerScore;
    }
    void setGetPlayerScore(IDCGetPlayerScore *newGetPlayerScore)
    {
        _getPlayerScore = newGetPlayerScore;
    }
    IDCCalcScoreCandidate *subTractScore() const
    {
        return _getScoreCandidate;
    }
    void setSubTractScore(IDCCalcScoreCandidate *newSubTractScore)
    {
        _getScoreCandidate = newSubTractScore;
    }
private:
    IDCScoresService *_scoresService;
    IDCGetPlayerScore *_getPlayerScore;
    IDCCalcScoreCandidate *_getScoreCandidate;
};








#endif // DPSCORESSERVICES_H
