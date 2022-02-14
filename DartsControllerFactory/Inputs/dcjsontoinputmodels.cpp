#include "dcjsontoinputmodels.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "Converters/idcjsontomodel.h"
#include "Models/dcinput.h"

DCJsonToInputModels::Models DCJsonToInputModels::convert(const QByteArray &byteArray, JsonToModel *jsonToModel) const
{
    auto arr = QJsonDocument::fromJson(byteArray).array();
    Models models;
    for (const auto &jsonVal : qAsConst(arr))
        models << jsonToModel->convert(jsonVal.toObject());
    return models;
}
