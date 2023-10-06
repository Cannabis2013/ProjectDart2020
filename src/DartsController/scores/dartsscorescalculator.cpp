#include "dartsscorescalculator.h"

DartsScoresCalculator::DartsScoresCalculator(IDartsIndexes* indexes, IDartPlayers* players, IDartInputs* inputs)
        : _indexes(indexes), _players(players), _inputs(inputs) {}

QList<DartsInternalScore> DartsScoresCalculator::calculatedScores()
{
        QList<DartsInternalScore> scores;
        auto turnIndex = _indexes->turnIndex();
        auto names = _players->names();
        for (const auto &name : qAsConst(names)) {
                int score = 501;
                auto inputs = _inputs->inputs(name,turnIndex);
                for (auto& input : qAsConst(inputs))
                        score -= inputScore(input);
                scores.append(DartsInternalScore(name,score));
        }
        return scores;
}

DartsInternalScore DartsScoresCalculator::calculatedScore(const DartsInput& input, DartsInternalScore& current)
{
        auto scoreValue = inputScore(input);
        auto newScore = current.score() - scoreValue;
        auto playerIndex = _indexes->index().playerIndex();
        auto playerName = _players->name(playerIndex);
        return DartsInternalScore(playerName,newScore);
}

int DartsScoresCalculator::inputScore(const DartsInput& input) const
{
        auto multiplier = modMultiplier(input.mod());
        return  input.point()*multiplier;
}

int DartsScoresCalculator::modMultiplier(QString mod) const
{
        if(mod == "S")
                return 1;
        else if(mod == "D")
                return 2;
        else
                return 3;
}
