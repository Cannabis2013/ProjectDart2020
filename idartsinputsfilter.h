#ifndef IDARTSINPUTSFILTER_H
#define IDARTSINPUTSFILTER_H

#include "idartsinput.h"
#include <qvector.h>

namespace DartsModelsContext {
    template<typename  TBaseModel, typename TUuid>
    class IDartsInputsFilter
    {
    public:
        typedef QVector<const TBaseModel*> Models;
        virtual Models filterByTournamentId(const Models& models, const TUuid& id) const = 0;
        virtual Models filterByPlayerId(const Models& models, const TUuid& id) const = 0;
        virtual Models filterByInputHint(const Models& models, const int& hint) const = 0;
        virtual Models filterByRoundIndex(const Models& models, const int& roundIndex) const = 0;
        virtual Models filterByAttemptIndex(const Models& models, const int& attemptIndex) const = 0;
    };
}

#endif // IDARTSINPUTSFILTER_H
