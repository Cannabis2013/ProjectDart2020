#include "dartsbeginnervalidator.h"

#include "src/DartsController/players/models/dartsplayer.h"
#include "src/DartsController/players/persistences/idartsplayers.h"
#include "src/DartsController/scores/models/Score.h"
#include "src/DartsController/scores/persistence/idartsscores.h"
#include "src/DartsController/servicecollection.h"
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
        auto scores = _services->scores->scores();
        for (const auto& score : scores) {
                if (score.value() <= 0) {
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
