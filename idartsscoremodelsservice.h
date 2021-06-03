#ifndef IDARTSSCOREMODELSSERVICE_H
#define IDARTSSCOREMODELSSERVICE_H

#include "idartsscoreinput.h"
#include "idartsscoreindexes.h"
namespace DartsModelsContext {
    template<typename TDbModelsService>
    class IDartsScoreModelsService
    {
    public:
        typedef TDbModelsService DbModelsService;
        typedef IPlayerInput PlayerInput;
        typedef QVector<const PlayerInput*> PlayerInputs;
        virtual const PlayerInput* dartsScoreModel(const QUuid& tournamentId,
                                                   const QUuid& playerId,
                                                   const int& roundIndex,
                                                   const DbModelsService* dbService) const = 0;
        virtual void setDartsScoreHint(const PlayerInput* model,const int &hint, DbModelsService* dbService) = 0 ;
        virtual const IDartsScoreIndexes *dartsScoreIndexes(const QUuid &tournamentId,
                                                            const int& assignedPlayersCount,
                                                            const DbModelsService* dbService) const = 0;
        };
}

#endif // IDARTSSCOREMODELSSERVICE_H
