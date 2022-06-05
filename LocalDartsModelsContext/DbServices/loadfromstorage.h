#ifndef LOADFROMSTORAGE_H
#define LOADFROMSTORAGE_H

#include <qstring.h>

template<typename T> class IModel;
class QUuid;
class QJsonObject;
class QByteArray;
class IFileDataIO;
template<typename T> class IModelConverter;

class LoadFromStorage
{
public:
    typedef IModel<QUuid> Model;
    typedef QVector<Model*> Models;
    typedef IModelConverter<Model> Converter;
    LoadFromStorage(const QString &key, IFileDataIO *ioDevice, Converter *converter);
    Models load();
private:
    Models toModels(const QByteArray &byteArray);
    Converter *_converter;
    IFileDataIO *_ioDevice;
    const QString _jsonKey;
};
#endif // FETCHFROMSTORAGE_H
