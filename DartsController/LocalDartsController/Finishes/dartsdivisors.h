#ifndef DARTSDIVISORS_H
#define DARTSDIVISORS_H

#include <DartsController/Contracts/Finishes/idartsdivisorvalues.h>

class DartsDivisors : public IDartsDivisorValues
{
public:
        virtual int trippleDivisor() const override
        {
                return _trippleDivisor;
        }
        virtual int doubleDivisor() const override
        {
                return _doubleDivisor;
        }
        virtual int singleDivisor() const override
        {
                return _singleDivisor;
        }
private:
        const int _singleDivisor = 1;
        const int _doubleDivisor = 2;
        const int _trippleDivisor = 3;
};
#endif // DARTSDIVISORS_H
