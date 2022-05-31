#include "loadfromstorage.h"
#include <qvector.h>
#include "FileIOSLAs/ifiledataio.h"
#include <qbytearray.h>
#include <qjsondocument.h>
#include "ModelSLAs/imodel.h"
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <DbSLAs/imodelconverter.h>


LoadFromStorage::LoadFromStorage(const QString &key, IFileDataIO *ioDevice, Converter *converter)
    :_converter(converter),_ioDevice(ioDevice),_jsonKey(key){}


LoadFromStorage::Models LoadFromStorage::load()
{
    auto byteArray = _ioDevice->read();
    auto models = toModels(byteArray);
    return models;
}

LoadFromStorage::Models LoadFromStorage::toModels(const QByteArray &byteArray)
{
    Models models;
    auto obj = QJsonDocument::fromJson(byteArray).object();
    auto arr = obj[_jsonKey].toArray();
    for (const auto &jsonVal : qAsConst(arr))
        models << _converter->convert(jsonVal.toObject());
    return models;
}
