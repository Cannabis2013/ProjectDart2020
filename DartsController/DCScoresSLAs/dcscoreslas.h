#ifndef DCSCORESLAS_H
#define DCSCORESLAS_H
#include "DartsController/DCScoresSLAs/idcscoremodels.h"
#include "DartsController/DCScoresSLAs/idcupdateplayerscores.h"
#include "DartsController/DCScoresSLAs/idcscorebuilder.h"
#include "DartsController/DCScoresSLAs/idccalcscore.h"
class DCScoreSLAs
{
public:
    IDCScoreModels *scoreModels() const
    {
        return _scoresModels;
    }
    void setScoresModels(IDCScoreModels *service)
    {
        _scoresModels = service;
    }
    IDCUpdatePlayerScores *updatePlayerScores() const
    {
        return _createCandidateTuples;
    }
    void setCreateCandidateScores(IDCUpdatePlayerScores *service)
    {
        _createCandidateTuples = service;
    }
    IDCScoreBuilder *scoresBuilder() const
    {
        return _createScoreModels;
    }
    void setScoreBuilder(IDCScoreBuilder *service)
    {
        _createScoreModels = service;
    }
    IDCCalcScore *scoreCalculator() const
    {
        return _calculateScore;
    }
    void setGetScoreFromInput(IDCCalcScore *service)
    {
        _calculateScore = service;
    }
private:
    IDCScoreModels *_scoresModels;
    IDCScoreBuilder *_createScoreModels;
    IDCUpdatePlayerScores *_createCandidateTuples;
    IDCCalcScore *_calculateScore;
};
#endif // DSCSCORESERVICESPROVIDER_H
