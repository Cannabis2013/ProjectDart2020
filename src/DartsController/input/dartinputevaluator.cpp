#include "dartinputevaluator.h"

DartInputEvaluator::DartInputEvaluator(IDartsScores* scores) : _scores(scores)
{}

bool DartInputEvaluator::isValid(const QString& mod, const int& point)
{
        if(point > MaxPoint || point < 0)
                return false;
        return AllowedMods.contains(mod);
}

bool DartInputEvaluator::isWithinBounds(const QString& mod, const int& point)
{
        auto scoreValue = inputScore(mod,point);
        auto playerScore = _scores->score().playerScore();
        auto remainingScore = playerScore - scoreValue;
        return remainingScore >= 0;
}

int DartInputEvaluator::inputScore(const QString& mod, const int& point) const
{
        auto multiplier = modMultiplier(mod);
        return  point*multiplier;
}

int DartInputEvaluator::modMultiplier(QString mod) const
{
        if(mod == "S")
                return 1;
        else if(mod == "D")
                return 2;
        else
                return 3;
}
