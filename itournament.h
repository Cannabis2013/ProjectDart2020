#ifndef ITOURNAMENT_H
#define ITOURNAMENT_H
#include "imodel.h"
template<class TUuid,class TList, class TString>
class ITournament : public IModel<TUuid>
{
public:
    virtual TString title() const = 0;
    virtual ITournament* setTitle(const TString &string) = 0;

    virtual TList assignedPlayerIdentities() const = 0;
    virtual ITournament* assignPlayerIdentity(const TUuid &identity) = 0;
    virtual ITournament* setAssignedPlayerIdentities(const TList &playerIdentities) = 0;

    virtual int gameMode() const = 0;
    virtual ITournament* setGameMode(const int &val) = 0;

    virtual bool status() const = 0;
    virtual ITournament* setStatus(const bool &active) = 0;

    virtual TUuid winnerId() const = 0;
    virtual ITournament* setWinner(const TUuid &val) = 0;
};
#endif // ITOURNAMENT_H
