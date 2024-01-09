#ifndef IDARTSINPUTADDER_H
#define IDARTSINPUTADDER_H

#include "src/DartsController/validation/abstractdartsevaluator.h"
#include <qstring.h>

class IDartsInputAdder {
public:
        virtual void add(const QString& mod, const int& point) = 0;
        virtual void setEvaluator(AbstractDartsEvaluator** evaluatorRef) = 0;
};

#endif // IDARTSINPUTADDER_H
