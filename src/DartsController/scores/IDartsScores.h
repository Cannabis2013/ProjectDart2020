#ifndef IDARTSSCORES_H
#define IDARTSSCORES_H

#include "src/DartsController/input/Input.h"
#include "src/DartsController/scores/DartsPlayerScores.h"
#include "src/DartsController/scores/dartsPlayerScore.h"

class IDartsScores
{
public:
        virtual void reset() = 0;
        virtual void init() = 0;
        virtual void initFromFile() = 0;
        virtual bool saveState() = 0;
        virtual DartsPlayerScore update(const Input &input) = 0;
        virtual DartsPlayerScores update() = 0;
        virtual DartsPlayerScore score() = 0;
        virtual DartsPlayerScores scores() = 0;
};

#endif // IDARTSSCORES_H
