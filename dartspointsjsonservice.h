#ifndef DARTSPOINTSJSONSERVICE_H
#define DARTSPOINTSJSONSERVICE_H

#include "idartspointsjsonservice.h"
#include "iplayerinput.h"
#include "idartspointindexes.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "idartspointinput.h"

namespace DartsModelsContext {
    class DartsPointsJsonService : public
            IDartsPointsJsonService<IPlayerInput,IDartsPointIndexes,QByteArray>
    {
    public:
        static DartsPointsJsonService* createInstance();
        virtual JsonFormat createJson(const IndexesInterface *indexes) const override;
        virtual JsonFormat createJson(const QVector<const ModelInterface *> &models) const override;
    };
}


#endif // DARTSPOINTSJSONSERVICE_H
