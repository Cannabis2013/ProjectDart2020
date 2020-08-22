#ifndef DEFAULTPLAYERBUILDERCONFIGURATIONS_H
#define DEFAULTPLAYERBUILDERCONFIGURATIONS_H

#include "iplayerbuildercontext.h"
#include <quuid.h>
#include <qstring.h>

class PlayerModelOptions : public IPlayerBuilderConfiguration
{
public:
    bool generateUniqueID() const override
    {
        return _generateUniqueId;
    }
    void setGenerateUniqueId(bool generateUniqueId)
    {
        _generateUniqueId = generateUniqueId;
    }

private:
    bool _generateUniqueId;
};


class PlayerBuilderParameters : public IPlayerBuilderParameters<QString,QUuid>
{
public:
    QString playerName() const override
    {
        return _firstName;
    }
    void setUserName(const QString &value)
    {
        _firstName = value;
    }

    QString eMail() const override
    {
        return _mailAdress;
    }
    void setMailAdress(const QString &value)
    {
        _mailAdress = value;
    }

    int role() const override
    {
        return _role;
    }
    void setRole(int value)
    {
        _role = value;
    }

    QUuid id() const override
    {
        return _id;
    }
    void setId(const QUuid &id)
    {
        _id = id;
    }

private:

    QString _firstName;
    QString _lastName;
    QString _mailAdress;
    QUuid _id;
    int _role;
};

#endif // DEFAULTPLAYERBUILDERCONFIGURATIONS_H
