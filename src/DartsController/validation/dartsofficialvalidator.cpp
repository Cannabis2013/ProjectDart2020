#include "dartsofficialvalidator.h"

bool DartsOfficialValidator::evaluatorInput(const QString& mod, const int& point)
{
        if (!isValid(mod, point))
                return false;
        auto remaining = remainingScore(mod, point);
        if (isWithinBounds(remaining))
                return true;
        else if (isWinnerShot(remaining, mod, point))
                return true;
        return false;
}

void DartsOfficialValidator::evaluateScoreCondition()
{
        for (const auto& score : _scores->scores().playerScores()) {
                if (score.score() == 0) {
                        _status->winnerFound();
                        _players->declareAsWinner(score.name());
                }
        }
}

bool DartsOfficialValidator::isValid(const QString& mod, const int& point)
{
        if(point > MaxPoint || point < 0)
                return false;
        return AllowedMods.contains(mod);
}

bool DartsOfficialValidator::isWithinBounds(const int& remainingScore)
{
        if (remainingScore > 1)
                return true;
        return false;
}

bool DartsOfficialValidator::isWinnerShot(const int& remainingScore, const QString& mod, const int& point)
{
        return remainingScore == 0 && validEndThrow(mod, point);
}

int DartsOfficialValidator::remainingScore(const QString& mod, const int& point) const
{
        auto scoreValue = inputScore(mod, point);
        auto playerScore = _scores->score().playerScore();
        return playerScore - scoreValue;
}

int DartsOfficialValidator::inputScore(const QString& mod, const int& point) const
{
        auto multiplier = modMultiplier(mod);
        return point * multiplier;
}

int DartsOfficialValidator::modMultiplier(QString mod) const
{
        if(mod == "S")
                return 1;
        else if(mod == "D")
                return 2;
        else
                return 3;
}

bool DartsOfficialValidator::validEndThrow(const QString& mod, const int& point) const
{
        return mod == "D" || point == 50;
}
