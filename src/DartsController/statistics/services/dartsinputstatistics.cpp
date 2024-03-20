#include "dartsinputstatistics.h"
#include "src/DartsController/input/services/idartsinputsfilter.h"
#include "src/DartsController/scores/models/Score.h"
#include "src/DartsController/scores/persistence/idartsscores.h"
#include "src/DartsController/scores/services/idartsscoresfetch.h"
#include "src/DartsController/scores/services/iscorescalculator.h"
#include "src/DartsController/servicecollection.h"
#include "src/DartsController/turns/models/dartsturnindex.h"
#include "src/DartsController/turns/persistences/idartsindexes.h"

DartsInputStatistics::DartsInputStatistics(ServiceCollection* services)
    : _services(services)
{
}

double DartsInputStatistics::middle(const QString& name) const
{
        auto playerScore = _services->scoresFetcher->score(name).value();
        auto currentTurnId = _services->indexes->index().turnId();
        auto completedTurns = currentTurnId == 2 ? 1 : currentTurnId - 2;
        if (completedTurns < 1)
                return 0;
        auto initialScore = _services->scores->initialScore();
        auto score = initialScore - playerScore;
        return score / completedTurns;
}

int DartsInputStatistics::lowest(const QString& name) const
{
        auto inputs = _services->inputsFilter->validFromName(name);
        if (inputs.length() < 3)
                return 0;
        return findValueByComparison(inputs, 180, [](const int& lowest, const int& sum) {
                return sum < lowest;
        });
}

int DartsInputStatistics::highest(const QString& name) const
{
        auto inputs = _services->inputsFilter->validFromName(name);
        if (inputs.length() < 3)
                return 0;
        return findValueByComparison(inputs, 0, [](const int& highest, const int& sum) {
                return sum > highest;
        });
}

int DartsInputStatistics::findValueByComparison(const QList<Input>& inputs, int target, const std::function<bool(const int&, const int&)>& predicate) const
{
        auto sum = 0;
        for (int index = 0; index < inputs.length(); ++index) {
                auto input = inputs.at(index);
                auto score = _services->calculator->score(input.mod(), input.point());
                sum += score;
                if ((index + 1) % 3 == 0) {
                        target = predicate(target, sum) ? sum : target;
                        sum = 0;
                }
        }
        return target;
}
