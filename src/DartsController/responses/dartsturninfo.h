#ifndef DARTSTURNINFO_H
#define DARTSTURNINFO_H

#include "src/DartsController/Finishes/idartsfinishes.h"
#include "src/DartsController/indexes/idartsindexes.h"
#include "src/DartsController/players/idartsplayers.h"
#include "src/DartsController/responses/idartsturninfo.h"
#include "src/DartsController/scores/idartsscores.h"
#include "src/DartsController/statistics/idartsstatistics.h"
#include "src/DartsController/status/idartsstatus.h"

class DartsTurnInfo : public IDartsTurnInfo {
        // IDartInfoResponse interface
public:
        DartsTurnInfo(IDartsPlayers* players,
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

#endif // DARTSTURNINFO_H
