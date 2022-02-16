#include "dartsinputstojson.h"
#include <QJsonDocument>
#include <qbytearray.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "InputModelsSLAs/idartsinput.h"
#include "DbSLAs/imodelconverter.h"
#include "SLAs/dartsmodelsservices.h"
DartsInputsToJson::DartsInputsToJson(DartsModelsServices *services):_services(services)
{
    _iptsDb = services->inputServices()->inputsDb();
    _cvtr = services->inputServices()->inputConverter();
}

DartsInputsToJson::ByteArray DartsInputsToJson::fromInputs(const QUuid &tournamentID) const
{
    QJsonArray arr;
    auto models = _iptsDb->models([=](Model *model){
        return dynamic_cast<IDartsInput*>(model)->tournamentId() == tournamentID;
    });
    for (const auto &model : qAsConst(models))
        arr << _cvtr->create(model);
    return toByteArray(arr);
}

QByteArray DartsInputsToJson::toByteArray(const QJsonArray &arr) const
{
    auto document = QJsonDocument(arr);
    return document.toJson();
}
