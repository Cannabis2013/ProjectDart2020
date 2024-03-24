#include "dartsinputsupdater.h"
#include "src/input/persistence/idartsinputs.h"
#include "src/players/models/dartsplayer.h"
#include "src/players/services/iplayerfetcher.h"
#include "src/servicecollection.h"
#include "src/turns/models/dartsturnindex.h"
#include "src/turns/persistences/idartsindexes.h"

DartsInputsUpdater::DartsInputsUpdater(ServiceCollection* services)
    : _services(services)
{
}

void DartsInputsUpdater::removeExcessInputs()
{
        auto index = _services->indexes->index();
        auto inputs = _services->inputs->all();
        Inputs filtered;
        for (const auto& input : inputs) {
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
        auto name = _services->playerFetcher->one().name();
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
