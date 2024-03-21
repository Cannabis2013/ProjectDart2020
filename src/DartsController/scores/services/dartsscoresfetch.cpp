#include "dartsscoresfetch.h"
#include "src/DartsController/scores/models/Score.h"
#include "src/DartsController/scores/persistence/idartsscores.h"
#include "src/DartsController/servicecollection.h"
#include "src/DartsController/turns/models/dartsturnindex.h"
#include "src/DartsController/turns/persistences/idartsindexes.h"

DartsScoresFetch::DartsScoresFetch(ServiceCollection* services)
    : _services(services)
{
}

Score DartsScoresFetch::score()
{
        auto index = _services->indexes->index().turnIndex();
        auto scores = _services->scores->all();
        return scores.at(index);
}

Score DartsScoresFetch::score(const QString& name)
{
        auto scores = _services->scores->all();
        for (const auto& score : scores) {
                if (score.name() == name)
                        return score;
        }
        return Score();
}
