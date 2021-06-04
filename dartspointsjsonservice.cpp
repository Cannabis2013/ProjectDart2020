#include "dartspointsjsonservice.h"

using namespace DartsModelsContext;

DartsPointsJsonService::JsonFormat DartsModelsContext::DartsPointsJsonService::assembleJsonDartsPointIndexes(const IndexesInterface *indexes) const
{
    auto json = _assembleJsonDartsPointIndexes->service(indexes);
    return json;
}

DartsPointsJsonService::JsonFormat DartsModelsContext::DartsPointsJsonService::assembleJsonOrderedDartsPointModels(const QVector<const ModelInterface *> &pointModels,
                                                                                                                   const PlayerModelsInterface *service) const
{
    auto json = _assembleJsonOrderedDartsPointModels->service(pointModels,service);
    return json;
}

DartsPointsJsonService::JsonFormat DartsModelsContext::DartsPointsJsonService::assembleJsonFromTournamentDartsPoints(const QVector<const ModelInterface *> &models) const
{
    auto json = _assembleJsonFromTournamentDartsPoints->service(models);
    return json;
}

const DartsPointsJsonService::ModelInterface *DartsModelsContext::DartsPointsJsonService::assembleDartsPointModelFromJson(const JsonFormat &json) const
{
    auto model = _assembleDartsPointModelFromJson->service(json);
    return model;
}

DartsPointsJsonService *DartsPointsJsonService::setAssembleJsonDartsPointIndexes(IUnaryService<const IDartsPointIndexes *, QByteArray> *newAssembleJsonDartsPointIndexes)
{
    _assembleJsonDartsPointIndexes = newAssembleJsonDartsPointIndexes;
    return this;
}

DartsPointsJsonService *DartsPointsJsonService::setAssembleJsonOrderedDartsPointModels(IBinaryService<const QVector<const IPlayerInput *> &, const IPlayerModelsService *, const QByteArray> *newAssembleJsonOrderedDartsPointModels)
{
    _assembleJsonOrderedDartsPointModels = newAssembleJsonOrderedDartsPointModels;
    return this;
}
