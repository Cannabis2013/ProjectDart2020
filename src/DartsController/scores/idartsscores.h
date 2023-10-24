#ifndef IDARTSSCORES_H
#define IDARTSSCORES_H

#include "src/DartsController/scores/DartsPlayerScores.h"
#include "src/DartsController/scores/dartsPlayerScore.h"

class IDartsScores
{
public:
        virtual void init() = 0;
        virtual void initFromFile() = 0;
        virtual bool saveState() = 0;
        virtual int initialScore() const = 0;
        virtual DartsPlayerScores update() = 0;
        virtual DartsPlayerScore score() = 0;
        virtual DartsPlayerScore score(const QString& name) = 0;
        virtual DartsPlayerScores scores() = 0;
};

#endif // IDARTSSCORES_H
