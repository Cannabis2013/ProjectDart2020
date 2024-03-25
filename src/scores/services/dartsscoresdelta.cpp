#include "dartsscoresdelta.h"
#include "src/scores/persistence/idartsscores.h"
#include "src/servicecollection.h"
#include "src/turns/models/dartsturnindex.h"
#include "src/turns/persistences/idartsindexes.h"

DartsScoresDelta::DartsScoresDelta(ServiceCollection* services)
    : _services(services)
{
}

int DartsScoresDelta::delta() const
{
        auto scores = _services->scores->all();
        if (scores.length() != 2)
                return -1;
        auto index = _services->indexes->index();
        auto playerIndex = index.turnIndex();
        auto firstRemaining = scores.takeAt(playerIndex).value();
        auto secondRemaining = scores.first().value();
        auto initialScore = _services->scores->initialScore();
        auto firstScore = initialScore - firstRemaining;
        auto secondScore = initialScore - secondRemaining;
        return firstScore - secondScore;
}
