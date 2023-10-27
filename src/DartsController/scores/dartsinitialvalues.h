#ifndef DARTSINITIALVALUES_H
#define DARTSINITIALVALUES_H

#include "src/DartsController/scores/Score.h"
class DartsInitialValues {
public:
        DartsInitialValues(const QList<Score>& scores, int initialScore)
            : _scores(scores)
            , _initialScore(initialScore)
        {
        }

        DartsInitialValues()
        {
        }

        QList<Score> scores() const
        {
                return _scores;
        }

        int initialScore() const
        {
                return _initialScore;
        }

private:
        QList<Score> _scores;
        int _initialScore;
};
#endif // DARTSINITIALVALUES_H
