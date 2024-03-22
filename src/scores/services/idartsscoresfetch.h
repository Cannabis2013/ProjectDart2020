#ifndef IDARTSSCORESFETCH_H
#define IDARTSSCORESFETCH_H

#include <QList>

class Score;

class IDartsScoresFetch {
public:
        virtual Score score() = 0;
        virtual Score score(const QString& name) = 0;
};

#endif // IDARTSSCORESFETCH_H
