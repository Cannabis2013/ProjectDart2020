#include "statscalculator.h"

#ifdef USE_IMP_2
#include "src/scores/models/Score.h"
#include "src/scores/persistence/idartsscores.h"
#include "src/scores/services/idartsscoresfetch.h"
#include "src/servicecollection.h"
#include "src/turns/models/dartsturnindex.h"
#include "src/turns/persistences/idartsindexes.h"

double StatsCalculator::middle(const QString& name) const
{
        auto rounds = finishedRounds();
        auto score = playerScore(name);
        return score / rounds;
}

int StatsCalculator::finishedRounds() const
{
        auto index = _services->indexes->index();
        auto turnId = index.turnId();
        auto rounds = index.roundIndex();
        if (rounds > 1 && turnId % 2 == 0)
                rounds--;
        return rounds;
}

int StatsCalculator::playerScore(const QString& name) const
{
        auto remaining = _services->scoresFetcher->score(name).value();
        auto initialScore = _services->scores->initialScore();
        auto score = initialScore - remaining;
        return score;
}

#endif
