#ifndef DARTSSCOREINDEXESBUILDERSERVICE_H
#define DARTSSCOREINDEXESBUILDERSERVICE_H

#include "idartscontrollerindexesbuilder.h"
#include "DartsScoreMultiAttempIndexes.h"
#include "idartsscoreindexservice.h"
#include <qbytearray.h>
#include <qjsondocument.h>
#include <QJsonObject>

namespace DartsScoreControllerContext {
    class DartsScoreIndexesBuilderService : public
            IDartsControllerIndexesBuilder<IDartsScoreControllerIndexes<QByteArray>,
                                           IDartsScoreIndexService<IDartsScoreControllerIndexes<QByteArray>>,
                                           QByteArray>
    {
    public:
        typedef IDartsScoreControllerIndexes<QByteArray> ControllerIndexes;
        const TurnIndexes *buildControllerIndexesByJson(const JsonFormat &json) const override;
        const TurnIndexes *buildControllerIndexesByIndexService(const ControllerIndexService *service) const override;
    };
}

#endif // DARTSSCOREINDEXESBUILDERSERVICE_H
