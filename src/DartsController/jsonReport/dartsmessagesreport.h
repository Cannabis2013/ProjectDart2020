#ifndef DARTSMESSAGESREPORT_H
#define DARTSMESSAGESREPORT_H

// QTC_TEMP

class IDartsIndexes;
class IDartsScores;
class IDartsFinishes;
class MessageTargetRow;
class QJsonArray;

class DartsMessagesReport {
public:
        DartsMessagesReport(IDartsFinishes* finishes,
            IDartsScores* scores, IDartsIndexes* indexes);

        QJsonArray report() const;

private:
        MessageTargetRow messageTargetRow() const;

        // Services
        IDartsFinishes* const _finishes;
        IDartsScores* const _scores;
        IDartsIndexes* const _indexes;
};

#endif // DARTSMESSAGESREPORT_H
