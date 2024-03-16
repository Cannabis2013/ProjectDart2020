#include "dartsscores.h"
#include "src/DartsController/indexes/idartsindexes.h"
#include "src/DartsController/input/idartsinputs.h"
#include "src/DartsController/players/dartsplayer.h"
#include "src/DartsController/players/idartsplayers.h"
#include "src/DartsController/scores/models/dartsinitialvalues.h"
#include "src/DartsController/scores/persistence/scoresio.h"
#include "src/DartsController/scores/services/iscorescalculator.h"
#include <src/DartsController/scores/models/Score.h>
#include <src/DartsController/servicecollection.h>

DartsScores::DartsScores(ServiceCollection* services)
    : _services(services)
{
        _scoresIO = new ScoresIO("playerScores.dat");
}

void DartsScores::init(const int& initialScore)
{
        _initialScore = initialScore;
        _scores.clear();
        for (const auto& player : _services->players->all())
                _scores << Score(player.name(), _initialScore);
}

void DartsScores::initFromFile()
{
        auto values = _scoresIO->fromFile();
        _scores = values.scores();
        _initialScore = values.initialScore();
}

int DartsScores::initialScore() const
{
        return _initialScore;
}

void DartsScores::reset()
{
        _scores.clear();
        for (const auto& player : _services->players->all())
                _scores << Score(player.name(), _initialScore);
}

void DartsScores::update()
{
        auto throwIndex = _services->indexes->index().throwIndex();
        _scores.clear();
        for (const auto& player : _services->players->all()) {
                auto inputs = _services->inputs->inputs(player.name(), throwIndex);
                auto score = _services->calculator->calculate(player.name(), inputs, _initialScore);
                _scores.append(score);
        }
}

Score DartsScores::score(){
        auto playerIndex = _services->indexes->index().playerIndex();
        auto score = _scores.at(playerIndex);
        return score;
}

Score DartsScores::score(const QString& name)
{
        for (const auto& score : _scores) {
                if (score.name() == name)
                        return score;
        }
        return Score();
}

QList<Score> DartsScores::scores()
{
        return _scores;
}

bool DartsScores::saveState()
{
        return _scoresIO->toFile(_scores, _initialScore);
}
