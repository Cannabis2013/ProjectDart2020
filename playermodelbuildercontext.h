#ifndef DEFAULTPLAYERBUILDERCONFIGURATIONS_H
#define DEFAULTPLAYERBUILDERCONFIGURATIONS_H

#include "iplayerbuildercontext.h"
#include <quuid.h>
#include <qstring.h>


class PlayerBuilderParameters : public IPlayerBuilderParameters<QString,QUuid>
{
public:
    QString playerName() const override
    {
        return _firstName;
    }
    PlayerBuilderParameters* setUserName(const QString &value)
    {
        _firstName = value;
        return this;
    }

    QString eMail() const override
    {
        return _mailAdress;
    }
    PlayerBuilderParameters* setMailAdress(const QString &value)
    {
        _mailAdress = value;
        return this;
    }

    int role() const override
    {
        return _role;
    }
    PlayerBuilderParameters* setRole(int value)
    {
        _role = value;
        return this;
    }

    QUuid id() const override
    {
        return _id;
    }
    PlayerBuilderParameters* setId(const QUuid &id)
    {
        _id = id;
        return this;
    }

private:
    QString _firstName;
    QString _lastName;
    QString _mailAdress;
    QUuid _id;
    int _role;
};

class PlayerModelOptions : public IPlayerModelOptions<QUuid>
{
public:
    bool generateID() const override
    {
        return _generateID;
    }
    void enableGenerateUniqueID(const bool &enable) override
    {
        _generateID = enable;
    }

private:
    bool _generateID;

};

#endif // DEFAULTPLAYERBUILDERCONFIGURATIONS_H
