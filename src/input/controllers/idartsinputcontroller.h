#ifndef IDARTSINPUTCONTROLLER_H
#define IDARTSINPUTCONTROLLER_H

#include "src/validation/abstractdartsevaluator.h"
#include <qstring.h>

class IDartsInputController {
public:
        virtual void add(const QString& mod, const int& point) = 0;
};

#endif // IDARTSINPUTCONTROLLER_H
