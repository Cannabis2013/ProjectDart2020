#ifndef IDARTINPUTEVALUTOR_H
#define IDARTINPUTEVALUTOR_H

#include <QString>
#include "src/input/models/inputCandidate.h"

class AbstractDartsEvaluator {
public:
    virtual void init() {};
    virtual void updateAllowance(const QString &name, const bool &allowance)
    {
        Q_UNUSED(name);
        Q_UNUSED(allowance);
    }
    virtual const QList<InputCandidate> acceptedInputs(const QList<InputCandidate> &candidates) = 0;
    virtual void evaluateWinnerCondition() = 0;

protected:
    typedef QList<InputCandidate> Candidates;
};

#endif // IDARTINPUTEVALUTOR_H
