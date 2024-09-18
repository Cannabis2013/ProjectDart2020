#include "dartsinputcontroller.h"
#include "src/input/services/idartsinputsfilter.h"
#include "src/input/services/idartsinputsupdater.h"
#include "src/scores/services/iscoresupdate.h"
#include "src/servicecollection.h"
#include "src/status/idartsstatus.h"
#include "src/turns/persistences/idartsindexes.h"
#include "src/validation/abstractdartsevaluator.h"

typedef QList<DartsInput> Inputs;

DartsInputController::DartsInputController(ServiceCollection* services)
    : _services(services)
{
}

void DartsInputController::add(const QByteArray& inputs)
{
    if (_services->status->isWinnerFound())
        return;
    auto candidates = fromJson(inputs);
    auto accepted = _services->evaluator->acceptedInputs(candidates);
    _services->inputsUpdater->removeExcessInputs();
    _services->inputsUpdater->save(accepted);
    _services->indexes->next();
    _services->scoresUpdate->updatePlayerScores();
    _services->evaluator->evaluateWinnerCondition();
}

QByteArray DartsInputController::inputs(const QString &name) {
    auto inputs = _services->inputsFilter->valids(name);
    QJsonArray arr;
    for (const auto &input : inputs)
        arr << input.toJsonObject();
    return QJsonDocument(arr).toJson();
}

DartsInputController::Candidates DartsInputController::fromJson(const QByteArray& json) const
{
    auto jsonDoc = QJsonDocument::fromJson(json);
    if (!jsonDoc.isArray())
        return QList<InputCandidate>();
    return InputCandidate::fromJsonArray(jsonDoc.array());
}
