#include "statscalculator.h"
#include "src/input/persistence/idartsinputs.h"
#include "src/input/services/idartsinputsfilter.h"
#include "src/scores/services/idartsremainings.h"
#include "src/servicecollection.h"
#include "src/turns/models/dartsturnindex.h"
#include "src/turns/persistences/idartsindexes.h"

StatsCalculator::StatsCalculator(ServiceCollection* services)
    : _services(services)
{
}

int StatsCalculator::lowest(const QString& name) const
{
    auto roundIndex = _services->indexes->index().roundIndex();
    auto count = _services->inputsFilter->validCount(name);
    auto result = count > 0 ? 180 : 0;
    for (int i = 1; i <= roundIndex; ++i) {
        auto inputs = _services->inputsFilter->valids(name, i);
        auto sum = _services->scores->calculateRemaining(inputs);
        result = inputs.length() == 0 ? result : sum < result ? sum : result;
    }
    return result;
}

int StatsCalculator::highest(const QString& name) const
{
    auto rounds = _services->indexes->index().roundIndex();
    auto result = 0;
    for (int roundIndex = 1; roundIndex <= rounds; ++roundIndex) {
        auto roundInputs = _services->inputsFilter->valids(name, roundIndex);
        auto sum = _services->scores->calculateRemaining(roundInputs);
        result = sum > result ? sum : result;
    }
    return result;
}
