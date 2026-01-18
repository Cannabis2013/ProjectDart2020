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

class FinishConstructor
{
public:
  typedef QMultiHash<int, QString> Finish;
  typedef QVector<Finish *> Finishes;
  Finishes *construct();

private:
  struct ScoreModel
  {
      QVector<char> multiplier;
      QVector<int> pointValue;
  };

    char multiplierToString(const int &divisor) const;

    QString constructRow(const int &remainingScore, const int &turnIndex) const;
    bool suggestion(const int &remainingScore, const int &turnIndex, ScoreModel *scoreObject) const;
    bool updateScoreObject(char stringIdentifier, int value, int index, ScoreModel *s) const;

    const char identifiers[3] = {'S', 'D', 'T'};
};
#endif // DARTSCONSTRUCTROW_H
