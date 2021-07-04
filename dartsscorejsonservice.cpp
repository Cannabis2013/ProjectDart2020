#include "dartsscorejsonservice.h"

using namespace DartsModelsContext;

DartsScoreJsonService *DartsScoreJsonService::createInstance()
{
    return new DartsScoreJsonService;
}

DartsScoreJsonService::JsonFormat DartsScoreJsonService::assembleJsonDartsScoreIndexes(const ModelIndexes *indexes) const
{
    auto json = _assembleJsonByDartsScoreIndexes->service(indexes);
    return json;
}

DartsScoreJsonService::JsonFormat DartsScoreJsonService::assembleJsonFromDartsMultiAttemptScores(const QVector<const ModelInterface *> &models) const
{
    auto json = _assembleJsonFromDartsScores->service(models);
    return json;
}

