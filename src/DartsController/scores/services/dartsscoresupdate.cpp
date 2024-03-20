#include "dartsscoresupdate.h"
#include "src/DartsController/input/services/idartsinputsfilter.h"
#include "src/DartsController/players/models/dartsplayer.h"
#include "src/DartsController/players/persistences/idartsplayers.h"
#include "src/DartsController/scores/models/Score.h"
#include "src/DartsController/scores/persistence/idartsscores.h"
#include "src/DartsController/scores/services/iscorescalculator.h"
#include "src/DartsController/servicecollection.h"

DartsScoresUpdate::DartsScoresUpdate(ServiceCollection* services)
    : _services(services)
{
}

void DartsScoresUpdate::resetPlayerScores()
{
        auto initialScore = _services->scores->initialScore();
        auto fresh = freshScores(initialScore);
        _services->scores->setScores(fresh);
}

void DartsScoresUpdate::updatePlayerScores()
{
        auto initialScore = _services->scores->initialScore();
        auto updated = updatedScores(initialScore);
        _services->scores->setScores(updated);
}

QList<Score> DartsScoresUpdate::freshScores(const int& initialScore) const
{
        QList<Score> fresh;
        auto players = _services->players->all();
        for (const auto& player : players)
                fresh << Score(player.name(), initialScore);
        return fresh;
}

QList<Score> DartsScoresUpdate::updatedScores(const int& initialScore) const
{
        QList<Score> updated;
        for (const auto& player : _services->players->all()) {
                auto inputs = _services->inputsFilter->validFromName(player.name());
                auto score = _services->calculator->calculate(player.name(), inputs, initialScore);
                updated.append(score);
        }
        return updated;
}

void DartsScoresUpdate::initPlayerScores(const int& initialScore)
{
        auto scores = freshScores(initialScore);
        _services->scores->setScores(scores);
        _services->scores->setInitialScore(initialScore);
}