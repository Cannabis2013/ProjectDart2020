#include "dartsscores.h"
#include "src/DartsController/scores/models/dartsinitialvalues.h"
#include "src/DartsController/scores/persistence/scoresio.h"
#include "src/DartsController/scores/services/iscorescalculator.h"
#include <src/DartsController/scores/models/Score.h>
#include <src/DartsController/servicecollection.h>

void DartsScores::initFromStorage()
{
        ScoresIO storage;
        auto values = storage.fromFile();
        _scores = values.scores();
        _initialScore = values.initialScore();
}

int DartsScores::initialScore() const
{
        return _initialScore;
}

void DartsScores::setInitialScore(const int& initialScore)
{
        _initialScore = initialScore;
}

QList<Score> DartsScores::scores()
{
        return _scores;
}

bool DartsScores::saveState()
{
        ScoresIO storage;
        return storage.toFile(_scores, _initialScore);
}

void DartsScores::setScores(const QList<Score>& scores)
{
        _scores = scores;
}
