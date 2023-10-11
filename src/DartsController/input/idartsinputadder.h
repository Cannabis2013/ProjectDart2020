#ifndef IDARTSINPUTADDER_H
#define IDARTSINPUTADDER_H

#include <qstring.h>

class IDartsInputAdder {
public:
        virtual void add(const QString& mod, const int& point) = 0;
};

#endif // IDARTSINPUTADDER_H
