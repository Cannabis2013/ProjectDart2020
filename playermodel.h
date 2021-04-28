#ifndef PLAYER_H
#define PLAYER_H

#include <quuid.h>

#include "iplayermodel.h"

class PlayerModel : public IPlayerModel<QUuid,QString>
{
    // IPlayerModel interface
public:
    QUuid id() const override
    {
        return _id;
    }
    PlayerModel* setId(const QUuid &id) override
    {
        _id = id;
        return this;
    }
    QString email() const override
    {
        return _email;
    }
    PlayerModel* setEmail(const QString &email) override
    {
        _email = email;
        return this;
    }
    int userRole() const override
    {
        return _role;
    }
    PlayerModel* setUserRole(const int &role) override
    {
        _role = role;
        return this;
    }
    QString playerName() const override
    {
        return _userName;
    }
    PlayerModel* setUserName(const QString &name) override
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
    virtual PlayerModel* setParent(const QUuid &) override
    {
        return this;
    }
    virtual QUuid parent() const override
    {
        return QUuid();
    }
    static PlayerModel* createInstance()
    {
        return new PlayerModel;
    }
private:
    QUuid _id;
    QString _userName, _email;
    int _role, _type;
};

#endif // PLAYER_H
