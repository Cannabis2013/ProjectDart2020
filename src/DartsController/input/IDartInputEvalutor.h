#ifndef IDARTINPUTEVALUTOR_H
#define IDARTINPUTEVALUTOR_H

#include "src/DartsController/input/DartsInput.h"

class IDartInputEvaluator
{
public:
    virtual bool isValid(const DartsInput &input) = 0; // Should check if input values is valid
    virtual bool isWithinBounds(const DartsInput &input) = 0; // Should check if score is within bounds
};

#endif // IDARTINPUTEVALUTOR_H
