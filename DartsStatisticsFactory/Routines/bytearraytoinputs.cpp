#include "bytearraytoinputs.h"
#include "SLAs/servicescontext.h"
#include "Inputs/ijsontoinput.h"
#include <qvector.h>
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
ByteArrayToInputs::ByteArrayToInputs(ServicesContext *provider):_provider(provider)
{
    _jsonToInput = provider->inputServices()->jsonToInput();
}

ByteArrayToInputs::Models ByteArrayToInputs::convert(const ByteArray &ba) const
{
    QVector<Input> inputs;
    auto document = QJsonDocument::fromJson(ba);
    if(!document.isArray()) return QVector<Input>();
    auto jsonArray = document.array();
    for (const auto &jsonValue : jsonArray) {
        auto jsonObject = jsonValue.toObject();
        auto input = _jsonToInput->convert(jsonObject);
        inputs << input;
    }
    return inputs;
}
