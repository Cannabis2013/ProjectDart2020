#ifndef DARTSCREATEFINISHES_H
#define DARTSCREATEFINISHES_H

#include <QMultiHash>
#include <qvector.h>
#include "DartsController/DCFinishesSLAs/dartsconstructslas.h"
#include "DartsController/DCFinishesSLAs/idartsfinishesdb.h"
#include "DartsController/DCFinishesSLAs/idartscreatefinishes.h"

class DartsCreateFinishes:
        public IDartsCreateFinishes,
        protected DartsConstructSLAs
{
public:
    static DartsCreateFinishes *createInstance();
    AllTargetRows constructRows() const override;
private:
    QString constructRow(const int &remainingScore, const int &turnIndex) const;
    bool suggestion(const int &remainingScore, const int &turnIndex, IDartsCreateFinishes::ScoreModel *scoreObject) const;
    bool evaluateConstraints(const int &remainingScore, const int &turnIndex, const int &totalTurns) const;
    bool isWithinTerminalThreshold(const int &remainingScore, const int &turnIndex, IDartsCreateFinishes::ScoreModel *scoreObject) const;
    bool isDivisor(int base, int div) const;
    bool determineRouteByThresholdDiff(const int &remainingScore, const int &turnIndex,
                                       IDartsCreateFinishes::ScoreModel *s) const;
    bool determineRouteByDiff(const int &remainingScore, const int &turnIndex,
                              IDartsCreateFinishes::ScoreModel *scoreObject) const;
    bool findGreatestPointsWithinThreshold(const int &remainingScore, const int &turnIndex,
                                           const int &threshold, const int &divisor,
                                           IDartsCreateFinishes::ScoreModel *s) const;
    bool findGreatestPointsWithinTerminalThreshold(const int &remainingScore, const int &turnIndex,
                                                   const int &threshold, IDartsCreateFinishes::ScoreModel *s) const;
    bool findGreatestOddDivisibleByThree(const int &remainingScore, const int &turnIndex, IDartsCreateFinishes::ScoreModel* s) const;
    void updateScoreObject(char stringIdentifier, int value, int index, IDartsCreateFinishes::ScoreModel *s) const;
    bool writeToScoreObject(const int &remainingScore, const int &points, const int &divisor,
                            const int &turnIndex, IDartsCreateFinishes::ScoreModel *s) const;
    bool isEven(const int& integer) const;
    QString toString(IDartsCreateFinishes::ScoreModel *s) const;
};
#endif // DARTSCONSTRUCTROW_H
