#ifndef DARTSMESSAGESREPORT_H
#define DARTSMESSAGESREPORT_H

#include "imessagesreport.h"

class IDartsIndexes;
class IDartsScores;
class IDartsFinishes;
class Message;

class DartsMessagesReport : public IMessagesReport {
public:
        DartsMessagesReport(IDartsFinishes* finishes,
            IDartsScores* scores, IDartsIndexes* indexes);

        QJsonArray report() const;

private:
        Message messageTargetRow() const;
        Message scoreDiff() const;

        // Services
        IDartsFinishes* const _finishes;
        IDartsScores* const _scores;
        IDartsIndexes* const _indexes;
};

#endif // DARTSMESSAGESREPORT_H
