#ifndef PLAYER_H
#define PLAYER_H
#include <quuid.h>
#include "PlayerModelsContext/DbSLAs/iplayermodel.h"
class PlayerModel : public IPlayerModel
{
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
    QString name() const override
    {
        return _userName;
    }
    PlayerModel* setName(const QString &name) override
    {
        _userName = name;
        return this;
    }

    bool operator==(IPlayerModel* &other) override
    {
        if(other->id() == this->id())
            return true;
        else
            return false;
    }
private:
    QUuid _id;
    QString _userName, _email;

};
#endif // PLAYER_H
