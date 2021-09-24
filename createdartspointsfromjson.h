#ifndef CREATEDARTSPOINTSFROMJSON_H
#define CREATEDARTSPOINTSFROMJSON_H

#include "icreatemodelsfromjson.h"
#include <qjsondocument.h>
#include <qjsonvalue.h>
#include <qjsonvalue.h>
#include <qjsonarray.h>
#include "qjsonobject.h"
#include "DartsModelsContext/DMCInputServices/dartsinput.h"
namespace DartsDbContext {
    class CreateDartsPointsFromJson : public ICreateModelsFromJson
    {
    public:
        virtual QVector<const IModel<QUuid> *> create(const QByteArray &json) const override;
    private:
        const QJsonArray toJsonArray(const QByteArray &json) const;
        QVector<const IModel<QUuid> *> createInputsFromJsonArray(const QJsonArray &arr) const;
        const ModelsContext::IDartsInput* toInputModel(const QJsonObject& jsonObject) const;
        QUuid toId(const QJsonObject &obj, const QString &key) const;
    };
}


#endif // DARTSINPUTJSONEXTRACTOR_H
