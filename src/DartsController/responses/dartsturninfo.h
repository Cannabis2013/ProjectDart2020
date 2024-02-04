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
public:
        DartsTurnInfo(IDartsPlayers* players,
            IDartsIndexes* _indexes,
            IDartsFinishes* finishes,
            IDartsScores* scores,
            IDartsStatus* status,
            IDartsStatistics* statistics);
        QByteArray report() override;

private:
        QJsonArray playerScores();
        QJsonObject turnInfo();
        QJsonObject winnerInfo();
        QJsonArray statsInfo();
        QJsonObject finish();
        // Services
        IDartsPlayers* const _players;
        IDartsIndexes* const _indexes;
        IDartsFinishes* const _finishes;
        IDartsScores* const _scores;
        IDartsStatus* const _status;
        IDartsStatistics* const _statistics;
};

#endif // DARTSTURNINFO_H
