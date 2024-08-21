#include "dartsmediumvalidator.h"
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

DartsMediumValidator::DartsMediumValidator(ServiceCollection *services)
    :_services(services){
}

const QList<InputCandidate> DartsMediumValidator::acceptedInputs(
    const QList<InputCandidate> &candidates)
{
    auto valid = validInputs(candidates);
    return accepted(valid);
}

void DartsMediumValidator::evaluateWinnerCondition()
{
    auto scores = _services->scores->all();
    for (const auto& score : scores) {
        if (score.value() <= 0) {
            _services->status->setWinner(score.name());
            auto winner = &_services->playerFetcher->one(score.name());
            winner->setWinner(true);
        }
    }
}

AbstractDartsEvaluator::Candidates DartsMediumValidator::validInputs(
    const Candidates &candidates) const
{
    Candidates valid;
    for (const auto &candidate : candidates) {
        if (candidate.point() <= MaxPoint || candidate.point() > 0)
            valid << candidate;
    }
    return valid;
}

AbstractDartsEvaluator::Candidates DartsMediumValidator::accepted(const Candidates &candidates)
{
    Candidates accepted;
    auto preRemaining = currentRemaining();
    auto postRemaining = preRemaining;
    for (const auto &candidate : candidates) {
        auto score = _services->calculator->score(candidate.mod(), candidate.point());
        postRemaining -= score;
        if (postRemaining == 0 && preRemaining == candidate.point()) {
            accepted << candidate;
            return accepted;
        } else if (postRemaining < 0)
            return Candidates();
        accepted << candidate;
        preRemaining = postRemaining;
    }
    return accepted;
}

int DartsMediumValidator::currentRemaining() const
{
    auto turnIndex = _services->indexes->index().turnIndex();
    auto scoreObject = _services->scores->all().at(turnIndex);
    return scoreObject.value();
}
