#ifndef IDARTINPUTEVALUTOR_H
#define IDARTINPUTEVALUTOR_H

#include <QString>

class IDartsEvaluator {
public:
        virtual void init() = 0;
        virtual bool evaluateInput(const QString& mod, const int& point) = 0;
        virtual void evaluateScoreCondition() = 0;
};

#endif // IDARTINPUTEVALUTOR_H
