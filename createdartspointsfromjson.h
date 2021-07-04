#ifndef CREATEDARTSPOINTSFROMJSON_H
#define CREATEDARTSPOINTSFROMJSON_H

#include "icreateinputmodelsfromjson.h"
#include <qjsondocument.h>
#include <qjsonvalue.h>
#include <qjsonvalue.h>
#include <qjsonarray.h>
#include "qjsonobject.h"
#include "dartspointinput.h"
namespace DartsModelsContext {
    class CreateDartsPointsFromJson : public ICreateInputModelsFromJson
    {
    public:
        virtual QVector<const IPlayerInput *> create(const QByteArray &json) const override;
    private:
        const QJsonArray createArray(const QByteArray &json) const;
        QVector<const IPlayerInput*> createInputsFromJsonArray(const QJsonArray &arr) const;
        const IPlayerInput *createInputFromJsonValue(const QJsonValue &jsonValue) const;
        const DartsModelsContext::DartsPointInput* createModelFromJsonObject(const QJsonObject& jsonObject) const;

    };
}


#endif // DARTSINPUTJSONEXTRACTOR_H
