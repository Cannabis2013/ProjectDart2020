#ifndef IDARTINPUTEVALUTOR_H
#define IDARTINPUTEVALUTOR_H

#include <QString>
#include "src/input/models/inputCandidate.h"

class IClosureFilter {
public:
    virtual void init(bool enabled) = 0;
    virtual void initFromFile() = 0;
    virtual void saveState() = 0;
    virtual const QList<InputCandidate> filter(const QList<InputCandidate> &candidates) = 0;
    virtual void evaluateWinnerCondition() = 0;
};

#endif // IDARTINPUTEVALUTOR_H
