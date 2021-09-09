#ifndef GENERICJSONBUILDER_H
#define GENERICJSONBUILDER_H

#include "QString"
#include <qjsondocument.h>
#include <qjsonobject.h>

class GenericJsonBuilder
{
public:
    static QByteArray createJson(const QUuid &value, const QString &key)
    {
        QJsonObject obj;
        obj[key] = value.toString(QUuid::WithoutBraces);
        return toByteArray(obj);
    }
    static QByteArray createJson(const QString &value, const QString &key)
    {
        return toByteArray({{key,value}});
    }
private:
    static QByteArray toByteArray(const QJsonObject &obj)
    {
        auto document = QJsonDocument(obj);
        return document.toJson();
    }
};

#endif // DARTSSCOREJSONEXTRACTOR_H
