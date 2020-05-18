#ifndef IMODEL_H
#define IMODEL_H

namespace PlayerContext {
    class IPlayerModel;
}

#define T_UNUSUED(X){X == X;}

template<class TUuid, class TString>
class IPlayerModel
{
public:
    virtual TUuid id() const = 0;
    virtual void setId(const TUuid &id) = 0;

    virtual int type() const {return -1;}
    virtual void setType(const int &type){T_UNUSUED(type);}

    virtual TString firstName() const = 0;
    virtual TString lastName() const = 0;

    virtual void setFirstName(const TString &string) = 0;
    virtual void setLastName(const TString &string) = 0;

    virtual TString email() const = 0;
    virtual void setEmail(const TString& email) = 0;

    virtual int userRole() const = 0;
    virtual void setUserRole(const int& role) = 0;
};

#endif // IMODEL_H
