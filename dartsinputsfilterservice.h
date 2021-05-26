#ifndef DARTSINPUTSFILTERSERVICE_H
#define DARTSINPUTSFILTERSERVICE_H

#include "idartsinputsfilter.h"
#include "idartspointinput.h"

namespace DartsModelsContext {
    class DartsInputsFilterService : public
            IDartsInputsFilter<IDartsInput,QUuid>
    {
    public:
        typedef IDartsInputsFilter<IDartsInput,QUuid> FilterService;

        // IDartsInputsFilter interface
    public:
        Models filterByTournamentId(const Models &models, const UniqueId &id) const override;
        Models filterByPlayerId(const Models &models, const UniqueId &tournamentId, const UniqueId &playerId) const override;
        Models filterByHint(const Models &models, const UniqueId &tournamentId, const int &hint) const override;
        Models filterByHint(const Models &models, const UniqueId &tournamentId, const UniqueId &playerId, const int &hint) const override;
        Models filterByRoundIndex(const Models &models, const UniqueId &tournamentId, const UniqueId &playerId, const int &roundIndex) const override;
        Models filterByAttemptIndex(const Models &models, const UniqueId &tournamentId, const UniqueId &playerId, const int &roundIndex, const int &hint, const int &attemptIndex) const override;
    };
}


#endif // DARTSINPUTSFILTERSERVICE_H
