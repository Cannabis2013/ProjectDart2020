#ifndef PLAYER_H
#define PLAYER_H

#include <quuid.h>

#include "iplayermodel.h"

class Player : public IPlayerModel<QUuid,QString>
{
    // IPlayerModel interface
public:
    QUuid id() const override
    {
        return _id;
    }
    void setId(const QUuid &id) override
    {
        _id = id;
    }
    QString firstName() const override
    {
        return _firstName;
    }
    QString lastName() const override
    {
        return _lastName;
    }
    void setFirstName(const QString &string) override
    {
        _firstName = string;
    }
    void setLastName(const QString &string) override
    {
        _lastName = string;
    }
    QString email() const override
    {
        return _email;
    }
    void setEmail(const QString &email) override
    {
        _email = email;
    }
    int userRole() const override
    {
        return _role;
    }
    void setUserRole(const int &role) override
    {
        _role = role;
    }

private:
    QUuid _id;
    QString _firstName, _lastName, _email;
    int _role;
};

#endif // PLAYER_H
