#ifndef IMODEL_H
#define IMODEL_H

#include "modelinterface.h"

template<class TUuid, class TString>
class IPlayerModel : public ModelInterface<TUuid>
{
public:
    virtual TString playerName() const = 0;

    virtual void setUserName(const TString &name) = 0;

    virtual TString email() const = 0;
    virtual void setEmail(const TString& email) = 0;

    virtual int userRole() const = 0;
    virtual void setUserRole(const int& role) = 0;

    virtual bool operator==(IPlayerModel* &other) = 0;
};

#endif // IMODEL_H
