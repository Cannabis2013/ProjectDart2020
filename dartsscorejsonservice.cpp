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
    auto json = _assembleJsonFromDartsMultiAttemptScores->service(models);
    return json;
}

DartsScoreJsonService *DartsScoreJsonService::setAssembleJsonByDartsScoreIndexes(IUnaryService<const IDartsScoreIndexes *, QByteArray> *newAssembleJsonByDartsScoreIndexes)
{
    _assembleJsonByDartsScoreIndexes = newAssembleJsonByDartsScoreIndexes;
    return this;
}

DartsScoreJsonService *DartsScoreJsonService::setAssembleJsonFromDartsMultiAttemptScores(IUnaryService<const QVector<const IPlayerInput *> &, QByteArray> *newAssembleJsonFromDartsMultiAttemptScores)
{
    _assembleJsonFromDartsMultiAttemptScores = newAssembleJsonFromDartsMultiAttemptScores;
    return this;
}

