#ifndef IDARTINPUTEVALUTOR_H
#define IDARTINPUTEVALUTOR_H

#include "src/DartsController/input/dartInput.h"

class IDartInputEvaluator
{
public:
        virtual bool isValid(const DartInput &input) = 0; // Should check if input values is valid
        virtual bool isWithinBounds(const DartInput &input) = 0; // Should check if score is within bounds
};

#endif // IDARTINPUTEVALUTOR_H
