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

    virtual int numberOfThrows() const = 0;
    virtual void setNumberOfThrows(const int &val) = 0;

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
};

template<class QUuid, class TList>
class ISet : public IModel<QUuid>
{
public:
    virtual int index() const = 0;
    virtual void setIndex(const int &index) = 0;
};

template <class QUuid>
class IScore : public IModel<QUuid>
{
public:
    virtual int point() const = 0;
    virtual void setPoint(const int &point) = 0;

    virtual int score() const = 0;
    virtual void setScore(const int &score) = 0;

    virtual int legIndex() const = 0;
    virtual void setLegIndex(const int &index) = 0;

    virtual QUuid player() const = 0;
    virtual void setPlayer(const QUuid &id) = 0;

    virtual int hint() const = 0;
    virtual void setHint(const int &hint) = 0;
};

#endif // GAMEMODELSCONTEXT_H
