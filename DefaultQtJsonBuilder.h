#ifndef JSONBUILDER_H
#define JSONBUILDER_H

#include "iqtjsonbuilder.h"
#include "QString"
#include <qjsondocument.h>
#include <qjsonobject.h>

class DefaultQtJsonBuilder : public IQtJsonBuilder
{
public:
    virtual JsonFormat createJson(const Id &id, const String &key) const override
    {
        QJsonObject obj;
        obj[key] = id.toString(QUuid::WithoutBraces);
        auto document = QJsonDocument(obj);
        auto json = document.toJson();
        return json;
    }
    virtual JsonFormat createJson(const String &string, const String &key) const override
    {
        QJsonObject obj;
        obj[key] = string;
        auto document = QJsonDocument(obj);
        auto json = document.toJson();
        return json;
    }
};

#endif // DARTSSCOREJSONEXTRACTOR_H