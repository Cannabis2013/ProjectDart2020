#include "dartsoverthrowevaluator.h"

bool DartsOverthrowEvaluator::evaluatorInput(const QString& mod, const int& point)
{
        return isValid(mod, point);
}

void DartsOverthrowEvaluator::evaluateScoreCondition()
{
        for (const auto& score : _scores->scores().playerScores()) {
                if (score.score() <= 0) {
                        _status->winnerFound();
                        _players->declareAsWinner(score.name());
                }
        }
}

bool DartsOverthrowEvaluator::isValid(const QString& mod, const int& point) const
{
        if (point > MaxPoint || point < 0)
                return false;
        return AllowedMods.contains(mod);
}
