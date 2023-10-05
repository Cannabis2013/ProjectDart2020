#ifndef IDARTSSCORES_H
#define IDARTSSCORES_H

#include "src/DartsController/input/dartInput.h"
#include "src/DartsController/scores/DartsScore.h"

class IDartsScores
{
public:
        virtual void reset() = 0;
        virtual void init(const int &playersCount) = 0;
        virtual void init() = 0;
        virtual DartsScore update(DartInput input) = 0;
        virtual DartsScore update() = 0;
        virtual DartsScore score() = 0;
        virtual QVector<int> scores() = 0;
};

#endif // IDARTSSCORES_H
