#include "dcscoreslas.h"

IDCScoreModels *DCScoreSLAs::scoreModels() const
{
    return _scoresModels;
}

void DCScoreSLAs::setScoresModels(IDCScoreModels *service)
{
    _scoresModels = service;
}

IDCUpdatePlayerScores *DCScoreSLAs::updatePlayerScores() const
{
    return _createCandidateTuples;
}

void DCScoreSLAs::setCreateCandidateScores(IDCUpdatePlayerScores *service)
{
    _createCandidateTuples = service;
}

IDCGetScoreCand *DCScoreSLAs::calcRemainingScoreCand() const
{
    return _calculateCandidateScore;
}

void DCScoreSLAs::setGetTotalScoreService(IDCGetScoreCand *service)
{
    _calculateCandidateScore = service;
}

IDCScoreBuilder *DCScoreSLAs::scoresBuilder() const
{
    return _createScoreModels;
}

void DCScoreSLAs::setScoreBuilder(IDCScoreBuilder *service)
{
    _createScoreModels = service;
}

IDCCalcScore *DCScoreSLAs::scoreCalculator() const
{
    return _calculateScore;
}

void DCScoreSLAs::setGetScoreFromInput(IDCCalcScore *service)
{
    _calculateScore = service;
}

IDCUpdateScoreModels *DCScoreSLAs::updateScores() const
{
    return _replaceTuples;
}

void DCScoreSLAs::setUpdateScoresService(IDCUpdateScoreModels *service)
{
    _replaceTuples = service;
}

