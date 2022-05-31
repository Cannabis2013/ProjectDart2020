#include "dartsinputstobytearray.h"
#include <QJsonDocument>
#include <qbytearray.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "InputModelsSLAs/idartsinput.h"
#include "DbSLAs/imodelconverter.h"
#include "SLAs/dartsmodelsservices.h"

DartsInputsToByteArray::ByteArray DartsInputsToByteArray::fromInputs(const QUuid &tournamentID, const DartsModelsServices *services) const
{
    auto models = getInputsFromMemory(tournamentID,services);
    QJsonArray arr = toJsonArray(models,services);
    return QJsonDocument(arr).toJson();
}

DartsInputsToByteArray::Models DartsInputsToByteArray::getInputsFromMemory(const QUuid &tournamentID, const DartsModelsServices *services) const
{
    auto dbContext = services->inputServices()->dbContext();
    auto models = dbContext->models([=](Model *model, const int &){
        return dynamic_cast<IDartsInput*>(model)->tournamentId() == tournamentID;
    });
    return models;
}

QJsonArray DartsInputsToByteArray::toJsonArray(const Models &models, const DartsModelsServices *services) const
{
    QJsonArray arr;
    auto converter = services->inputServices()->inputConverter();
    for (const auto &model : qAsConst(models))
        arr << converter->convert(model);
    return arr;
}
