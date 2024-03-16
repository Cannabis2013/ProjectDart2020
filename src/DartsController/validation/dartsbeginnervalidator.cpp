#include "dartsbeginnervalidator.h"

#include "src/DartsController/servicecollection.h"
#include "src/DartsController/players/dartsplayer.h"
#include "src/DartsController/players/idartsplayers.h"
#include "src/DartsController/scores/DartsPlayerScores.h"
#include "src/DartsController/scores/idartsscores.h"
#include "src/DartsController/status/idartsstatus.h"

DartsBeginnerValidator::DartsBeginnerValidator(ServiceCollection* services)
    : _services(services)
{
}

bool DartsBeginnerValidator::evaluateInput(const QString& mod, const int& point)
{
        return isValid(mod, point);
}

void DartsBeginnerValidator::evaluateWinnerCondition()
{
        auto scores = _services->scores->scores().playerScores();
        for (const auto& score : std::as_const(scores)) {
                if (score.score() <= 0) {
                        _services->status->winnerFound();
                        auto winner = &_services->players->one(score.name());
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
