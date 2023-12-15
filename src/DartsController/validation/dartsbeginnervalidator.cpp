#include "dartsbeginnervalidator.h"

void DartsBeginnerValidator::init() { }

bool DartsBeginnerValidator::evaluateInput(const QString& mod, const int& point)
{
        return isValid(mod, point);
}

void DartsBeginnerValidator::evaluateScoreCondition()
{
        auto scores = _scores->scores().playerScores();
        for (const auto& score : std::as_const(scores)) {
                if (score.score() <= 0) {
                        _status->winnerFound();
                        auto winner = &_players->player();
                        winner->setWinner(true);
                }
        }
}

bool DartsBeginnerValidator::isValid(const QString& mod, const int& point) const
{
        if (point > MaxPoint || point < 0)
                return false;
        return AllowedMods.contains(mod);
}
