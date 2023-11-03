#include "dartsoverthrowvalidator.h"

bool DartsOverthrowValidator::evaluatorInput(const QString& mod, const int& point)
{
        return isValid(mod, point);
}

void DartsOverthrowValidator::evaluateScoreCondition()
{
        auto scores = _scores->scores().playerScores();
        for (const auto& score : std::as_const(scores)) {
                if (score.score() <= 0) {
                        _status->winnerFound();
                        _players->declareAsWinner(score.name());
                }
        }
}

bool DartsOverthrowValidator::isValid(const QString& mod, const int& point) const
{
        if (point > MaxPoint || point < 0)
                return false;
        return AllowedMods.contains(mod);
}
