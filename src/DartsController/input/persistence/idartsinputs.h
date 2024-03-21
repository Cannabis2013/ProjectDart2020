#ifndef IDARTINPUTS_H
#define IDARTINPUTS_H

#include "src/DartsController/input/models/input.h"
#include <QList>

class IDartsInputs {
public:
        virtual void init() = 0;
        virtual void initFromFile() = 0;
        virtual QList<Input> all() const = 0;
        virtual void setInputs(const QList<Input>& inputs) = 0;
        virtual bool saveState() = 0;
};

#endif // IDARTINPUTS_H
