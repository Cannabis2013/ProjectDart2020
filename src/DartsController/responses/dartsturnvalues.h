#ifndef DARTSTURNVALUES_H
#define DARTSTURNVALUES_H

#include "src/DartsController/Finishes/idartsfinishes.h"
#include "src/DartsController/indexes/IDartsIndexes.h"
#include "src/DartsController/players/IDartsPlayers.h"
#include "src/DartsController/responses/IDartsInfoResponse.h"
#include "src/DartsController/scores/IDartsScores.h"
#include "src/DartsController/statistics/idartsstatistics.h"
#include "src/DartsController/status/IDartsStatus.h"

class DartsTurnValues : public IDartsInfoResponse {
        // IDartInfoResponse interface
public:
        DartsTurnValues(IDartsPlayers* players,
            IDartsIndexes* _indexes,
            IDartsStatistics* statistics,
            IDartsFinishes* finishes,
            IDartsScores* scores,
            IDartsStatus* status);
        virtual TurnInfo currentTurnInfo() override;

private:
        void updateWithIndexes(TurnInfo& turnInfo);
        void updateWithStatistics(TurnInfo& turnInfo);
        void updateWithPlayerName(TurnInfo& turnInfo);
        void updateWithFinish(TurnInfo& turnInfo);
        void updateWithStatus(TurnInfo& turnInfo);

        // Services
        IDartsPlayers* const _players;
        IDartsIndexes* const _indexes;
        IDartsStatistics* const _statistics;
        IDartsFinishes* const _finishes;
        IDartsScores* const _scores;
        IDartsStatus* const _status;
};

#endif // DARTSTURNVALUES_H