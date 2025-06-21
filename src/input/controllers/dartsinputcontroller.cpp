#include "dartsinputcontroller.h"
#include "src/input/services/idartsinputsfilter.h"
#include "src/input/services/idartsinputsupdater.h"
#include "src/scores/services/iscoresupdate.h"
#include "src/servicecollection.h"
#include "src/turns/persistences/idartsindexes.h"
#include "src/validation/services/iclosurefilter.h"
#include "src/validation/services/iopenvalidator.h"

#include <QJsonDocument>

typedef QList<DartsInput> Inputs;

DartsInputController::DartsInputController(ServiceCollection* services)
    : _services(services)
{
}

void DartsInputController::add(const QByteArray& inputsAsJson)
{
    auto inputs = fromJson(inputsAsJson);
    auto allowed = _services->openingFilter->filter(inputs);
    auto accepted = _services->closeningFilter->filter(allowed);
    _services->inputsUpdater->removeExcessInputs();
    _services->inputsUpdater->save(accepted);
    _services->indexes->next();
    _services->scoresUpdate->updatePlayerScores();
    _services->closeningFilter->evaluateWinnerCondition();
}

QByteArray DartsInputController::inputs(const QString &name) {
    auto inputs = _services->inputsFilter->valids(name);
    QJsonArray arr;
    for (const auto &input : std::as_const(inputs))
        arr << input.toJsonObject();
    return QJsonDocument(arr).toJson();
}

bool DartsInputController::isValid(const int &point, const QString& mod) const {
    return _services->openingFilter->isValid(point,mod);
}

DartsInputController::Candidates DartsInputController::fromJson(const QByteArray& json) const
{
    auto jsonDoc = QJsonDocument::fromJson(json);
    if (!jsonDoc.isArray())
        return QList<InputCandidate>();
    return InputCandidate::fromJsonArray(jsonDoc.array());
}
