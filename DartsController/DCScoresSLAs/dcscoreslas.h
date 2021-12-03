#ifndef DCSCORESLAS_H
#define DCSCORESLAS_H
#include "DartsController/DCScoresSLAs/abstractdcscoresctx.h"
#include "DartsController/DCScoresSLAs/idcupdateplayerscores.h"
#include "DartsController/DCScoresSLAs/idcscorebuilder.h"
#include "DartsController/DCScoresSLAs/idccalcscore.h"
class DCScoreSLAs
{
public:
    AbstractDCScoresCtx *scoresContext() const
    {
        return _scoresModels;
    }
    void setScoresModels(AbstractDCScoresCtx *service)
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
    IDCCalcScore *scoreCalc() const
    {
        return _calculateScore;
    }
    void setGetScoreFromInput(IDCCalcScore *service)
    {
        _calculateScore = service;
    }
private:
    AbstractDCScoresCtx *_scoresModels;
    IDCScoreBuilder *_createScoreModels;
    IDCUpdatePlayerScores *_createCandidateTuples;
    IDCCalcScore *_calculateScore;
};
#endif // DSCSCORESERVICESPROVIDER_H
