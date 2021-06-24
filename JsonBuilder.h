#ifndef JSONBUILDER_H
#define JSONBUILDER_H

#include "ijsonbuilder.h"
#include "QString"
#include <qjsondocument.h>
#include <qjsonobject.h>

namespace DartsScoreControllerContext {
    class JsonBuilder : public IJsonBuilder<QByteArray,QUuid,QString>
    {
    public:
        virtual JsonFormat createJsonByKey(const Id &id, const String &key) const override
        {
            QJsonObject obj;
            obj[key] = id.toString(QUuid::WithoutBraces);
            auto document = QJsonDocument(obj);
            auto json = document.toJson();
            return json;
        }
        virtual JsonFormat createJsonByKey(const String &string, const String &key) const override
        {
            QJsonObject obj;
            obj[key] = string;
            auto document = QJsonDocument(obj);
            auto json = document.toJson();
            return json;
        }
    };
}

#endif // DARTSSCOREJSONEXTRACTOR_H
