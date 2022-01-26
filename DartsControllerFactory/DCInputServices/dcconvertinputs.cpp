#include "dcconvertinputs.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "ModelBuilderSLAs/idcmodelconverter.h"
#include "Models/dcinput.h"

DCConvertInputs::Models DCConvertInputs::convert(const QByteArray &byteArray, ModelBuilder *builder) const
{
    auto arr = QJsonDocument::fromJson(byteArray).array();
    Models models;
    for (const auto &jsonVal : qAsConst(arr))
        models << builder->create(jsonVal.toObject());
    return models;
}
