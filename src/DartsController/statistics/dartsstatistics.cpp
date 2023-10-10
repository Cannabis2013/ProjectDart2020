#include "dartsstatistics.h"

DartsStatistics::DartsStatistics(IDartsInputs* inputs, IDartsPlayers* players, IDartsScores* scores, IDartsIndexes* indexes)
    : _inputs(inputs)
    , _players(players)
    , _scores(scores)
    , _indexes(indexes)
{}

Statistics DartsStatistics::statistics() const
{
        auto score = _scores->score();
        auto inputs = getInputs();
        auto avg = average(_scores->initialScore(), score.playerScore(), inputs.count());
        auto low = lowest(inputs);
        auto high = highest(inputs);
        return Statistics(avg, low, high);
}

QList<Input> DartsStatistics::getInputs() const
{
        auto currentPlayer = _players->name();
        auto throwIndex = _indexes->index().throwIndex();
        return _inputs->inputs(currentPlayer, throwIndex);
}

double DartsStatistics::average(int initialScore, int score, int count) const
{
        if (count <= 0)
                return 0;
        auto playerPoints = initialScore - score;
        return playerPoints / count;
}

int DartsStatistics::lowest(const QList<Input>& inputs) const
{
        if (inputs.count() <= 0)
                return 0;
        auto lowest = 60;
        for (const auto &input : inputs) {
                auto score = scoreValue(input.mod(),input.point());
                lowest = score < lowest ? score : lowest;
        }
        return lowest;
}

int DartsStatistics::highest(const QList<Input>& inputs) const
{
        auto highest = 0;
        for (const auto &input : inputs) {
                auto score = scoreValue(input.mod(),input.point());
                highest = score > highest ? score : highest;
        }
        return highest;
}

int DartsStatistics::scoreValue(const QString& mod, const int& point) const
{
        auto multiplier = modMultiplier(mod);
        return  point*multiplier;
}

int DartsStatistics::modMultiplier(QString mod) const
{
        if(mod == "S")
                return 1;
        else if(mod == "D")
                return 2;
        else
                return 3;
}
