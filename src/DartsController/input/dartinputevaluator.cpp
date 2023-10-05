#include "dartinputevaluator.h"

DartInputEvaluator::DartInputEvaluator(IDartsScores* scores) : _scores(scores)
{}

bool DartInputEvaluator::isValid(const DartsInput& input)
{
        if(input.point() > MaxPoint || input.point() < 1)
                return false;
        return AllowedMods.contains(input.mod());
}

bool DartInputEvaluator::isWithinBounds(const DartsInput& input)
{
        auto scoreValue = inputScore(input);
        auto playerScore = _scores->score().playerScore();
        auto remainingScore = playerScore - scoreValue;
        return remainingScore >= 0;
}

int DartInputEvaluator::inputScore(const DartsInput& input) const
{
        auto multiplier = modMultiplier(input.mod());
        return  input.point()*multiplier;
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
