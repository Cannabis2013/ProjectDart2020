#include "jsonopenpersistence.h"
#include "qjsonarray.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "src/FileIO/filejsonio.h"

QHash<QString, bool> JsonOpenPersistence::readAllowances() const
{
    auto ioDevice = FileJsonIO(_file);
    QHash<QString, bool> allowances;
    auto jsonObject = ioDevice.readAsJson().object();
    auto arr = jsonObject.value("allowances").toArray();
    QJsonObject obj;
    for (const auto& value : std::as_const(arr)) {
        obj = value.toObject();
        allowances.insert(obj.value("key").toString(),obj.value("val").toBool());
    }
    return allowances;
}

QString JsonOpenPersistence::readModifier() const
{
    auto ioDevice = FileJsonIO(_file);
    auto jsonObject = ioDevice.readAsJson().object();
    return jsonObject.value("openingModifier").toString("D");
}

bool JsonOpenPersistence::readEnabled() const
{
    auto ioDevice = FileJsonIO(_file);
    auto jsonObject = ioDevice.readAsJson().object();
    return jsonObject.value("enabled").toBool(false);
}

void JsonOpenPersistence::save(const QHash<QString, bool> &allowances,
                                       const QString &openModifier)
{
    QJsonObject jsonObj;
    auto ioDevice = FileJsonIO(_file);
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
    ioDevice.write(jsonObj);
}
