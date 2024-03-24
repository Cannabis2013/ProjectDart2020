#include "dartsinputsfilter.h"
#include "src/input/persistence/idartsinputs.h"
#include "src/servicecollection.h"
#include "src/turns/models/dartsturnindex.h"
#include "src/turns/persistences/idartsindexes.h"

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
        for (const auto& input : inputs) {
                if (input.playerName() == name && input.turnId() < turnId)
                        filtered << input;
        }
        return filtered;
}


int DartsInputsfilter::validCount(const QString& name) const
{
        int count = 0;
        auto roundIndex = _services->indexes->index().roundIndex();
        auto inputs = _services->inputs->all();
        for (const auto& input : inputs) {
                if (input.playerName() == name && input.roundIndex() < roundIndex)
                        count++;
        }
        return count;
}
