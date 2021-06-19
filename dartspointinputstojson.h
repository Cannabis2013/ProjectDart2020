#ifndef DARTSPOINTINPUTSTOJSON_H
#define DARTSPOINTINPUTSTOJSON_H

#include "idartscontrollerpoint.h"
#include "idartsinputstojson.h"
#include <quuid.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

namespace DartsPointControllerContext {
    class DartsPointInputsToJson : public IDartsInputsToJson<IDartsControllerPoint<QUuid,QString,QByteArray>,QByteArray>
    {
    public:
        JsonFormat toJson(const InputModels &inputs) const override;

    private:
        QByteArray toJsonByteArray(const QJsonArray &arr) const;
        QJsonArray toJsonArray(const InputModels &inputs) const;
        QJsonObject toJsonobject(const InputModel* inputModel) const;
    };
}


#endif // DARTSPOINTINPUTSTOJSON_H
