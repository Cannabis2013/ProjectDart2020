#ifndef IDARTSREMAININGS_H
#define IDARTSREMAININGS_H

#include "src/input/dartsinput.h"
class QString;
class DartsPlayerScores;

class IDartsRemainings {
public:
        virtual bool saveState() = 0;
        virtual void initFromStorage() = 0;
        virtual int initialRemaining() const = 0;
        virtual void setInitialRemaining(const int& initialScore) = 0;
        virtual int fromPlayerName(const QString &name) const = 0;
        virtual int calculateRemaining(const QList<DartsInput> &inputs) const = 0;
        virtual int inputValue(const DartsInput &input) const = 0;
};

#endif // IDARTSREMAININGS_H
