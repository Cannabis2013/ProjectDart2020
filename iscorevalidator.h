#ifndef INPUTVALIDATORINTERFACE_H
#define INPUTVALIDATORINTERFACE_H

class IScoreValidator
{
public:
    virtual int validateInput(const int&) const = 0;
};

#endif // INPUTVALIDATORINTERFACE_H
