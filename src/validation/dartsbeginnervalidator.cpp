#include "dartsbeginnervalidator.h"

#include "src/players/models/dartsplayer.h"
#include "src/players/persistences/idartsplayers.h"
#include "src/players/services/iplayerfetcher.h"
#include "src/scores/models/Score.h"
#include "src/scores/persistence/idartsscores.h"
#include "src/servicecollection.h"
#include "src/status/idartsstatus.h"

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
        auto scores = _services->scores->all();
        for (const auto& score : scores) {
                if (score.value() <= 0) {
                        _services->status->winnerFound();
                        auto winner = &_services->playerFetcher->one(score.name());
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
