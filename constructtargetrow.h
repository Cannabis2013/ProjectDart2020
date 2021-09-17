#ifndef CONSTRUCTTARGETROW_H
#define CONSTRUCTTARGETROW_H

#include <QMultiHash>
#include <qvector.h>
#include "dartsconstructservices.h"
#include "idclogisticdb.h"

#include "idartsconstructrow.h"

namespace DartsSuggestionContext
{
    class ConstructTargetRow;
}

class ConstructTargetRow :
        public IDartsConstructRow,
        protected DartsConstructServices
{
public:
    static ConstructTargetRow *createInstance();
    AllTargetRows constructRows() const override;
    int attempts() const;
private:
    QString constructRow(const int &remainingScore, const int &turnIndex) const;
    bool suggestion(const int &remainingScore, const int &turnIndex, IDartsConstructRow::ScoreModel *scoreObject) const;
    bool evaluateConstraints(const int &remainingScore, const int &turnIndex, const int &totalTurns) const;
    bool isWithinTerminalThreshold(const int &remainingScore, const int &turnIndex, IDartsConstructRow::ScoreModel *scoreObject) const;
    bool isDivisor(int base, int div) const;
    bool determineRouteByThresholdDiff(const int &remainingScore, const int &turnIndex,
                                       IDartsConstructRow::ScoreModel *s) const;
    bool determineRouteByDiff(const int &remainingScore, const int &turnIndex,
                              IDartsConstructRow::ScoreModel *scoreObject) const;
    bool findGreatestPointsWithinThreshold(const int &remainingScore, const int &turnIndex,
                                           const int &threshold, const int &divisor,
                                           IDartsConstructRow::ScoreModel *s) const;
    bool findGreatestPointsWithinTerminalThreshold(const int &remainingScore, const int &turnIndex,
                                                   const int &threshold, IDartsConstructRow::ScoreModel *s) const;
    bool findGreatestOddDivisibleByThree(const int &remainingScore, const int &turnIndex, IDartsConstructRow::ScoreModel* s) const;
    void updateScoreObject(char stringIdentifier, int value, int index, IDartsConstructRow::ScoreModel *s) const;
    bool writeToScoreObject(const int &remainingScore, const int &points, const int &divisor,
                            const int &turnIndex, IDartsConstructRow::ScoreModel *s) const;
    bool isEven(const int& integer) const;
    QString toString(IDartsConstructRow::ScoreModel *s) const;
    const char identifiers[3] = {'S','D','T'};
    const int _attempts = 3;
};
#endif // CONSTRUCTTARGETROW_H
