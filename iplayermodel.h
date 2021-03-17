#ifndef IMODEL_H
#define IMODEL_H

#include "imodel.h"

template<class TUuid, class TString>
class IPlayerModel : public IModel<TUuid>
{
public:
    virtual TString playerName() const = 0;

    virtual IPlayerModel* setUserName(const TString &name) = 0;

    virtual TString email() const = 0;
    virtual IPlayerModel* setEmail(const TString& email) = 0;

    virtual int userRole() const = 0;
    virtual IPlayerModel* setUserRole(const int& role) = 0;

    virtual bool operator==(IPlayerModel* &other) = 0;
};

#endif // IMODEL_H
