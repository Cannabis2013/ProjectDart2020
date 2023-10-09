#include "dartsscores.h"

#define INITIAL_SCORE 501

DartsScores::DartsScores(IDartsIndexes* indexes, IDartsPlayers* players, IDartsInputs* inputs, IDartsStatus* status)
    : _indexes(indexes)
    , _players(players)
    , _status(status)
{
        _scoresIO = new ScoresIO("playerScores.dat");
        _calculator = new ScoresCalculator(inputs);
}

void DartsScores::init()
{
        _scores.clear();
        auto names = _players->names();
        for (const auto& name : qAsConst(names))
                _scores << Score(name, INITIAL_SCORE);
}

void DartsScores::initFromFile()
{
        _scores = _scoresIO->fromFile();
}

void DartsScores::reset()
{
        auto names = _players->names();
        for (const auto& name : qAsConst(names))
                _scores << Score(name, INITIAL_SCORE);
}

DartsPlayerScore DartsScores::update(const Input& input)
{
        if(input.point() == 0)
                return score();
        auto index = _indexes->index().playerIndex();
        auto name = _players->name();
        auto score = _calculator->calculatedScore(input,_scores.at(index),name);
        _scores.replace(index,score);
        if (score.score() == 0)
                _status->updateStatus(IDartsStatus::Winner);
        return DartsPlayerScore(score);
}

int DartsScores::initialScore() const
{
        return INITIAL_SCORE;
}

DartsPlayerScores DartsScores::update()
{
        _scores = _calculator->calculatedScores(_players->names(), INITIAL_SCORE);
        for (const auto& score : qAsConst(_scores)) {
                if (score.score() == 0)
                        _status->updateStatus(IDartsStatus::Winner);
        }
        return DartsPlayerScores(_scores);
}

DartsPlayerScore DartsScores::score()
{
        auto playerIndex = _indexes->index().playerIndex();
        auto internal = _scores.at(playerIndex);
        return DartsPlayerScore(internal);
}

bool DartsScores::saveState()
{
        return _scoresIO->toFile(_scores);
}

