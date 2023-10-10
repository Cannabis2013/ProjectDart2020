#include "dartsinputevaluator.h"

DartsInputEvaluator::DartsInputEvaluator(IDartsScores* scores) : _scores(scores)
{}

bool DartsInputEvaluator::isValid(const QString& mod, const int& point)
{
        if(point > MaxPoint || point < 0)
                return false;
        return AllowedMods.contains(mod);
}

bool DartsInputEvaluator::isWithinBounds(const QString& mod, const int& point)
{
        auto scoreValue = inputScore(mod,point);
        auto playerScore = _scores->score().playerScore();
        auto remainingScore = playerScore - scoreValue;
        if (remainingScore > 1)
                return true;
        else if (remainingScore == 0 && validEndThrow(mod, point))
                return true;
        else
                return false;
}

int DartsInputEvaluator::inputScore(const QString& mod, const int& point) const
{
        auto multiplier = modMultiplier(mod);
        return  point*multiplier;
}

int DartsInputEvaluator::modMultiplier(QString mod) const
{
        if(mod == "S")
                return 1;
        else if(mod == "D")
                return 2;
        else
                return 3;
}

bool DartsInputEvaluator::validEndThrow(const QString& mod, const int& point) const
{
        return mod == "D" || point == 50;
}
