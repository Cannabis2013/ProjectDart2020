#include "scorescalculator.h"

ScoresCalculator::ScoresCalculator(IDartsInputs* inputs)
    : _inputs(inputs)
{
}

QList<Score> ScoresCalculator::calculatedScores(const QStringList& names, const int& initialScore, const int& throwIndex)
{
        QList<Score> scores;
        for (const auto &name : qAsConst(names)) {
                auto inputs = _inputs->inputs(name, throwIndex);
                int score = initialScore;
                for (auto& input : qAsConst(inputs))
                        score -= inputScore(input.mod(),input.point());
                scores.append(Score(name,score));
        }
        return scores;
}

Score ScoresCalculator::calculatedScore(const Input &input, const Score &score, const QString &name)
{
        auto scoreValue = inputScore(input.mod(),input.point());
        auto newScore = score.score() - scoreValue;
        return Score(name,newScore);
}

int ScoresCalculator::inputScore(const QString& mod, const int& point) const
{
        auto multiplier = modMultiplier(mod);
        return  point*multiplier;
}

int ScoresCalculator::modMultiplier(QString mod) const
{
        if(mod == "S")
                return 1;
        else if(mod == "D")
                return 2;
        else
                return 3;
}
