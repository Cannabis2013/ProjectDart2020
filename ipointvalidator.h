#ifndef IPOINTVALIDATOR_H
#define IPOINTVALIDATOR_H

class IPointValidator
{
public:
    virtual int validateInput(const int &currentScore,
                              const int &keyCode = -1,
                              const int &input = -1) const = 0;
};


#endif // IPOINTVALIDATOR_H
