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
        Models filterByTournamentId(const Models &models, const QUuid &id) const override;
        Models filterByPlayerId(const Models &models, const QUuid &id) const override;
        Models filterByInputHint(const Models &models, const int &hint) const override;
        Models filterByRoundIndex(const Models &models, const int &roundIndex) const override;
        Models filterByAttemptIndex(const Models &models, const int &attemptIndex) const override;
    };
}


#endif // DARTSINPUTSFILTERSERVICE_H
