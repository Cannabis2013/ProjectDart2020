#include "dartsprofessionalevaluator.h"
#include "src/players/models/dartsplayer.h"
#include "src/players/persistences/idartsplayers.h"
#include "src/players/services/iplayerfetcher.h"
#include "src/scores/models/Score.h"
#include "src/scores/persistence/idartsscores.h"
#include "src/scores/services/idartsscoresfetch.h"
#include "src/scores/services/iscorescalculator.h"
#include "src/servicecollection.h"
#include "src/status/idartsstatus.h"
#include "src/validation/dartsallowances.h"

DartsProfessionalEvaluator::DartsProfessionalEvaluator(ServiceCollection* services)
    : _services(services)
{
        _allowances = new DartsAllowances();
}

void DartsProfessionalEvaluator::init()
{
        QStringList names;
        auto players = _services->players->all();
        for (const auto& player : players)
                names << player.name();
        _allowances->init(names);
}

bool DartsProfessionalEvaluator::evaluateInput(const QString& mod, const int& point)
{
        auto name = _services->playerFetcher->one().name();
        if (!validateInput(name, mod, point))
                return false;
        auto playerScore = _services->scoresFetcher->score().value();
        return validateRemaining(mod, point, playerScore);
}

void DartsProfessionalEvaluator::evaluateWinnerCondition()
{
        auto scores = _services->scores->all();
        for (const auto& score : scores) {
                if (score.value() == 0) {
                        _services->status->winnerFound();
                        auto winner = _services->playerFetcher->one(score.name());
                        winner.setWinner(true);
                }
        }
}

void DartsProfessionalEvaluator::updateAllowance(const QString& name, const bool& allowance)
{
        _allowances->updateAllowance(name, allowance);
}

bool DartsProfessionalEvaluator::validateInput(const QString& name, const QString& mod, const int& point)
{
        if (!isValid(point, mod))
                return false;
        if (_allowances->isAllowed(name))
                return true;
        if (mod == "D")
                return _allowances->updateAllowance(name, true);
        return false;
}

bool DartsProfessionalEvaluator::validateRemaining(const QString& mod, const int& point, const int& current)
{
        auto remaining = _services->calculator->remaining(mod, point, current);
        if (remaining > 1)
                return true;
        else if (remaining == 0 && (mod == "D" || point == 50))
                return true;
        return false;
}

bool DartsProfessionalEvaluator::isValid(const int& point, const QString& mod) const
{
        if (point > MaxPoint || point < 0)
                return false;
        return AllowedMods.contains(mod);
}
