#ifndef GAMEMODELSCONTEXT_H
#define GAMEMODELSCONTEXT_H

namespace GameModelsContext
{
    class IModel;
    class ITournament;
    class IRound;
    class ISet;
    class IPoint;
}

template<class QUuid>
class IModel
{
public:
    virtual QUuid id() const = 0;
    virtual void setId(const QUuid &val) = 0;

    virtual int type() const = 0;
    virtual void setType(const int &val) = 0;
};

template<class QUuid,class TList, class TString>
class ITournament : public IModel<QUuid>
{
public:
    virtual TString title() const = 0;
    virtual void setTitle(const TString &string) = 0;

    virtual int numberOfMaxAllowedPlayers() const = 0;
    virtual void setMaximumAllowedPlayers(const int &val) = 0;

    virtual TList assignedPlayerIdentities() const = 0;
    virtual void setAssignedPlayerIdentities(const TList &playerIdentities) = 0;
    virtual void assignPlayerIdentity(const QUuid &identity) = 0;

    virtual int numberOfLegs() const = 0;
    virtual void setNumberOfLegs(const int &val) = 0;

    virtual int gameMode() const = 0;
    virtual void setGameMode(const int &val) = 0;

    virtual int keyPoint() const = 0;
    virtual void setKeyPoint(const int &val) = 0;

    virtual bool status() const = 0;
    virtual void setStatus(const bool &active) = 0;

    virtual QUuid winner() const = 0;
    virtual void setWinner(const QUuid &val) = 0;
};

template<class QUuid, class TList>
class IRound : public IModel<QUuid>
{
public:
    virtual int index() const = 0;
    virtual void setIndex(const int &val) = 0;

    virtual QUuid tournament() const = 0;
    virtual void setTournament(const QUuid &id) = 0;
};

template<class QUuid, class TList>
class ISet : public IModel<QUuid>
{
public:
    virtual QUuid round() const = 0;
    virtual void setRound(const QUuid &id) = 0;
    virtual int index() const = 0;
    virtual void setIndex(const int &index) = 0;
};

template <class QUuid>
class IPoint : public IModel<QUuid>
{
public:
    virtual int point() const = 0;
    virtual void setPoint(const int &point) = 0;

    virtual QUuid set() const = 0;
    virtual void setSet(const QUuid &id) = 0;

    virtual int legIndex() const = 0;
    virtual void setLegIndex(const int &index) = 0;

    virtual QUuid player() const = 0;
    virtual void setPlayer(const QUuid &id) = 0;
};

#endif // GAMEMODELSCONTEXT_H
