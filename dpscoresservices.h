#ifndef DPSCORESSERVICES_H
#define DPSCORESSERVICES_H

#include "idcscoresservice.h"
#include "idcgetplayerscore.h"
#include "idpccalcscorecandidate.h"

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
    IDPCCalcScoreCandidate *subTractScore() const
    {
        return _getScoreCandidate;
    }
    void setSubTractScore(IDPCCalcScoreCandidate *newSubTractScore)
    {
        _getScoreCandidate = newSubTractScore;
    }
private:
    IDCScoresService *_scoresService;
    IDCGetPlayerScore *_getPlayerScore;
    IDPCCalcScoreCandidate *_getScoreCandidate;
};








#endif // DPSCORESSERVICES_H
