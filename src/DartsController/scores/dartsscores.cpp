#include "dartsscores.h"

#define INITIAL_SCORE 170

DartsScores::DartsScores(IDartsIndexes* indexes, IDartsPlayers* players, IDartsInputs* inputs)
    : _indexes(indexes)
    , _players(players)
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

void DartsScores::reset()
{
        auto names = _players->names();
        for (const auto &name : names)
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
        return DartsPlayerScore(score);
}

DartsPlayerScores DartsScores::update()
{
        auto turnIndex = _indexes->turnIndex();
        _scores = _calculator->calculatedScores(turnIndex,_players->names());
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

