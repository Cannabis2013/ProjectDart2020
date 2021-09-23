#ifndef IDARTSINPUTVALIDATOR_H
#define IDARTSINPUTVALIDATOR_H

class IDartsInputValidator
{
public:
    virtual int validateInput(const int &currentScore,
                              const int &keyCode,
                              const int &point) const = 0;
};


#endif // IPOINTVALIDATOR_H
