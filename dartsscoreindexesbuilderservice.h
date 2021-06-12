#ifndef DARTSSCOREINDEXESBUILDERSERVICE_H
#define DARTSSCOREINDEXESBUILDERSERVICE_H

#include "idartscontrollerindexesbuilder.h"
#include "DartsScoreMultiAttempIndexes.h"
#include "idartsmultiattemptindexservice.h"
#include <qbytearray.h>
#include <qjsondocument.h>
#include <QJsonObject>

namespace DartsScoreControllerContext {
    class DartsScoreIndexesBuilderService : public
            IDartsControllerIndexesBuilder<IDartsMultiAttemptIndexes,IDartsMultiAttemptIndexService<IDartsMultiAttemptIndexes>,QByteArray>
    {
    public:

        // IDartsControllerIndexesBuilder interface
    public:
        const TurnIndexes *buildControllerIndexesByJson(const JsonFormat &json) const override;
        const TurnIndexes *buildControllerIndexesByIndexService(const ControllerIndexService *service) const override;
    };
}

#endif // DARTSSCOREINDEXESBUILDERSERVICE_H
