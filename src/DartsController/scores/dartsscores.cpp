#include "dartsscores.h"
#include "src/DartsController/scores/scorescalculator.h"

#define INITIAL_SCORE 501

void DartsScores::init()
{
        _scores.clear();
        for (const auto& name : _players->names())
                _scores << Score(name, INITIAL_SCORE);
}

void DartsScores::initFromFile()
{
        _scores = _scoresIO->fromFile();
}

void DartsScores::reset()
{
        for (const auto& name : _players->names())
                _scores << Score(name, INITIAL_SCORE);
}

int DartsScores::initialScore() const
{
        return INITIAL_SCORE;
}

DartsPlayerScores DartsScores::update()
{
        auto throwIndex = _indexes->index().throwIndex();
        _scores.clear();
        ScoresCalculator calculator;
        for (const auto& name : _players->names()) {
                auto inputs = _inputs->inputs(name, throwIndex);
                auto score = calculator.calculate(name, inputs, INITIAL_SCORE);
                _scores.append(score);
        }
        return DartsPlayerScores(_scores);
}

DartsPlayerScore DartsScores::score()
{
        auto playerIndex = _indexes->index().playerIndex();
        auto internal = _scores.at(playerIndex);
        return DartsPlayerScore(internal);
}

DartsPlayerScore DartsScores::score(const QString& name)
{
        return _scores.at(_players->indexOf(name));
}

bool DartsScores::saveState()
{
        return _scoresIO->toFile(_scores);
}
