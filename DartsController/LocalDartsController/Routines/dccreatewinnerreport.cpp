#include "dccreatewinnerreport.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <DartsController/Contracts/ServicesProvider/dcservices.h>
#include <DartsController/Contracts/Meta/dcmetaservices.h>
#include <DartsController/Contracts/Inputs/dcinputsservices.h>
#include <DartsController/Contracts/Models/dcmeta.h>

DCCreateWinnerReport::DCCreateWinnerReport(DCServices *services)
{
         _metaManager = services->metaServices()->metaManager();
         _inputToJson = services->inputServices()->inputConverter();
}

QByteArray DCCreateWinnerReport::create() const
{
        auto meta = _metaManager->meta();
        auto lastInput = meta.lastInput;
        QJsonObject json;
        json["WinnerDetails"] = createWinnerJson(meta);
        json["LastReportedInput"] = _inputToJson->convert(lastInput);
        auto byteArray = toByteArray(json);
        return byteArray;
}

QJsonObject DCCreateWinnerReport::createWinnerJson(const DCMeta &meta) const
{
    QJsonObject json;
    json["winnerName"] = meta.winnerName;
    return json;
}

QByteArray DCCreateWinnerReport::toByteArray(const QJsonObject &obj) const
{
    auto document = QJsonDocument(obj);
    auto byteArray = document.toJson();
    return byteArray;
}
