#ifndef DARTSJSONREPORT_H
#define DARTSJSONREPORT_H

#include "src/DartsController/jsonReport/idartsjsonreport.h"

class IMessagesReport;
class IStatusReport;
class IScoresReport;
class IStatsReport;
class DartsMessagesReport;
class DartsStatusReport;
class IScoresCalculator;
class IDartsIndexes;
class IDartsFinishes;
class IDartsPlayers;
class IDartsStatus;
class IDartsScores;
class QJsonArray;
class QJsonObject;
class IDartsInputs;
class MessageTargetRow;

class DartsJsonReport : public IDartsJsonReport {
public:
        DartsJsonReport(IStatsReport* statsReport,
            IScoresReport* scoresReport,
            IStatusReport* statusReport,
            IMessagesReport* messagesReport);

        QByteArray report() override;

private:
        // Services
        IStatsReport* const _statsReport;
        IScoresReport* const _scoresReport;
        IStatusReport* const _statusReport;
        IMessagesReport* const _messagesReport;
};

#endif // DARTSJSONREPORT_H
