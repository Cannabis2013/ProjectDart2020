#ifndef DARTSSCOREINDEXESBUILDERSERVICE_H
#define DARTSSCOREINDEXESBUILDERSERVICE_H

#include "idscindexesbuilder.h"
#include "DartsScoreMultiAttempIndexes.h"
#include "idsindexservice.h"
#include <qjsondocument.h>
#include <QJsonObject>

namespace DSCContext {
    /*
     * Darts Score(DS) indexes builder service
     */
    class DSIndexesBuilder : public IDSCIndexesBuilder
    {
    public:
        const DSCContext::IDSCIndexes *createIndexes(const QByteArray &json) const override;
        const DSCContext::IDSCIndexes *createIndexes(const IDSIndexService *service) const override;
    };
}

#endif // DARTSSCOREINDEXESBUILDERSERVICE_H
