#include "dartsscorescontroller.h"
#include "src/DartsController/Finishes/idartsfinishes.h"
#include "src/DartsController/scores/models/Score.h"
#include "src/DartsController/scores/persistence/idartsscores.h"
#include "src/DartsController/scores/services/idartsscoresfetch.h"
#include "src/DartsController/servicecollection.h"
#include "src/DartsController/turns/models/dartsturnindex.h"
#include "src/DartsController/turns/persistences/idartsindexes.h"
#include <QJsonObject>

DartsScoresController::DartsScoresController(ServiceCollection* services)
    : _services(services)
{
}

int DartsScoresController::playerOne() const
{
        auto scores = _services->scores->scores();
        auto score = scores.first();
        return score.value();
}

int DartsScoresController::playerTwo() const
{
        auto scores = _services->scores->scores();
        auto score = scores.last();
        return score.value();
}

QString DartsScoresController::finishRow() const
{
        auto turnIndex = _services->indexes->index().throwIndex();
        auto remaining = _services->scoresFetcher->score().value();
        return _services->finishes->suggestTargetRow(remaining, turnIndex);
}

QString DartsScoresController::delta() const
{
        auto scores = _services->scores->scores();
        if (scores.length() != 2)
                return QString();
        auto scoreOne = scores.at(0).value();
        auto scoreTwo = scores.at(1).value();
        auto diff = scoreTwo - scoreOne;
        return QString::number(diff >= 0 ? diff : diff * (-1));
}
