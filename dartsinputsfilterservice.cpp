#include "dartsinputsfilterservice.h"

using namespace DartsModelsContext;

DartsInputsFilterService::Models DartsModelsContext::DartsInputsFilterService::filterByTournamentId(const Models &models, const QUuid &id) const
{
    Models m;
    for (const auto& model : models) {
        if(model->tournamentId() == id)
            m << model;
    }
    return m;
}

DartsInputsFilterService::Models DartsModelsContext::DartsInputsFilterService::filterByPlayerId(const Models &models, const QUuid &id) const
{
    Models m;
    for (const auto& model : models) {
        if(model->playerId() == id)
            m << model;
    }
    return m;
}

DartsInputsFilterService::Models DartsModelsContext::DartsInputsFilterService::filterByInputHint(const Models &models, const int &hint) const
{
    Models m;
    for (const auto& model : models) {
        if(model->hint() == hint)
            m << model;
    }
    return m;
}

DartsInputsFilterService::Models DartsModelsContext::DartsInputsFilterService::filterByRoundIndex(const Models &models, const int &roundIndex) const
{
    Models m;
    for (const auto& model : models) {
        if(model->roundIndex() == roundIndex)
            m << model;
    }
    return m;
}

DartsInputsFilterService::Models DartsInputsFilterService::filterByAttemptIndex(const Models &models, const int &attemptIndex) const
{
    Models m;
    for (const auto& model : models) {
        auto pointModel = dynamic_cast<const IDartsPointInput*>(model);
        if(pointModel->attempt() == attemptIndex)
            m << model;
    }
    return m;
}
