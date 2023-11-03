#ifndef DARTSTURNVALUES_H
#define DARTSTURNVALUES_H

#include "src/DartsController/Finishes/idartsfinishes.h"
#include "src/DartsController/indexes/idartsindexes.h"
#include "src/DartsController/players/idartsplayers.h"
#include "src/DartsController/responses/idartsinforesponse.h"
#include "src/DartsController/scores/idartsscores.h"
#include "src/DartsController/statistics/idartsstatistics.h"
#include "src/DartsController/status/idartsstatus.h"

class DartsTurnValues : public IDartsInfoResponse {
        // IDartInfoResponse interface
public:
        DartsTurnValues(IDartsPlayers* players,
            IDartsIndexes* _indexes,
            IDartsStatistics* statistics,
            IDartsFinishes* finishes,
            IDartsScores* scores,
            IDartsStatus* status);
        QByteArray currentTurnInfo() override;

private:
        QJsonArray playerScores();
        QJsonObject turnIndex();
        QJsonArray statistics();
        QJsonObject finish();
        // Services
        IDartsPlayers* const _players;
        IDartsIndexes* const _indexes;
        IDartsStatistics* const _statistics;
        IDartsFinishes* const _finishes;
        IDartsScores* const _scores;
        IDartsStatus* const _status;
};

#endif // DARTSTURNVALUES_H
