#ifndef GENERICJSONBUILDER_H
#define GENERICJSONBUILDER_H

#include "igenericjsonbuilder.h"
#include "QString"
#include <qjsondocument.h>
#include <qjsonobject.h>

class GenericJsonBuilder : public IGenericJsonBuilder
{
public:
    virtual JsonFormat createJson(const Id &value, const String &key) const override
    {
        QJsonObject obj;
        obj[key] = value.toString(QUuid::WithoutBraces);
        return toByteArray(obj);
    }
    virtual JsonFormat createJson(const String &value, const String &key) const override
    {
        return toByteArray({{key,value}});
    }
private:
    QByteArray toByteArray(const QJsonObject &obj) const
    {
        auto document = QJsonDocument(obj);
        return document.toJson();
    }
};

#endif // DARTSSCOREJSONEXTRACTOR_H
