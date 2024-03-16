#ifndef IDARTSSCORES_H
#define IDARTSSCORES_H

#include <QList>

class Score;
class QString;
class DartsPlayerScore;
class DartsPlayerScores;

class IDartsScores {
public:
        virtual void init(const int& initialScore = 501) = 0;
        virtual void initFromFile() = 0;
        virtual void reset() = 0;
        virtual bool saveState() = 0;
        virtual int initialScore() const = 0;
        virtual void update() = 0;
        virtual Score score() = 0;
        virtual Score score(const QString& name) = 0;
        virtual QList<Score> scores() = 0;
};

#endif // IDARTSSCORES_H
