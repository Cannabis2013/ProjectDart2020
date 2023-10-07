#ifndef IDARTINPUTEVALUTOR_H
#define IDARTINPUTEVALUTOR_H

#include <qstring.h>

class IDartInputEvaluator
{
public:
    virtual bool isValid(const QString &mod, const int &point) = 0; // Should check if input values is valid
    virtual bool isWithinBounds(const QString &mod, const int &point) = 0; // Should check if score is within bounds
};

#endif // IDARTINPUTEVALUTOR_H
