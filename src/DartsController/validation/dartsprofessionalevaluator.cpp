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
        if (!isAllowed(mod))
                return false;
        if (!isValid(mod, point))
                return false;
        auto remaining = remainingScore(mod, point);
        if (isWithinBounds(remaining))
                return true;
        else if (isWinnerShot(remaining, mod, point))
                return true;
        return false;
}

void DartsProfessionalEvaluator::evaluateScoreCondition()
{
        for (const auto& score : _scores->scores().playerScores()) {
                if (score.score() == 0) {
                        _status->winnerFound();
                        _players->declareAsWinner(score.name());
                }
        }
}

bool DartsProfessionalEvaluator::isAllowed(const QString& mod)
{
        auto name = _players->name();
        for (auto& allowance : allowances) {
                if (allowance.first == name) {
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

bool DartsProfessionalEvaluator::isWinnerShot(const int& remainingScore, const QString& mod, const int& point)
{
        return remainingScore == 0 && (mod == "D" || point == 50);
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
