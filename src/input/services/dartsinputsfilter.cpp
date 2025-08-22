#include "dartsinputsfilter.h"
#include "src/input/persistence/idartsinputs.h"
#include "src/servicecollection.h"
#include "src/turns/models/dartsturnindex.h"
#include "src/turns/persistences/idartsindexes.h"

typedef QList<DartsInput> Inputs;

DartsInputsfilter::DartsInputsfilter(ServiceCollection* services)
    : _services(services)
{
}

bool DartsInputsfilter::anyInputs(const QString& name, const int& turnId) const
{
    auto inputs = _services->inputs->all();
    for (auto& input : inputs) {
        if (input.playerName() == name && input.roundIndex() < turnId)
            return true;
    }
    return false;
}

QList<DartsInput> DartsInputsfilter::valids(const QString& name) const
{
    Inputs filtered;
    auto turnId = _services->indexes->index().turnId();
    auto inputs = _services->inputs->all();
    for (const auto& input : std::as_const(inputs)) {
        if (input.playerName() == name && input.turnId() < turnId)
            filtered << input;
    }
    return filtered;
}

QList<DartsInput> DartsInputsfilter::valids(const QString &name, const int &roundIndex) const
{
    Inputs filtered;
    auto inputs = _services->inputs->all();
    auto turnId = _services->indexes->index().turnId();
    for (const auto &input : std::as_const(inputs)) {
        if (input.playerName() == name && input.roundIndex() == roundIndex
            && input.turnId() < turnId) {
            filtered << input;
        }
    }
    return filtered;
}

int DartsInputsfilter::validCount(const QString& name) const
{
    int count = 0;
    auto index = _services->indexes->index();
    auto inputs = _services->inputs->all();
    for (const auto &input : std::as_const(inputs)) {
        if (input.playerName() == name && input.turnId() < index.turnId())
            count++;
    }
    return count;
}
