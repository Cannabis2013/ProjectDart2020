#ifndef FTPTOURNAMENTMODELINTERFACE_H
#define FTPTOURNAMENTMODELINTERFACE_H

#include "itournament.h"

template<class TUuid,class TList, class TString>
class IFTPTournament : public ITournament<TUuid,TList,TString>
{
public:
    virtual IFTPTournament<TUuid,TList,TString>* setTitle(const TString &string) = 0;
    virtual int attempts() const = 0;

    virtual IFTPTournament<TUuid,TList,TString>* setAttempts(const int &val) = 0;

    virtual IFTPTournament<TUuid,TList,TString>* setAssignedPlayerIdentities(const TList &playerIdentities) = 0;

    virtual int keyPoint() const = 0;
    virtual IFTPTournament* setKeyPoint(const int &val) = 0;

    virtual int terminalKeyCode() const = 0;
    virtual IFTPTournament* setTerminalKeyCode(const int &keyCode) = 0;

    virtual int displayHint() const = 0;
    virtual IFTPTournament* setDisplayHint(int modelDisplayHint) = 0;

    virtual int inputHint() const = 0;
    virtual IFTPTournament* setInputMode(const int &inputMode) = 0;
};

#endif // FTPTOURNAMENTMODELINTERFACE_H
