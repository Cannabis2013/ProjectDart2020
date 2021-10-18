#include "dcscoreslas.h"

IDCScoresService *DCScoreSLAs::scoresService() const
{
    return _scoresService;
}

void DCScoreSLAs::setScoresService(IDCScoresService *service)
{
    _scoresService = service;
}

IDCCreateCandidateModels *DCScoreSLAs::createCandidatesScore() const
{
    return _createCandidateTuples;
}

void DCScoreSLAs::setCreateCandidateScores(IDCCreateCandidateModels *service)
{
    _createCandidateTuples = service;
}

IDCAddScore *DCScoreSLAs::addScoreService() const
{
    return _addScoreService;
}

void DCScoreSLAs::setAddScoreService(IDCAddScore *service)
{
    _addScoreService = service;
}

IDCGetScoreCand *DCScoreSLAs::getTotalScore() const
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

IDCSubtractScore *DCScoreSLAs::subtractScore() const
{
    return _subtractScore;
}

void DCScoreSLAs::setSubtractScore(IDCSubtractScore *service)
{
    _subtractScore = service;
}

IDCResetScoreScoreModels *DCScoreSLAs::resetScoreModels() const
{
    return _resetScoreModels;
}

void DCScoreSLAs::setResetScoreModels(IDCResetScoreScoreModels *service)
{
    _resetScoreModels = service;
}
