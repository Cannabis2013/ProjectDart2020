#ifndef IMODEL_H
#define IMODEL_H

template<class TUuid, class TString>
class IPlayerModel
{
public:
    virtual TUuid id() const = 0;
    virtual void setId(const TUuid &id) = 0;

    virtual int type() const = 0;
    virtual void setType(const int &type) = 0;

    virtual TString playerName() const = 0;

    virtual void setUserName(const TString &name) = 0;

    virtual TString email() const = 0;
    virtual void setEmail(const TString& email) = 0;

    virtual int userRole() const = 0;
    virtual void setUserRole(const int& role) = 0;

    virtual bool operator==(IPlayerModel* &other) = 0;
};

#endif // IMODEL_H
