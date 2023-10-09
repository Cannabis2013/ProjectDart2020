#ifndef IDARTINPUTS_H
#define IDARTINPUTS_H

#include "src/DartsController/input/Input.h"
#include "src/DartsController/input/InputRequest.h"

class IDartsInputs
{
public:
        virtual void init() = 0;
        virtual void initFromFile() = 0;
        virtual Input evaluateAndAdd(const InputRequest &req) = 0;
        virtual QList<Input> inputs(const QString& playerName) const = 0;
        virtual void chop() = 0;
        virtual bool saveState() = 0;
};

#endif // IDARTINPUTS_H
