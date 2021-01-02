#ifndef ITOURNAMENTMODEL_H
#define ITOURNAMENTMODEL_H

template<class TUuid>
class IModel
{
public:
    virtual TUuid id() const = 0;
    virtual IModel* setId(const TUuid &val) = 0;

    virtual int type() const = 0;
    virtual IModel* setType(const int &val) = 0;

    virtual IModel* setParent(const TUuid &parent) = 0;
    virtual TUuid parent() const = 0;
};

template<class TUuid,class TList, class TString>
class ITournament : public IModel<TUuid>
{
public:
    virtual TString title() const = 0;
    virtual ITournament* setTitle(const TString &string) = 0;

    virtual TList assignedPlayerIdentities() const = 0;
    virtual ITournament* setAssignedPlayerIdentities(const TList &playerIdentities) = 0;
    virtual ITournament* assignPlayerIdentity(const TUuid &identity) = 0;

    virtual int numberOfThrows() const = 0;
    virtual ITournament* setNumberOfThrows(const int &val) = 0;

    virtual int gameMode() const = 0;
    virtual ITournament* setGameMode(const int &val) = 0;

    virtual int keyPoint() const = 0;
    virtual ITournament* setKeyPoint(const int &val) = 0;

    virtual bool status() const = 0;
    virtual ITournament* setStatus(const bool &active) = 0;

    virtual TUuid winner() const = 0;
    virtual ITournament* setWinner(const TUuid &val) = 0;

    virtual int terminateKeyCondition() const = 0;
    virtual ITournament* setTerminateKeyCondition(const int &keyCode) = 0;

    virtual ITournament* setId(const TUuid &val) override = 0;
    virtual ITournament* setType(const int &val) override = 0;
    virtual ITournament* setParent(const TUuid &parent) override = 0;

    virtual int modelTableViewHint() const = 0;
    virtual ITournament* setModelTableViewHint(int modelDisplayHint) = 0;
};

#endif // ITOURNAMENTMODEL_H
