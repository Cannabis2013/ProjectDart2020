#ifndef IDARTSFINISHES_H
#define IDARTSFINISHES_H

#include <qstring.h>

class IDartsFinishes {
public:
        virtual QString suggestTargetRow(const int& remainingScore, const int& turnIndex) const = 0;
};

#endif // IDARTSFINISHES_H
