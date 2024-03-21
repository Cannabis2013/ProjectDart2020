#ifndef IDARTSSCORES_H
#define IDARTSSCORES_H

#include "src/DartsController/scores/models/Score.h"

class QString;
class DartsPlayerScore;
class DartsPlayerScores;

class IDartsScores {
public:
        virtual bool saveState() = 0;
        virtual void initFromStorage() = 0;
        virtual int initialScore() const = 0;
        virtual void setInitialScore(const int& initialScore) = 0;
        virtual QList<Score> all() = 0;
        virtual void setScores(const QList<Score>& scores) = 0;
};

#endif // IDARTSSCORES_H
