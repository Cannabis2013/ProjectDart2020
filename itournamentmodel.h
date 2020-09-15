#ifndef ITOURNAMENTMODEL_H
#define ITOURNAMENTMODEL_H

template<class TUuid>
class IModel
{
public:
    virtual TUuid id() const = 0;
    virtual void setId(const TUuid &val) = 0;

    virtual int type() const = 0;
    virtual void setType(const int &val) = 0;

    virtual void setParent(const TUuid &parent) = 0;
    virtual TUuid parent() const = 0;
};

template<class TUuid,class TList, class TString>
class ITournament : public IModel<TUuid>
{
public:
    virtual TString title() const = 0;
    virtual void setTitle(const TString &string) = 0;

    virtual TList assignedPlayerIdentities() const = 0;
    virtual void setAssignedPlayerIdentities(const TList &playerIdentities) = 0;
    virtual void assignPlayerIdentity(const TUuid &identity) = 0;

    virtual int numberOfThrows() const = 0;
    virtual void setNumberOfThrows(const int &val) = 0;

    virtual int gameMode() const = 0;
    virtual void setGameMode(const int &val) = 0;

    virtual int keyPoint() const = 0;
    virtual void setKeyPoint(const int &val) = 0;

    virtual bool status() const = 0;
    virtual void setStatus(const bool &active) = 0;

    virtual TUuid winner() const = 0;
    virtual void setWinner(const TUuid &val) = 0;

    virtual int terminateKeyCondition() const = 0;
    virtual void setTerminateKeyCondition(const int &keyCode) = 0;
};

#endif // ITOURNAMENTMODEL_H
