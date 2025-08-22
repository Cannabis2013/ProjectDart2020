#ifndef IDARTSSCORES_H
#define IDARTSSCORES_H

#include "src/input/models/dartsinput.h"
class QString;
class DartsPlayerScores;

class IDartsScores {
public:
        virtual bool saveState() = 0;
        virtual void initFromStorage() = 0;
        virtual int initialScore() const = 0;
        virtual void setInitialScore(const int& initialScore) = 0;
        virtual int playerScore(const QString& name) const = 0;
        virtual int calcScore(const QList<DartsInput> &inputs) const = 0;
        virtual int calcScore(const DartsInput &input) const = 0;
        virtual int calcRemaining(const DartsInput &input, const int &current) = 0;
};

#endif // IDARTSSCORES_H
