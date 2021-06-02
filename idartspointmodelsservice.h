#ifndef IDARTSPOINTMODELSSERVICE_H
#define IDARTSPOINTMODELSSERVICE_H

#include "idartsinput.h"
#include "idartspointindexes.h"

namespace DartsModelsContext {
    class IDartsPointModelsService
    {
    public:
        typedef IPlayerInput PlayerInput;
        typedef QVector<const PlayerInput*> PlayerInputs;
        virtual const PlayerInput* dartsPointModel(const QUuid& tournamentId,
                                                   const QUuid& playerId,
                                                   const int& roundIndex,
                                                   const int& attemptIndex) const = 0;
        virtual PlayerInputs dartsPointModelsByTournamentId(const QUuid& tournamentId) const = 0;
        virtual QVector<const PlayerInput*> sortDartsPointsByIndexes(const QVector<const PlayerInput*>& models) const = 0;
        virtual const IDartsPointIndexes* dartsPointIndexes(const QVector<const IDartsInput*>& models,
                                                            const int& totalInputModelsCount,
                                                            const int& assignedPlayersCount) const = 0;
        virtual void addDartsPoint(const PlayerInput*) = 0;
        virtual PlayerInputs getDartsPointModelsOrdedByIndexes(const QUuid& tournamentId) const = 0;
        virtual const PlayerInput* getDartsPointModelById(const QUuid& id) const = 0;
        virtual int dartsPointsCount(const QUuid&,const int&) const = 0;
        virtual void setDartsPointHint(const PlayerInput* inputModel,const int& hint) = 0;
        virtual void removePointById(const QUuid&) = 0;
        virtual void removeHiddenPoints(const QUuid&) = 0;
        virtual void removePointsByTournamentId(const QUuid&) = 0;
    };
}

#endif // IDARTSPOINTMODELSSERVICE_H
