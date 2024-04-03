#include "dartsscorescontroller.h"
#include "src/Finishes/idartsfinishes.h"
#include "src/players/services/iplayerfetcher.h"
#include "src/scores/models/Score.h"
#include "src/scores/persistence/idartsscores.h"
#include "src/scores/services/iscoresdelta.h"
#include "src/servicecollection.h"
#include "src/turns/models/dartsturnindex.h"
#include "src/turns/persistences/idartsindexes.h"
#include <QJsonObject>

DartsScoresController::DartsScoresController(ServiceCollection* services)
    : _services(services)
{
}

int DartsScoresController::playerOne() const
{
        auto score = _services->scores->all().value(0);
        return score.value();
}

int DartsScoresController::playerTwo() const
{
        auto score = _services->scores->all().value(1);
        return score.value();
}

QString DartsScoresController::finishRow() const
{
        auto turnIndex = _services->indexes->index().turnIndex();
        auto scoreObject = _services->scores->all().at(turnIndex);
        auto remaining = scoreObject.value();
        return _services->finishes->suggestTargetRow(remaining, 0);
}

int DartsScoresController::delta() const
{
        return _services->scoresDelta->delta();
}

int DartsScoresController::currentRemaining() const
{
        auto turnIndex = _services->indexes->index().turnIndex();
        auto score = _services->scores->all().at(turnIndex);
        return score.value();
}
