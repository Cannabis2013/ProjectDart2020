#ifndef FTPTOURNAMENTMODELINTERFACE_H
#define FTPTOURNAMENTMODELINTERFACE_H

#include "modelinterface.h"

template<class TUuid,class TList, class TString>
class FTPTournamentModelInterface : public ModelInterface<TUuid>
{
public:
    virtual TString title() const = 0;
    virtual FTPTournamentModelInterface<TUuid,TList,TString>* setTitle(const TString &string) = 0;

    virtual TList assignedPlayerIdentities() const = 0;
    virtual FTPTournamentModelInterface<TUuid,TList,TString>* setAssignedPlayerIdentities(const TList &playerIdentities) = 0;
    virtual FTPTournamentModelInterface<TUuid,TList,TString>* assignPlayerIdentity(const TUuid &identity) = 0;

    virtual int attemps() const = 0;
    virtual FTPTournamentModelInterface<TUuid,TList,TString>* setNumberOfThrows(const int &val) = 0;

    virtual int gameMode() const = 0;
    virtual FTPTournamentModelInterface<TUuid,TList,TString>* setGameMode(const int &val) = 0;

    virtual int initialPoint() const = 0;
    virtual FTPTournamentModelInterface* setKeyPoint(const int &val) = 0;

    virtual bool status() const = 0;
    virtual FTPTournamentModelInterface* setStatus(const bool &active) = 0;

    virtual TUuid winnerId() const = 0;
    virtual FTPTournamentModelInterface* setWinner(const TUuid &val) = 0;

    virtual int terminalKeyCode() const = 0;
    virtual FTPTournamentModelInterface* setTerminateKeyCondition(const int &keyCode) = 0;

    virtual FTPTournamentModelInterface* setId(const TUuid &val) override = 0;
    virtual FTPTournamentModelInterface* setType(const int &val) override = 0;
    virtual FTPTournamentModelInterface* setParent(const TUuid &parent) override = 0;

    virtual int displayHint() const = 0;
    virtual FTPTournamentModelInterface* setModelTableViewHint(int modelDisplayHint) = 0;

    virtual int inputHint() const = 0;
    virtual FTPTournamentModelInterface* setInputMode(const int &inputMode) = 0;
};

#endif // FTPTOURNAMENTMODELINTERFACE_H
