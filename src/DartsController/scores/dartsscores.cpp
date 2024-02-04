#include "dartsscores.h"

#include "src/DartsController/indexes/idartsindexes.h"
#include "src/DartsController/input/idartsinputs.h"
#include "src/DartsController/players/idartsplayers.h"
#include "src/DartsController/scores/DartsPlayerScores.h"
#include "src/DartsController/scores/dartsPlayerScore.h"
#include "src/DartsController/scores/iscorescalculator.h"
#include "src/DartsController/scores/scoresio.h"

DartsScores::DartsScores(IDartsIndexes* indexes, IDartsPlayers* players, IDartsInputs* inputs, IScoresCalculator* calculator)
    : _indexes(indexes)
    , _players(players)
    , _inputs(inputs)
    , _calculator(calculator)
{
        _scoresIO = new ScoresIO("playerScores.dat");
}

void DartsScores::init(const int& initialScore)
{
        _initialScore = initialScore;
        _scores.clear();
        for (const auto& name : _players->names())
                _scores << Score(name, _initialScore);
}

void DartsScores::initFromFile()
{
        auto values = _scoresIO->fromFile();
        _scores = values.scores();
        _initialScore = values.initialScore();
}

void DartsScores::reset()
{
        _scores.clear();
        for (const auto& name : _players->names())
                _scores << Score(name, _initialScore);
}

void DartsScores::update()
{
        auto throwIndex = _indexes->index().throwIndex();
        _scores.clear();
        for (const auto& name : _players->names()) {
                auto inputs = _inputs->inputs(name, throwIndex);
                auto score = _calculator->calculate(name, inputs, _initialScore);
                _scores.append(score);
        }
}

DartsPlayerScore DartsScores::score(){
        auto playerIndex = _indexes->index().playerIndex();
        auto internal = _scores.at(playerIndex);
        return DartsPlayerScore(internal);
}

DartsPlayerScore DartsScores::score(const QString& name){
        for (const auto& score : _scores) {
                if (score.name() == name)
                        return score;
        }
        return DartsPlayerScore();
}

DartsPlayerScores DartsScores::scores()
{
        return DartsPlayerScores(_scores);
}

bool DartsScores::saveState()
{
        return _scoresIO->toFile(_scores, _initialScore);
}
