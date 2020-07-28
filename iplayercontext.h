#ifndef IPLAYERDATACONTEXT_H
#define IPLAYERDATACONTEXT_H

template<class TUuid,class TList,class TString, class TBuilderInterface>
class IPlayerContext
{
public:
    virtual ~IPlayerContext() = default;
    virtual TUuid createPlayer(const TString& userName,
                               const TString& playerEMail,
                               const int& role = 0x00) = 0;
    virtual void deletePlayerByUserName(const TString &firstName) = 0;
    virtual void deletePlayerByID(const TUuid &player) = 0;
    virtual void deletePlayerByEmail(const TString &playerEMail) = 0;
    virtual TUuid playerIDFromUserName(const TString &fullName) const = 0;
    virtual TUuid playerIDFromIndex(const int &index) const = 0;
    virtual TString playerUserName(const TUuid &id) const = 0;

    virtual TString playerEMail(const TUuid& id) const = 0;

    virtual TList players() const = 0;

    virtual int playersCount() const = 0;

    virtual IPlayerContext<TUuid,TList,TString, TBuilderInterface> *setPlayerBuilder(TBuilderInterface *builder) = 0;
    virtual TBuilderInterface *playerBuilder() const = 0;

    virtual void buildPlayerModel(const TUuid &id,
                                  const TString &userName,
                                  const TString& email) = 0;

};

#endif // IPLAYERDATACONTEXT_H
