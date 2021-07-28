#ifndef FTPTOURNAMENTMODELINTERFACE_H
#define FTPTOURNAMENTMODELINTERFACE_H

#include "tournament.h"

class AbstractDartsTournament : public Tournament
{
public:
    virtual int attempts() const = 0;
    virtual AbstractDartsTournament* setAttempts(const int &val) = 0;
    virtual int keyPoint() const = 0;
    virtual AbstractDartsTournament* setKeyPoint(const int &val) = 0;
    virtual int terminalKeyCode() const = 0;
    virtual AbstractDartsTournament* setTerminalKeyCode(const int &keyCode) = 0;
    virtual int displayHint() const = 0;
    virtual AbstractDartsTournament* setDisplayHint(int modelDisplayHint) = 0;
    virtual int inputHint() const = 0;
    virtual AbstractDartsTournament* setInputMode(const int &inputMode) = 0;
};

#endif // FTPTOURNAMENTMODELINTERFACE_H
