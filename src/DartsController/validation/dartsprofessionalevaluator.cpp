#include "dartsprofessionalevaluator.h"

void DartsProfessionalEvaluator::init()
{
        allowances.clear();
        auto names = _players->names();
        for (const auto& name : names)
                allowances.append(QPair<QString, bool>(name, false));
}

bool DartsProfessionalEvaluator::evaluateInput(const QString& mod, const int& point)
{
        if (!isAllowed(mod) || !isValid(mod, point))
                return false;
        auto remaining = remainingScore(mod, point);
        if (isWithinBounds(remaining))
                return true;
        else if (remaining == 0 && (mod == "D" || point == 50))
                return true;
        return false;
}

void DartsProfessionalEvaluator::evaluateScoreCondition()
{
        auto scores = _scores->scores().playerScores();
        for (const auto& score : scores) {
                if (score.score() == 0) {
                        _status->winnerFound();
                        auto winner = &_players->player();
                        winner->setWinner(true);
                }
        }
}

bool DartsProfessionalEvaluator::isAllowed(const QString& mod)
{
        auto player = _players->player();
        for (auto& allowance : allowances) {
                if (allowance.first == player.name()) {
                        if (allowance.second)
                                return true;
                        else if (mod == "D") {
                                allowance.second = true;
                                return true;
                        } else
                                return false;
                }
        }
        return false;
}

bool DartsProfessionalEvaluator::isValid(const QString& mod, const int& point)
{
        if(point > MaxPoint || point < 0)
                return false;
        return AllowedMods.contains(mod);
}

bool DartsProfessionalEvaluator::isWithinBounds(const int& remainingScore)
{
        if (remainingScore > 1)
                return true;
        return false;
}

int DartsProfessionalEvaluator::remainingScore(const QString& mod, const int& point) const
{
        auto scoreValue = point * modMultiplier(mod);
        auto playerScore = _scores->score().playerScore();
        return playerScore - scoreValue;
}

int DartsProfessionalEvaluator::modMultiplier(QString mod) const
{
        if(mod == "S")
                return 1;
        else if(mod == "D")
                return 2;
        else
                return 3;
}
