#ifndef IDARTSDIVISORVALUES_H
#define IDARTSDIVISORVALUES_H

class IDartsDivisorValues
{
public:
    virtual int trippleDivisor() const = 0;
    virtual int doubleDivisor() const = 0;
    virtual int singleDivisor() const = 0;
};
#endif // IDARTSDIVISORVALUES_H
