#include "dartsinputsfilter.h"
#include "src/DartsController/input/persistence/idartsinputs.h"
#include "src/DartsController/servicecollection.h"
#include "src/DartsController/turns/models/dartsturnindex.h"
#include "src/DartsController/turns/persistences/idartsindexes.h"

DartsInputsfilter::DartsInputsfilter(ServiceCollection* services)
    : _services(services)
{
}

bool DartsInputsfilter::anyInputs(const QString& name, const int& throwId) const
{
        auto inputs = _services->inputs->all();
        for (auto& input : inputs) {
                if (input.playerName() == name && input.throwId() < throwId)
                        return true;
        }
        return false;
}

QList<Input> DartsInputsfilter::validFromName(const QString& name) const
{
        QList<Input> filtered;
        auto throwId = _services->indexes->index().throwId();
        auto inputs = _services->inputs->all();
        for (const auto& input : inputs) {
                if (input.playerName() == name && input.throwId() < throwId)
                        filtered << input;
        }
        return filtered;
}


int DartsInputsfilter::validCount(const QString& name) const
{
        int count = 0;
        auto throwId = _services->indexes->index().throwId();
        auto inputs = _services->inputs->all();
        for (const auto& input : inputs) {
                if (input.playerName() == name && input.throwId() < throwId)
                        count++;
        }
        return count;
}
