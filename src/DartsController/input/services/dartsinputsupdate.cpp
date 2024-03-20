#include "dartsinputsupdate.h"
#include "src/DartsController/input/persistence/idartsinputs.h"
#include "src/DartsController/players/models/dartsplayer.h"
#include "src/DartsController/players/services/iplayerfetcher.h"
#include "src/DartsController/servicecollection.h"
#include "src/DartsController/turns/models/dartsturnindex.h"
#include "src/DartsController/turns/persistences/idartsindexes.h"

DartsInputsUpdate::DartsInputsUpdate(ServiceCollection* services)
    : _services(services)
{
}

void DartsInputsUpdate::save(const QString& mod, const int& point)
{
        auto name = _services->playerFetcher->one().name();
        auto throwId = _services->indexes->index().throwId();
        Input input(mod, point, name, throwId);
        auto inputs = _services->inputs->all() << input;
        _services->inputs->setInputs(inputs);
}

void DartsInputsUpdate::removeExcessInputs()
{
        auto throwId = _services->indexes->index().throwId();
        QList<Input> filtered;
        auto inputs = _services->inputs->all();
        for (const auto& input : inputs) {
                if (input.throwId() < throwId)
                        filtered << input;
        }
        _services->inputs->setInputs(filtered);
}

void DartsInputsUpdate::removeCurrentTurnInputs()
{
        auto turnId = _services->indexes->index().turnId();
        QList<Input> filtered;
        auto inputs = _services->inputs->all();
        for (const auto& input : inputs) {
                if (input.turnId() != turnId)
                        filtered << input;
        }
        _services->inputs->setInputs(filtered);
}
