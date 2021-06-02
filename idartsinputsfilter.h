#ifndef IDARTSINPUTSFILTER_H
#define IDARTSINPUTSFILTER_H

#include "idartsinput.h"
#include <qvector.h>

namespace DartsModelsContext {
    template<typename  TBaseModel, typename TUuid>
    class IDartsInputsFilter
    {
    public:
        typedef TBaseModel Model;
        typedef QVector<const Model*> Models;
        typedef TUuid UniqueId;
        virtual Models filterByTournamentId(const Models& models, const UniqueId& id) const = 0;
        virtual Models filterByPlayerId(const Models& models, const UniqueId& tournamentId, const UniqueId& playerId) const = 0;
        virtual Models filterByHint(const Models& models,
                                    const int& hint) const = 0;
        virtual Models filterByHint(const Models& models,
                                    const UniqueId& tournamentId,
                                    const int& hint) const = 0;
        virtual Models filterByHint(const Models& models,
                                    const UniqueId& tournamentId,
                                    const UniqueId& playerId,
                                    const int& hint) const = 0;
        virtual Models filterByRoundIndex(const Models& models,
                              const UniqueId& tournamentId,
                              const UniqueId& playerId,
                              const int& roundIndex) const = 0;
        virtual const Model* filterByAttemptIndex(const Models& models,
                                           const UniqueId& tournamentId,
                                           const UniqueId& playerId,
                                           const int& roundIndex,
                                           const int &hint,
                                           const int& attemptIndex) const = 0;
    };
}

#endif // IDARTSINPUTSFILTER_H
