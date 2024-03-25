#include "dartsscorescontroller.h"
#include "src/Finishes/idartsfinishes.h"
#include "src/scores/models/Score.h"
#include "src/scores/persistence/idartsscores.h"
#include "src/scores/services/idartsscoresfetch.h"
#include "src/scores/services/iscoresdelta.h"
#include "src/servicecollection.h"
#include <QJsonObject>

DartsScoresController::DartsScoresController(ServiceCollection* services)
    : _services(services)
{
}

int DartsScoresController::playerOne() const
{
        auto scores = _services->scores->all();
        auto score = scores.first();
        return score.value();
}

int DartsScoresController::playerTwo() const
{
        auto scores = _services->scores->all();
        auto score = scores.last();
        return score.value();
}

QString DartsScoresController::finishRow() const
{
        auto remaining = _services->scoresFetcher->score().value();
        return _services->finishes->suggestTargetRow(remaining, 0);
}

int DartsScoresController::delta() const
{
        return _services->scoresDelta->delta();
}
