#include "dartsinputsupdater.h"
#include "src/input/idartsinputs.h"
#include "src/players/idartsplayers.h"
#include "src/servicecollection.h"
#include "src/turns/dartsturnindex.h"
#include "src/turns/idartsindexes.h"

DartsInputsUpdater::DartsInputsUpdater(ServiceCollection* services)
    : _services(services)
{
}

void DartsInputsUpdater::removeExcessInputs()
{
    auto index = _services->indexes->index();
    auto inputs = _services->inputs->all();
    Inputs filtered;
    for (const auto& input : std::as_const(inputs)) {
        if (input.turnId() < index.turnId())
            filtered << input;
    }
    _services->inputs->setInputs(filtered);
}

DartsInputsUpdater::Inputs DartsInputsUpdater::toInputs(const Candidates& candidates)
{
    Inputs inputs;
    for (const auto& candidate : candidates)
        inputs << candidate.input();
    return inputs;
}

void DartsInputsUpdater::save(const QList<InputCandidate>& candidates)
{
    auto inputs = toInputs(candidates);
    auto playerIndex = _services->indexes->index().playerIndex();
    auto name = _services->players->all().at(playerIndex);
    auto index = _services->indexes->index();
    auto savedInputs = _services->inputs->all();
    for (auto& input : inputs) {
        input.setTurnId(index.turnId());
        input.setPlayerName(name);
        input.setRoundIndex(index.roundIndex());
        savedInputs << input;
    }
    _services->inputs->setInputs(savedInputs);
}
