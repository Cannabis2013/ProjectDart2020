#include "dartsscoresupdate.h"
#include "src/input/services/idartsinputsfilter.h"
#include "src/players/models/dartsplayer.h"
#include "src/players/persistences/idartsplayers.h"
#include "src/scores/models/Score.h"
#include "src/scores/persistence/idartsscores.h"
#include "src/scores/services/iscorescalculator.h"
#include "src/servicecollection.h"

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
        auto players = _services->players->all();
        for (const auto& player : players) {
                auto inputs = _services->inputsFilter->valids(player.name());
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
