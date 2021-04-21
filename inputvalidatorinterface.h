#ifndef INPUTVALIDATORINTERFACE_H
#define INPUTVALIDATORINTERFACE_H

class InputValidatorInterface
{
public:
    enum InputDomains {
        PointDomain = 0x01,
        CriticalDomain = 0x02,
        OutsideDomain = 0x03,
        TargetDomain = 0x4,
        InputOutOfRange = 0x5
    };
    virtual int validateInput(const int& currentScore,
                              const int& input) const = 0;
};

#endif // INPUTVALIDATORINTERFACE_H
