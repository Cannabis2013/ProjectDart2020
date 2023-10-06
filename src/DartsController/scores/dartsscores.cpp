#include "dartsscores.h"
#include "src/DartsController/scores/scoresio.h"

DartsScores::DartsScores(IDartsIndexes* indexes, IDartPlayers* players, IDartInputs* inputs):
        _indexes(indexes),_players(players), _inputs(inputs){
        _scoresIO = new ScoresIO("playerScores.dat");
        _calculator = new DartsScoresCalculator(indexes,players,inputs);
}

void DartsScores::init()
{
        auto names = _players->names();
        for (const auto &name : names)
                _scores << DartsInternalScore(name);
}

void DartsScores::reset()
{
        auto names = _players->names();
        for (const auto &name : names)
                _scores << DartsInternalScore(name);
}

DartsPlayerScore DartsScores::update(DartsInput input)
{
        auto playerIndex = _indexes->index().playerIndex();
        auto internalScore = _calculator->calculatedScore(input,_scores[playerIndex]);
        _scores.replace(playerIndex,internalScore);
        _scoresIO->toFile(_scores);
        return DartsPlayerScore(internalScore);
}

DartsPlayerScores DartsScores::update()
{
        _scores =_calculator->calculatedScores();
        _scoresIO->toFile(_scores);
        return DartsPlayerScores(_scores);
}

DartsPlayerScore DartsScores::score()
{
        auto playerIndex = _indexes->index().playerIndex();
        auto internal = _scores.at(playerIndex);
        return DartsPlayerScore(internal);
}
