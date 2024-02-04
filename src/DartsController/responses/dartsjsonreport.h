#ifndef DARTSJSONREPORT_H
#define DARTSJSONREPORT_H

#include "src/DartsController/responses/idartsjsonreport.h"

class IDartsIndexes;
class IDartsFinishes;
class IDartsPlayers;
class IDartsStatistics;
class IDartsStatus;
class IDartsScores;
class QJsonArray;
class QJsonObject;

class MessageTargetRow;

class DartsJsonReport : public IDartsJsonReport {
public:
        DartsJsonReport(IDartsPlayers* players,
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
        QJsonArray messages();
        MessageTargetRow messageTargetRow();
        // Services
        IDartsPlayers* const _players;
        IDartsIndexes* const _indexes;
        IDartsFinishes* const _finishes;
        IDartsScores* const _scores;
        IDartsStatus* const _status;
        IDartsStatistics* const _statistics;
};

#endif // DARTSJSONREPORT_H
