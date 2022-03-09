#ifndef SAVETOSTORAGE_H
#define SAVETOSTORAGE_H
#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <quuid.h>
#include "ModelSLAs/imodel.h"
#include "DbSLAs/idbcontext.h"
#include "DbSLAs/imodelconverter.h"
#include "FileIOSLAs/ifiledataio.h"
class SaveToStorage
{
public:
    typedef IModel<QUuid> Model;
    typedef QVector<Model*> Models;
    typedef QByteArray ByteArray;
    typedef QJsonObject Json;
    typedef IModelConverter<Model> Converter;
    SaveToStorage(const QString &key, IFileDataIO *ioDevice, Converter *converter);
protected:
    virtual bool save(const Models &models);
private:
    QJsonObject toJsonObject(const QByteArray &byteArray);
    QJsonObject toJsonObject(const QJsonObject &json, const Models &models);
    IFileDataIO *const _ioDevice;
    Converter *const _converter;
    QString _jsonKey;
};


#endif // SAVETOSTORAGE_H
