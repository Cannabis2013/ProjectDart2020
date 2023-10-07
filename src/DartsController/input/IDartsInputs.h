#ifndef IDARTINPUTS_H
#define IDARTINPUTS_H

#include "src/DartsController/input/Input.h"

class IDartsInputs
{
public:
        virtual void init() = 0;
        virtual void clear() = 0;
        virtual bool save(Input input) = 0;
        virtual QList<Input> inputs(const QString &playerName, const int& turnIndex) = 0;
};

#endif // IDARTINPUTS_H
