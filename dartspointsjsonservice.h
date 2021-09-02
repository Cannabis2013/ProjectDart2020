#ifndef DARTSPOINTSJSONSERVICE_H
#define DARTSPOINTSJSONSERVICE_H

#include "idartsmodelscreatejsonfrompoints.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "idartsinput.h"

namespace ModelsContext {
    class DartsModelsCreateJsonFromPoints : public IDartsModelsCreateJsonFromPoints
    {
    public:
        virtual QByteArray createJson(const QVector<const IModel<QUuid>*> &models) const override;
    };
}

#endif // DARTSPOINTSJSONSERVICE_H
