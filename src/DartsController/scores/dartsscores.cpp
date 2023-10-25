#include "dartsscores.h"
#include "src/DartsController/scores/scorescalculator.h"

#define INITAL_SCORE 501

DartsScores::DartsScores(IDartsIndexes* indexes, IDartsPlayers* players, IDartsInputs* inputs)
    : _indexes(indexes)
    , _players(players)
    , _inputs(inputs)
{
        _scoresIO = new ScoresIO("playerScores.dat");
}

void DartsScores::init()
{
        _scores.clear();
        for (const auto& name : _players->names())
                _scores << Score(name, INITAL_SCORE);
}

int DartsScores::initialScore() const { return INITAL_SCORE; }

DartsPlayerScores DartsScores::update()
{
        auto throwIndex = _indexes->index().throwIndex();
        _scores.clear();
        ScoresCalculator calculator;
        for (const auto& name : _players->names()) {
                auto inputs = _inputs->inputs(name, throwIndex);
                auto score = calculator.calculate(name, inputs, INITAL_SCORE);
                _scores.append(score);
        }
        return DartsPlayerScores(_scores);
}

DartsPlayerScore DartsScores::score(){
        auto playerIndex = _indexes->index().playerIndex();
        auto internal = _scores.at(playerIndex);
        return DartsPlayerScore(internal);
}

DartsPlayerScore DartsScores::score(const QString& name){
        auto index = _players->indexOf(name);
        return _scores.at(index);
}
