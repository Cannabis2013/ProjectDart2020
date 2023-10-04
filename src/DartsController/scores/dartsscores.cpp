#include "dartsscores.h"

DartsScores::DartsScores(IDartIndexes* indexes, IDartPlayers* players, IDartInputs* inputs):
        _indexes(indexes),_players(players), _inputs(inputs){}

void DartsScores::init(const int& playersCount)
{
        _scores = QVector<int>(playersCount,0);
}

void DartsScores::reset()
{
        _scores = QVector<int>();
}

DartScore DartsScores::update(DartInput input)
{
        auto playerIndex = _indexes->index().playerIndex();
        auto playerName = _players->name(playerIndex);
        auto scoreValue = inputScore(input);
        auto currentScore = _scores.at(playerIndex);
        auto newScore = currentScore - scoreValue;
        _scores.replace(playerIndex,newScore);
        return DartScore(playerName,newScore);
}

DartScore DartsScores::update()
{
        auto playerIndex = _indexes->index().playerIndex();
        auto turnIndex =_indexes->turnIndex();
        auto playerName = _players->name(playerIndex);
        auto playerInputs = _inputs->inputs(playerName,turnIndex);
        auto score = totalScore(playerInputs);
        _scores.replace(playerIndex,score);
        return DartScore(playerName,score);
}

int DartsScores::score()
{
        auto playerIndex = _indexes->index().playerIndex();
        return _scores.at(playerIndex);
}

QVector<int> DartsScores::scores()
{
        return _scores;
}

int DartsScores::totalScore(const QList<DartInput>& inputs)
{
        int sum = 0;
        for (auto& input : qAsConst(inputs))
                sum += inputScore(input);
        return sum;
}

int DartsScores::inputScore(const DartInput& input) const
{
        auto multiplier = modMultiplier(input.mod());
        return  input.point()*multiplier;
}

int DartsScores::modMultiplier(QString mod) const
{
        if(mod == "S")
                return 1;
        else if(mod == "D")
                return 2;
        else
                return 3;
}
