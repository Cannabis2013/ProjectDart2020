#ifndef FINISHCONSTRUCTOR_H
#define FINISHCONSTRUCTOR_H

#include <QMultiHash>
#include <qvector.h>

#define SINGLE_MAX 20
#define DOUBLE_MAX 40
#define TRIPPLE_MAX 60
#define SINGLE_MULTIPLIER 1
#define DOUBLE_MULTIPLIER 2
#define TRIPPLE_MULTIPLIER 3
#define ATTEMPTS 3
#define BULL 25
#define BULLS 50
#define UPPER_LIMIT 110

#define USE_IMP1

class FinishConstructor
{
public:
  typedef QMultiHash<int, QString> TargetRow;
  typedef QVector<TargetRow *> TargetRows;
  TargetRows *construct();

private:
  struct ScoreModel
  {
      QVector<char> multiplier;
      QVector<int> pointValue;
  };

    char multiplierToString(const int &divisor) const;

    QString constructRow(const int &remainingScore, const int &turnIndex) const;
    bool suggestion(const int &remainingScore, const int &turnIndex, ScoreModel *scoreObject) const;
#ifdef USE_IMP1
    bool isWithinTerminalThreshold(const int &remainingScore,
                                   const int &turnIndex,
                                   ScoreModel *scoreObject) const;
    bool determineRouteByDiff(const int &remainingScore,
                              const int &turnIndex,
                              ScoreModel *scoreObject) const;
    bool findGreatestPointsWithinThreshold(const int &remainingScore, const int &turnIndex,
                                           const int &threshold, const int &divisor, ScoreModel *s) const;
    bool findGreatestPointsWithinTerminalThreshold(const int &remainingScore, const int &turnIndex,
                                                   const int &threshold, ScoreModel *s) const;
    bool findGreatestOddDivisibleByThree(const int &remainingScore, const int &turnIndex, ScoreModel *s) const;
    bool writeToScoreObject(const int &remainingScore,
                            const int &points,
                            const int &divisor,
                            const int &turnIndex,
                            ScoreModel *scoreObject) const;
    QString toString(ScoreModel *s) const;
#endif
    bool updateScoreObject(char stringIdentifier, int value, int index, ScoreModel *s) const;

    const char identifiers[3] = {'S', 'D', 'T'};
};
#endif // DARTSCONSTRUCTROW_H
