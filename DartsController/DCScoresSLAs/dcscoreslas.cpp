#include "dcscoreslas.h"

IDCScoresService *DCScoreSLAs::scoreController() const
{
    return _scoresService;
}

void DCScoreSLAs::setScoresService(IDCScoresService *service)
{
    _scoresService = service;
}

IDCUpdateInputDetails *DCScoreSLAs::createCandidatesScore() const
{
    return _createCandidateTuples;
}

void DCScoreSLAs::setCreateCandidateScores(IDCUpdateInputDetails *service)
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

IDCScoreBuilder *DCScoreSLAs::scoreBuilder() const
{
    return _createScoreTuples;
}

void DCScoreSLAs::setScoreBuilder(IDCScoreBuilder *service)
{
    _createScoreTuples = service;
}

IDCGetScore *DCScoreSLAs::getScoreFromInput() const
{
    return _calculateScore;
}

void DCScoreSLAs::setGetScoreFromInput(IDCGetScore *service)
{
    _calculateScore = service;
}

IDCUpdateScoreModels *DCScoreSLAs::updateScoreModels() const
{
    return _replaceTuples;
}

void DCScoreSLAs::setUpdateScoreModels(IDCUpdateScoreModels *service)
{
    _replaceTuples = service;
}

IDCResetScoreScoreModels *DCScoreSLAs::resetScoreModels() const
{
    return _resetScoreModels;
}

void DCScoreSLAs::setResetScoreModels(IDCResetScoreScoreModels *service)
{
    _resetScoreModels = service;
}
