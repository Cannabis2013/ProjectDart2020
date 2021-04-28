#ifndef FTPTOURNAMENTMODELINTERFACE_H
#define FTPTOURNAMENTMODELINTERFACE_H

#include "itournament.h"

template<class TUuid,class TList, class TString>
class IDartsTournament : public ITournament<TUuid,TList,TString>
{
public:
    virtual IDartsTournament<TUuid,TList,TString>* setTitle(const TString &string) = 0;
    virtual int attempts() const = 0;

    virtual IDartsTournament<TUuid,TList,TString>* setAttempts(const int &val) = 0;

    virtual IDartsTournament<TUuid,TList,TString>* setAssignedPlayerIdentities(const TList &playerIdentities) = 0;

    virtual int keyPoint() const = 0;
    virtual IDartsTournament* setKeyPoint(const int &val) = 0;

    virtual int terminalKeyCode() const = 0;
    virtual IDartsTournament* setTerminalKeyCode(const int &keyCode) = 0;

    virtual int displayHint() const = 0;
    virtual IDartsTournament* setDisplayHint(int modelDisplayHint) = 0;

    virtual int inputHint() const = 0;
    virtual IDartsTournament* setInputMode(const int &inputMode) = 0;
};

#endif // FTPTOURNAMENTMODELINTERFACE_H
