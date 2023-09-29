#ifndef DARTSCREATEFINISHES_H
#define DARTSCREATEFINISHES_H

#include <QMultiHash>
#include <DartsController/Contracts/Finishes/idartscreatefinishes.h>
#include <DartsController/LocalDartsController/Finishes/dartsboundaries.h>
#include <DartsController/LocalDartsController/Finishes/dartsdefaultattempts.h>
#include <DartsController/LocalDartsController/Finishes/dartsdivisors.h>
#include <DartsController/LocalDartsController/Finishes/dartsfieldvalues.h>
#include <DartsController/LocalDartsController/Finishes/dartsmodidentifiers.h>
#include <DartsController/LocalDartsController/Finishes/dartsterminaldivisor.h>
#include <DartsController/LocalDartsController/Finishes/defaultthresholds.h>
#include <qvector.h>

class DartsCreateFinishes: public IDartsCreateFinishes
{
public:
    static DartsCreateFinishes *createInstance() {return new DartsCreateFinishes;}
    TargetRows constructRows() const override;
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

    IDartsBoundaries *_boundaries = new DartsBoundaries();
    IDartsThresholds *_thresholds = new DefaultThresholds();
    IDartsFieldValues *_fieldValues = new DartsFieldValues();
    IDartsDivisorValues *_divisors = new DartsDivisors();
    IDartsterminalDivisor *_terminalDivisor = new DartsTerminalDivisor();
    IDartsModIdentifiers *_identifiers = new DartsModIdentifiers();
    IDartsAttemptsService *_attempts = new DartsDefaultAttempts();
};
#endif // DARTSCONSTRUCTROW_H
