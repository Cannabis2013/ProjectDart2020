#include "dcscoreservices.h"

IDCScoresService *DCScoreServices::scoresService() const
{
    return _scoresService;
}

void DCScoreServices::setScoresService(IDCScoresService *newScoresService)
{
    _scoresService = newScoresService;
}

IDCCreateCandidateModels *DCScoreServices::createCandidatesTuple() const
{
    return _createCandidateTuples;
}

void DCScoreServices::setCreateCandidateTuples(IDCCreateCandidateModels *newSubtractService)
{
    _createCandidateTuples = newSubtractService;
}

IDCAddScore *DCScoreServices::addScoreService() const
{
    return _addScoreService;
}

void DCScoreServices::setAddScoreService(IDCAddScore *newAddScoreService)
{
    _addScoreService = newAddScoreService;
}

IDCGetScoreCand *DCScoreServices::getTotalScore() const
{
    return _calculateCandidateScore;
}

void DCScoreServices::setGetTotalScoreService(IDCGetScoreCand *newCandidateService)
{
    _calculateCandidateScore = newCandidateService;
}

IDCCreateScoreTuples *DCScoreServices::createScoreTuples() const
{
    return _createScoreTuples;
}

void DCScoreServices::setCreateScoreModelsService(IDCCreateScoreTuples *newCreateScoreTuples)
{
    _createScoreTuples = newCreateScoreTuples;
}

IDCGetScore *DCScoreServices::getScoreFromInput() const
{
    return _calculateScore;
}

void DCScoreServices::setGetScoreFromInput(IDCGetScore *newCalculateScore)
{
    _calculateScore = newCalculateScore;
}

IDCUpdateScoreModels *DCScoreServices::updateScoreModels() const
{
    return _replaceTuples;
}

void DCScoreServices::setUpdateScoreModels(IDCUpdateScoreModels *newReplaceTuples)
{
    _replaceTuples = newReplaceTuples;
}

IDCSubtractScore *DCScoreServices::subtractScore() const
{
    return _subtractScore;
}

void DCScoreServices::setSubtractScore(IDCSubtractScore *newSubtractScore)
{
    _subtractScore = newSubtractScore;
}

IDCResetScoreScoreModels *DCScoreServices::resetScoreModels() const
{
    return _resetScoreModels;
}

void DCScoreServices::setResetScoreModels(IDCResetScoreScoreModels *newResetScoreModels)
{
    _resetScoreModels = newResetScoreModels;
}
