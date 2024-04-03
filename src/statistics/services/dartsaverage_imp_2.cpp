#include "src/players/services/iplayerfetcher.h"
#include "statscalculator.h"

#ifdef USE_IMP_2
#include "src/scores/persistence/idartsscores.h"
#include "src/servicecollection.h"
#include "src/turns/models/dartsturnindex.h"
#include "src/turns/persistences/idartsindexes.h"

double StatsCalculator::middle(const QString& name) const
{
        auto playerIndex = _services->playerFetcher->indexOf(name);
        auto rounds = finishedRounds(playerIndex);
        auto score = playerScore(name);
        return score / rounds;
}

int StatsCalculator::finishedRounds(const int& playerIndex) const
{
        auto index = _services->indexes->index();
        auto turnIndex = index.turnIndex();
        auto rounds = index.roundIndex();
        if (rounds > 1 && playerIndex >= turnIndex)
                rounds--;
        return rounds;
}

int StatsCalculator::playerScore(const QString& name) const
{
        auto playerIndex = _services->playerFetcher->indexOf(name);
        auto scoreObject = _services->scores->all().at(playerIndex);
        auto remaining = scoreObject.value();
        auto initialScore = _services->scores->initialScore();
        auto score = initialScore - remaining;
        return score;
}

#endif
