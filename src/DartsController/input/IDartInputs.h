#ifndef IDARTINPUTS_H
#define IDARTINPUTS_H

#include "src/DartsController/input/dartInput.h"
class IDartInputs
{
public:
        virtual void init() = 0;
        virtual void clear() = 0;
        virtual bool save(DartInput input) = 0;
        virtual QList<DartInput> inputs() = 0;
        virtual QList<DartInput> inputs(const QString &playerName, const int& turnIndex) = 0;
};

#endif // IDARTINPUTS_H
