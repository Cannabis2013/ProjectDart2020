#ifndef IDARTINPUTS_H
#define IDARTINPUTS_H

#include "src/input/models/dartsinput.h"
#include <QList>

class IDartsInputs {
public:
        virtual void init() = 0;
        virtual void initFromFile() = 0;
        virtual QList<DartsInput> all() const = 0;
        virtual void setInputs(const QList<DartsInput>& inputs) = 0;
        virtual bool saveState() = 0;
};

#endif // IDARTINPUTS_H
