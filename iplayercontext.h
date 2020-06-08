#ifndef IPLAYERDATACONTEXT_H
#define IPLAYERDATACONTEXT_H

template<class TUuid,class TList,class TString>
class IPlayerContext
{
public:
    virtual TUuid createPlayer(const TString& firstName,
                               const TString& lastName,
                               const TString& email,
                               const int& role) = 0;

    virtual void deletePlayerByFirstName(const TString &firstName) = 0;
    virtual void deletePlayerByID(const TUuid &player) = 0;
    virtual void deletePlayerByEmail(const TString &email) = 0;

    virtual TUuid playerIDFromForname(const TString& firstName) const = 0;
    virtual TUuid playerIDFromSurname(const TString& lastName) const = 0;

    virtual TString playerFirstName(const TUuid& id) const = 0;
    virtual TString playerLastName(const TUuid& id) const = 0;

    virtual TString playerFullName(const TUuid& id) const = 0;

    virtual TString email(const TUuid& id) const = 0;

    virtual TList players() const = 0;

    virtual int playerCount() const = 0;
};

#endif // IPLAYERDATACONTEXT_H
