#include "dartsstatistics.h"

DartsStatistics::DartsStatistics(IDartsInputs* inputs, IDartsPlayers* players, IDartsScores* scores)
    : _inputs(inputs)
    , _players(players)
    , _scores(scores)
{}

double DartsStatistics::average()
{
        auto score = _scores->score();
        auto currentPlayer = score.playerName();
        auto inputsCount = _inputs->inputs(currentPlayer).count();
        if (inputsCount <= 0)
                return 0;
        auto playerPoints = 501 - score.playerScore();
        return playerPoints / inputsCount;
}

int DartsStatistics::lowest()
{
        auto currentPlayer = _players->name();
        auto inputs = _inputs->inputs(currentPlayer);
        if (inputs.count() <= 0)
                return 0;
        auto lowest = 60;
        for (const auto &input : inputs) {
                auto score = scoreValue(input.mod(),input.point());
                lowest = score < lowest ? score : lowest;
        }
        return lowest;
}

int DartsStatistics::highest()
{
        auto currentPlayer = _players->name();
        auto inputs = _inputs->inputs(currentPlayer);
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
