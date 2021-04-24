#ifndef IPOINTVALIDATOR_H
#define IPOINTVALIDATOR_H

class IPointValidator
{
public:
    virtual int validateInput(const int &,
                              const int &,
                              const int &) const = 0;
};


#endif // IPOINTVALIDATOR_H
