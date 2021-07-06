#ifndef DARTSPOINTSJSONSERVICE_H
#define DARTSPOINTSJSONSERVICE_H

#include "idartsmodelscreatejsonfrompoints.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "idartspointinput.h"

namespace DartsModelsContext {
    class DartsModelsCreateJsonFromPoints : public IDartsModelsCreateJsonFromPoints
    {
    public:
        virtual QByteArray createJson(const QVector<const IPlayerInput*> &models) const override;
    };
}

#endif // DARTSPOINTSJSONSERVICE_H
