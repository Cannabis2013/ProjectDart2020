#include "dartsinputevaluator.h"

DartsInputEvaluator::DartsInputEvaluator(IDartsScores** scores) : _scores(scores)
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
        auto playerScore = scores()->score().playerScore();
        auto remainingScore = playerScore - scoreValue;
        return remainingScore >= 0;
}

IDartsScores* DartsInputEvaluator::scores() const
{
        return *_scores;
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
