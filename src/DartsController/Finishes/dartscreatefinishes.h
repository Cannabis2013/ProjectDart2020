#ifndef DARTSCREATEFINISHES_H
#define DARTSCREATEFINISHES_H

#include "dartsThresholds.h"
#include "dartsboundaries.h"
#include "dartsdivisors.h"
#include "dartsfieldvalues.h"
#include "dartsmodidentifiers.h"
#include "src/DartsController/Finishes/finishestypes.h"

#include <QMultiHash>
#include <qvector.h>

class DartsCreateFinishes
{
public:
    typedef FinishesTypes::TargetRow TargetRow;
    typedef QVector<TargetRow *> TargetRows;
    static DartsCreateFinishes *createInstance() { return new DartsCreateFinishes; }
    TargetRows *constructRows();

private:
    struct ScoreModel
    {
        QVector<char> multiplier;
        QVector<int> pointValue;
    };
    QString constructRow(const int &remainingScore, const int &turnIndex) const;
    bool suggestion(const int &remainingScore, const int &turnIndex, ScoreModel *scoreObject) const;
    bool evaluateConstraints(const int &remainingScore, const int &turnIndex, const int &totalTurns) const;
    bool isWithinTerminalThreshold(const int &remainingScore, const int &turnIndex, ScoreModel *scoreObject) const;
    bool isDivisor(int base, int div) const;
    bool determineRouteByThresholdDiff(const int &remainingScore, const int &turnIndex, ScoreModel *s) const;
    bool determineRouteByDiff(const int &remainingScore, const int &turnIndex, ScoreModel *scoreObject) const;
    bool findGreatestPointsWithinThreshold(const int &remainingScore, const int &turnIndex,
                                           const int &threshold, const int &divisor, ScoreModel *s) const;
    bool findGreatestPointsWithinTerminalThreshold(const int &remainingScore, const int &turnIndex,
                                                   const int &threshold, ScoreModel *s) const;
    bool findGreatestOddDivisibleByThree(const int &remainingScore, const int &turnIndex, ScoreModel *s) const;
    void updateScoreObject(char stringIdentifier, int value, int index, ScoreModel *s) const;
    bool writeToScoreObject(const int &remainingScore, const int &points, const int &divisor,
                            const int &turnIndex, ScoreModel *s) const;
    bool isEven(const int& integer) const;
    QString toString(ScoreModel *s) const;

    const int _terminalDivisor = 2;
    const int _attempts = 3;

    DartsBoundaries *_boundaries = new DartsBoundaries();
    DartsThresholds *_thresholds = new DartsThresholds();
    DartsFieldValues *_fieldValues = new DartsFieldValues();
    DartsDivisors *_divisors = new DartsDivisors();
    DartsModIdentifiers *_identifiers = new DartsModIdentifiers();
};
#endif // DARTSCONSTRUCTROW_H
