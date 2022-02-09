#include "bytearraytoinputs.h"
#include "SLAs/servicescontext.h"
#include "Inputs/ijsontosnapshot.h"
#include <qvector.h>
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>

ByteArrayToInputs::ByteArrayToInputs(ServicesContext *provider):_provider(provider)
{
    _jsonToSnapShot = provider->snapShotServices()->jsonToInput();
}

ByteArrayToInputs::Models ByteArrayToInputs::convert(const ByteArray &ba) const
{
    QVector<SnapShot> snapShots;
    auto document = QJsonDocument::fromJson(ba);
    if(!document.isArray()) return QVector<SnapShot>();
    auto jsonArray = document.array();
    for (const auto &jsonValue : jsonArray) {
        auto jsonObject = jsonValue.toObject();
        auto snapShot = _jsonToSnapShot->convert(jsonObject);
        snapShots << snapShot;
    }
    return snapShots;
}
