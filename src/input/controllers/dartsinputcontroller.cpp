#include "dartsinputcontroller.h"
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
        auto accepted = filteredInputs(candidates);
        _services->inputsUpdater->removeExcessInputs();
        _services->inputsUpdater->save(accepted);
        _services->indexes->next();
        _services->scoresUpdate->updatePlayerScores();
        _services->evaluator->evaluateWinnerCondition();
}

DartsInputController::Candidates DartsInputController::filteredInputs(const Candidates& candidates) const
{
        Candidates filtered;
        for (const auto& candidate : candidates) {
                if (_services->evaluator->evaluateInput(candidate.mod(), candidate.point()))
                        filtered << candidate;
        }
        return filtered;
}

DartsInputController::Candidates DartsInputController::fromJson(const QByteArray& json) const
{
        auto jsonDoc = QJsonDocument::fromJson(json);
        if (!jsonDoc.isArray())
                return QList<InputCandidate>();
        return InputCandidate::fromJsonArray(jsonDoc.array());
}
