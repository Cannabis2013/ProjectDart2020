#include "dartsinputsfilterservice.h"

using namespace DartsModelsContext;

DartsInputsFilterService::IDartsInputsFilter::Models DartsInputsFilterService::filterByTournamentId(const Models &models,
                                                                                                    const UniqueId &id) const
{
    Models list;
    for (const auto& model : models) {
        if(model->tournamentId() == id)
            list << model;
    }
    return list;
}

DartsInputsFilterService::Models DartsInputsFilterService::filterByPlayerId(const Models &models,
                                                                            const UniqueId &tournamentId,
                                                                            const UniqueId &playerId) const
{
    auto tournamentInputModels = filterByTournamentId(models,tournamentId);
    Models inputModelsByPlayerId;
    for (const auto& model : tournamentInputModels) {
        if(model->playerId() == playerId)
            inputModelsByPlayerId << model;
    }
    return inputModelsByPlayerId;
}

DartsInputsFilterService::IDartsInputsFilter::Models DartsInputsFilterService::filterByHint(const Models &models,
                                                                                            const UniqueId &tournamentId,
                                                                                            const UniqueId &playerId,
                                                                                            const int &hint) const
{
    auto inputModelsByPlayerId = filterByPlayerId(models,tournamentId,playerId);
    Models playerInputsByHint;
    for (const auto& model : inputModelsByPlayerId) {
        if(model->hint() == hint)
            playerInputsByHint << model;
    }
    return playerInputsByHint;

}

DartsInputsFilterService::Models DartsInputsFilterService::filterByRoundIndex(const Models &models,
                                                                              const UniqueId &tournamentId,
                                                                              const UniqueId &playerId,
                                                                              const int &roundIndex) const
{
    auto inputModelsByPlayerId = filterByPlayerId(models,tournamentId,playerId);
    Models playerInputsByRoundIndex;
    for (const auto& model : inputModelsByPlayerId) {
        if(model->roundIndex() == roundIndex)
            playerInputsByRoundIndex << model;
    }
    return playerInputsByRoundIndex;
}

DartsInputsFilterService::Models DartsInputsFilterService::filterByAttemptIndex(const Models &models,
                                                                                const UniqueId &tournamentId,
                                                                                const UniqueId &playerId,
                                                                                const int &roundIndex,
                                                                                const int &hint,
                                                                                const int &attemptIndex) const
{
    auto inputModelsByRoundIndex = filterByRoundIndex(models,tournamentId,playerId,roundIndex);
    Models inputModelsByAttemptIndex;
    for (const auto& model : inputModelsByRoundIndex) {
        auto pointModel = dynamic_cast<const IDartsPointInput*>(model);
        if(pointModel->attempt() != attemptIndex)
            continue;
        if(pointModel->hint() == hint || hint == AllHints)
            inputModelsByAttemptIndex << model;
    }
    return inputModelsByAttemptIndex;
}


DartsInputsFilterService::Models DartsModelsContext::DartsInputsFilterService::filterByHint(const Models &models,
                                                                                            const UniqueId &tournamentId,
                                                                                            const int &hint) const
{
    auto inputModelsByTournamentId = filterByTournamentId(models,tournamentId);
    Models inputModelsByHint;
    for (const auto& model : inputModelsByTournamentId) {
        if(model->hint() == hint)
            inputModelsByHint << model;
    }
    return inputModelsByHint;
}


DartsInputsFilterService::Models DartsModelsContext::DartsInputsFilterService::filterByHint(const Models &models, const int &hint) const
{
    Models inputModelsByHint;
    for (const auto& model : models) {
        if(model->hint() == hint)
            inputModelsByHint << model;
    }
    return inputModelsByHint;
}
