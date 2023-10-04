#ifndef IDARTSSCORES_H
#define IDARTSSCORES_H

#include "src/DartsController/input/dartInput.h"
#include "src/DartsController/scores/dartScore.h"

class IDartsScores
{
public:
        virtual void reset() = 0;
        virtual void init(const int &playersCount) = 0;
        virtual DartScore update(DartInput input) = 0;
        virtual DartScore update() = 0;
        virtual int score() = 0;
        virtual QVector<int> scores() = 0;
};

#endif // IDARTSSCORES_H
