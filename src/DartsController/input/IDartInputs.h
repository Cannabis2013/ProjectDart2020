#ifndef IDARTINPUTS_H
#define IDARTINPUTS_H

#include "src/DartsController/input/DartsInput.h"
class IDartInputs
{
public:
        virtual void init() = 0;
        virtual void clear() = 0;
        virtual bool save(DartsInternalInput input) = 0;
        virtual QList<DartsInput> inputs() = 0;
        virtual QList<DartsInput> inputs(const QString &playerName, const int& turnIndex) = 0;
};

#endif // IDARTINPUTS_H
