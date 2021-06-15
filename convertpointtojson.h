#ifndef DATAMODELPOINTTOJSON_H
#define DATAMODELPOINTTOJSON_H

#include "idatamodelpoint.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include "iconvertpointtojson.h"

namespace DartsDataModelsContext {
    class ConvertPointToJson : public IConvertPointToJson
    {
    public:
        QByteArray toJson(const IDataModelPoint* model) override
        {
            QJsonObject obj = {
                {"point",model->point()},
                {"score",model->score()}
            };
            auto document = QJsonDocument(obj);
            auto json = document.toJson();
            return json;
        }
    };
}

#endif // DATAMODELPOINTTOJSON_H
