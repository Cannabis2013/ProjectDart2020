#ifndef JSONBUILDER_H
#define JSONBUILDER_H

#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>

class JsonBuilder
{
public:
    void add(const QJsonObject &obj, const QString &key)
    {
        _obj[key] = obj;
    }
    void add(const QJsonArray &arr, const QString &key)
    {
        _obj[key] = arr;
    }
    QByteArray toByteArray() const
    {
        return QJsonDocument(_obj).toJson();
    }
    QJsonObject toObject() const
    {
        return _obj;
    }
private:
    QJsonObject _obj;
};

#endif // JSONBUILDER_H
