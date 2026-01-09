#include "dartsinputcontroller.h"
#include "src/input/idartsinputsfilter.h"
#include "src/input/idartsinputsupdater.h"
#include "src/servicecollection.h"
#include "src/turns/idartsindexes.h"
#include "src/validation/iclosurefilter.h"
#include "src/validation/iopenvalidator.h"

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
}

QByteArray DartsInputController::inputs(const QString& name) const
{
    auto inputs = _services->inputsFilter->valids(name);
    QJsonArray arr;
    for (const auto &input : std::as_const(inputs))
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

QByteArray DartsInputController::inputs(const QString& name, const int& roundIndex) const
{
    auto inputs = _services->inputsFilter->valids(name, roundIndex);
    QJsonArray arr;
    for (const auto& input : std::as_const(inputs))
        arr << input.toJsonObject();
    return QJsonDocument(arr).toJson();
}
