#ifndef DARTSINPUTSFILTERSERVICE_H
#define DARTSINPUTSFILTERSERVICE_H

#include "idartsinputsfilter.h"
#include "idartspointinput.h"

namespace DartsModelsContext {
    class DartsInputsFilterService : public
            IDartsInputsFilter<IPlayerInput,QUuid>
    {
    public:
        enum ModelDisplayHint{
            HiddenHint = 0x1,
            DisplayHint = 0x2,
            AllHints = 0x3
        };
        typedef IDartsInputsFilter<IDartsInput,QUuid> FilterService;
        Models filterByTournamentId(const Models &models, const UniqueId &id) const override;
        Models filterByPlayerId(const Models &models, const UniqueId &tournamentId, const UniqueId &playerId) const override;
        Models filterByHint(const Models &models, const int &hint) const override;
        Models filterByHint(const Models &models, const UniqueId &tournamentId, const int &hint) const override;
        Models filterByHint(const Models &models, const UniqueId &tournamentId, const UniqueId &playerId, const int &hint) const override;
        Models filterByRoundIndex(const Models &models, const UniqueId &tournamentId, const UniqueId &playerId, const int &roundIndex) const override;
        const Model* filterByAttemptIndex(const Models &models, const UniqueId &tournamentId, const UniqueId &playerId, const int &roundIndex, const int &hint, const int &attemptIndex) const override;
    };
}


#endif // DARTSINPUTSFILTERSERVICE_H
