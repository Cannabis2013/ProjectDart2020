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
    Player* setId(const QUuid &id) override
    {
        _id = id;
        return this;
    }
    QString email() const override
    {
        return _email;
    }
    Player* setEmail(const QString &email) override
    {
        _email = email;
        return this;
    }
    int userRole() const override
    {
        return _role;
    }
    Player* setUserRole(const int &role) override
    {
        _role = role;
        return this;
    }
    int type() const override
    {
        return _type;
    }
    Player* setType(const int &type) override
    {
        _type = type;
        return this;
    }
    QString playerName() const override
    {
        return _userName;
    }
    Player* setUserName(const QString &name) override
    {
        _userName = name;
        return this;
    }

    bool operator==(IPlayerModel<QUuid,QString>* &other) override
    {
        if(other->id() == this->id())
            return true;
        else
            return false;
    }
    virtual Player* setParent(const QUuid &) override
    {
        return this;
    }
    virtual QUuid parent() const override
    {
        return QUuid();
    }
    static Player* createInstance()
    {
        return new Player;
    }
private:
    QUuid _id;
    QString _userName, _email;
    int _role, _type;
};

#endif // PLAYER_H
