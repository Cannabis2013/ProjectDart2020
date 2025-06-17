#include "dartsscorescontroller.h"
#include <QJsonArray>
#include <QJsonObject>
#include "src/Finishes/idartsfinishes.h"
#include "src/players/services/iplayerfetcher.h"
#include "src/scores/models/Score.h"
#include "src/scores/persistence/idartsscores.h"
#include "src/scores/services/iscoresdelta.h"
#include "src/servicecollection.h"
#include "src/turns/models/dartsturnindex.h"
#include "src/turns/persistences/idartsindexes.h"

DartsScoresController::DartsScoresController(ServiceCollection* services)
    : _services(services)
{
}

QString DartsScoresController::finishRow() const
{
        auto turnIndex = _services->indexes->index().playerIndex();
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
        auto turnIndex = _services->indexes->index().playerIndex();
        auto score = _services->scores->all().at(turnIndex);
        return score.value();
}

int DartsScoresController::current() const {
    auto playerIndex = _services->indexes->index().playerIndex();
    auto score = _services->scores->all().value(playerIndex);
    return score.value();
}

QByteArray DartsScoresController::all() const {
    auto scores = _services->scores->all();
    QJsonArray arr;
    for (const auto& score : std::as_const(scores))
        arr << score.jsonObject();
    return QJsonDocument(arr).toJson(QJsonDocument::Compact);
}
