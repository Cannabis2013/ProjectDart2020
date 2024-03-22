#ifndef IDARTINPUTEVALUTOR_H
#define IDARTINPUTEVALUTOR_H

#include <QString>

class AbstractDartsEvaluator {
public:
        virtual void init() {};
        virtual void updateAllowance(const QString& name, const bool& allowance)
        {
                Q_UNUSED(name);
                Q_UNUSED(allowance);
        }
        virtual bool evaluateInput(const QString& mod, const int& point) = 0;
        virtual void evaluateWinnerCondition() = 0;
};

#endif // IDARTINPUTEVALUTOR_H
