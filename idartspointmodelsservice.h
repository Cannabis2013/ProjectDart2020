#ifndef IDARTSPOINTMODELSSERVICE_H
#define IDARTSPOINTMODELSSERVICE_H

#include "idartsinput.h"
#include "idartspointindexes.h"

namespace DartsModelsContext {
    template<typename TDbService>
    class IDartsPointModelsService
    {
    public:
        typedef TDbService DbServiceInterface;
        typedef IPlayerInput PlayerInput;
        typedef QVector<const PlayerInput*> PlayerInputs;
        virtual const PlayerInput* dartsPointModel(const QUuid& tournamentId,
                                                   const QUuid& playerId,
                                                   const int& roundIndex,
                                                   const int& attemptIndex,
                                                   const DbServiceInterface* dbService) const = 0;
        virtual const IDartsPointIndexes* dartsPointIndexes(const QVector<const PlayerInput*>& models,
                                                            const int& totalInputModelsCount,
                                                            const int& assignedPlayersCount) const = 0;
        virtual void setDartsPointHint(const PlayerInput* inputModel,const int& hint,
                                       DbServiceInterface* dbService) = 0;
    };
}

#endif // IDARTSPOINTMODELSSERVICE_H
