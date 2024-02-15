#ifndef DARTSJSONREPORT_H
#define DARTSJSONREPORT_H

#include "src/DartsController/jsonReport/idartsjsonreport.h"

class DartsMessagesReport;
class DartsTurnReport;
class IScoresCalculator;
class IDartsIndexes;
class IDartsFinishes;
class IDartsPlayers;
class DartsStatsReport;
class IDartsStatus;
class IDartsScores;
class QJsonArray;
class QJsonObject;
class IDartsInputs;
class MessageTargetRow;

class DartsJsonReport : public IDartsJsonReport {
public:
        DartsJsonReport(IDartsPlayers* players,
            IDartsIndexes* _indexes,
            IDartsFinishes* finishes,
            IDartsScores* scores,
            IDartsStatus* status,
            IDartsInputs* inputs,
            IScoresCalculator* calculator);
        QByteArray report() override;

private:
        QJsonObject winnerInfo();
        // Services
        IDartsPlayers* const _players;
        IDartsScores* const _scores;
        IDartsStatus* const _status;
        DartsStatsReport* _statsReport;
        DartsTurnReport* _turnReport;
        DartsMessagesReport* _messageReport;
};

#endif // DARTSJSONREPORT_H
