#include "dartsprofessionalevaluator.h"
#include "src/players/models/dartsplayer.h"
#include "src/players/persistences/idartsplayers.h"
#include "src/players/services/iplayerfetcher.h"
#include "src/scores/models/Score.h"
#include "src/scores/persistence/idartsscores.h"
#include "src/scores/services/iscorescalculator.h"
#include "src/servicecollection.h"
#include "src/status/idartsstatus.h"
#include "src/turns/models/dartsturnindex.h"
#include "src/turns/persistences/idartsindexes.h"
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

const QList<InputCandidate> DartsProfessionalEvaluator::acceptedInputs(
    const QList<InputCandidate> &candidates)
{
    auto turnIndex = _services->indexes->index().turnIndex();
    auto player = _services->players->all().at(turnIndex);
    auto allowed = validInputs(candidates,player.name());
    return accepted(allowed);
}

void DartsProfessionalEvaluator::evaluateWinnerCondition() {
    auto scores = _services->scores->all();
    for (const auto& score : scores) {
        if (score.value() <= 0) {
            _services->status->setWinner(score.name());
            auto winner = &_services->playerFetcher->one(score.name());
            winner->setWinner(true);
        }
    }
}

AbstractDartsEvaluator::Candidates DartsProfessionalEvaluator::validInputs(const Candidates &candidates, const QString& name)
{
    if(_allowances->isAllowed(name))
        return candidates;
    auto allowed = false;
    Candidates allowedCandidates;
    for (const auto &candidate : candidates) {
        if(!allowed && candidate.point() == 20 && candidate.mod() == "D")
            allowed = true;
        if(allowed && isValid(candidate.point(),candidate.mod()))
            allowedCandidates << candidate;
    }
    return allowedCandidates;

}

bool DartsProfessionalEvaluator::isValid(const int& point, const QString& mod) const
{
    if (point > MaxPoint || point < 0)
        return false;
    return AllowedMods.contains(mod);
}

AbstractDartsEvaluator::Candidates DartsProfessionalEvaluator::accepted(const Candidates &candidates)
{
    Candidates accepted;
    auto remaining = currentRemaining();
    for (const auto &candidate : candidates) {
        auto score = _services->calculator->score(candidate.input());
        remaining -= score;
        accepted << candidate;
        if (remaining == 0 && (candidate.mod() == "D" || candidate.point() == 50))
            return accepted;
        else if (remaining < 0)
            return Candidates();
    }
    return accepted;
}

int DartsProfessionalEvaluator::currentRemaining() const {
    auto turnIndex = _services->indexes->index().turnIndex();
    auto scoreObject = _services->scores->all().at(turnIndex);
    return scoreObject.value();
}
