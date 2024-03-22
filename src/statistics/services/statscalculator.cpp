#include "statscalculator.h"
#include "src/input/services/idartsinputsfilter.h"
#include "src/scores/models/Score.h"
#include "src/scores/persistence/idartsscores.h"
#include "src/scores/services/idartsscoresfetch.h"
#include "src/scores/services/iscorescalculator.h"
#include "src/servicecollection.h"

StatsCalculator::StatsCalculator(ServiceCollection* services)
    : _services(services)
{
}

int StatsCalculator::lowest(const QString& name) const
{
        auto inputs = _services->inputsFilter->valids(name);
        auto sum = 0;
        auto result = -1;
        for (int index = 0; index < inputs.length(); ++index) {
                auto input = inputs.at(index);
                sum += _services->calculator->score(input.mod(), input.point());
                if ((index + 1) % 3 == 0) {
                        result = sum < result || result == -1 ? sum : result;
                        sum = 0;
                }
        }
        return result > -1 ? result : sum;
}

int StatsCalculator::highest(const QString& name) const
{
        auto inputs = _services->inputsFilter->valids(name);
        auto sum = 0;
        auto result = 0;
        for (int index = 0; index < inputs.length(); ++index) {
                auto input = inputs.at(index);
                sum += _services->calculator->score(input.mod(), input.point());
                if ((index + 1) % 3 == 0) {
                        result = sum > result ? sum : result;
                        sum = 0;
                }
        }
        return result;
}
