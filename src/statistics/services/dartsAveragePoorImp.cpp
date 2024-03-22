#include "statscalculator.h"

#ifdef USE_POOR_AVERAGE

#include "src/input/services/idartsinputsfilter.h"
#include "src/scores/models/Score.h"
#include "src/scores/persistence/idartsscores.h"
#include "src/scores/services/idartsscoresfetch.h"
#include "src/servicecollection.h"

/*
 * Poor implementation
 *
 * The average of the two first throws in a turn is based on prediction
 * rather on the actual average of the combined throws
 */

double StatsCalculator::middle(const QString& name) const
{
        auto count = _services->inputsFilter->validCount(name);
        if (count <= 0)
                return 0;
        auto remaining = _services->scoresFetcher->score(name).value();
        auto score = _services->scores->initialScore() - remaining;
        return 3 * (score / count);
}
#endif
