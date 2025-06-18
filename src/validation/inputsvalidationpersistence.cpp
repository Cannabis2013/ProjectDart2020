#include "inputsvalidationpersistence.h"
#include "qjsonarray.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "src/FileIO/filejsonio.h"

InputsValidationPersistence::InputsValidationPersistence(const QString &fileName)
{
    _ioDevice = new FileJsonIO(fileName);
}

QHash<QString, bool> InputsValidationPersistence::readAllowances()
{
    QHash<QString, bool> allowances;
    auto jsonObject = _ioDevice->readAsJson().object();
    auto arr = jsonObject.value("allowances").toArray();
    QJsonObject obj;
    for (const auto& value : std::as_const(arr)) {
        obj = value.toObject();
        allowances.insert(obj.value("key").toString(),obj.value("val").toBool());
    }
    return allowances;
}

QString InputsValidationPersistence::readModifier() {
    auto jsonObject = _ioDevice->readAsJson().object();
    return jsonObject.value("openingModifier").toString("D");
}

bool InputsValidationPersistence::readEnabled() {
    auto jsonObject = _ioDevice->readAsJson().object();
    return jsonObject.value("enabled").toBool(false);
}

void InputsValidationPersistence::save(const QHash<QString, bool> &allowances,
                                       const QString &openModifier)
{
    QJsonObject jsonObj;
    jsonObj.insert("openingModifier",openModifier);
    QJsonObject obj;
    QJsonArray arr;
    auto keys = allowances.keys();
    for (const auto& key : std::as_const(keys)) {
        obj.insert("key",key);
        obj.insert("value",allowances.value(key));
        arr << obj;
    }
    jsonObj.insert("allowances",arr);
    _ioDevice->write(jsonObj);
}
