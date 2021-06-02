#ifndef IDARTSSCOREMODELSSERVICE_H
#define IDARTSSCOREMODELSSERVICE_H

#include "idartsscoreinput.h"
#include "idartsscoreindexes.h"
namespace DartsModelsContext {
    class IDartsScoreModelsService
    {
    public:
        typedef IModel<QUuid,QByteArray> PlayerInput;
        typedef QVector<const PlayerInput*> PlayerInputs;
        virtual const PlayerInput *dartsScoreModel(const QUuid &tournamentId,
                                                   const QUuid &playerId,
                                                   const int &roundIndex) const = 0;
        virtual QVector<const PlayerInput *> dartsScoreModelsByTournamentIdAndHint(const QUuid &tournamentId,
                                                                                   const int &hint) const = 0;
        virtual void addDartsScore(const IDartsScoreInput *pointModel) = 0 ;
        virtual void removeHiddenScores(const QUuid &tournamentId) = 0 ;
        virtual void removeScoreById(const QUuid &scoreId) = 0 ;
        virtual void removeScoresByTournamentId(const QUuid &tournamentId) = 0 ;
        virtual void removeScoreModel(const QUuid &scoreId) = 0 ;
        virtual void setDartsScoreHint(const PlayerInput* model,const int &hint) = 0 ;
        virtual const IDartsScoreIndexes *dartsScoreIndexes(const QUuid &tournamentId,
                                                            const int& assignedPlayersCount) const = 0;
        virtual int dartsScoreCount(const QUuid &tournamentId, const int &hint) const = 0;
    };
}

#endif // IDARTSSCOREMODELSSERVICE_H
