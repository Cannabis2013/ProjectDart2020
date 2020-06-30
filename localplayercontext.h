#ifndef LOCALPLAYERCONTEXT_H
#define LOCALPLAYERCONTEXT_H

#include "iplayercontext.h"
#include "idatamodelbuilder.h"
#include "iplayermodel.h"
#include <quuid.h>
#include <QString>
#include <qlist.h>
#include <qobject.h>
#include "iplayerbuildercontext.h"

namespace PlayerContext {
    class LocalPlayerContext;
    class PlayerModelOptions;
    class PlayerBuilderParameters;
}

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

    bool generateCustomID() const override
    {
        return _customUuid;
    }
    void setCustomUuid(bool customUuid)
    {
        _customUuid = customUuid;
    }

private:
    bool _generateUniqueId;
    bool _customUuid = false;
};


class PlayerBuilderParameters : public IPlayerBuilderParameters<QString>
{
public:
    QString firstName() const
    {
        return _firstName;
    }
    void setFirstName(const QString &value)
    {
        _firstName = value;
    }

    QString lastName() const
    {
        return _lastName;
    }
    void setLastName(const QString &value)
    {
        _lastName = value;
    }

    QString eMail() const
    {
        return _mailAdress;
    }
    void setMailAdress(const QString &value)
    {
        _mailAdress = value;
    }

    int role() const
    {
        return _role;
    }
    void setRole(int value)
    {
        _role = value;
    }

private:

    QString _firstName;
    QString _lastName;
    QString _mailAdress;

    int _role;
};

typedef IPlayerModel<QUuid,QString> DefaultPlayerInterface;
typedef IDataModelBuilder<DefaultPlayerInterface,IPlayerBuilderParameters<QString>,IPlayerBuilderConfiguration> DefaultPlayerBuilder;
typedef IPlayerContext<QUuid,QList<QUuid>,QString,DefaultPlayerBuilder> PlayerContextInterface;

class LocalPlayerContext :
        public QObject,
        public PlayerContextInterface
{
    Q_OBJECT
    // IPlayerDataContext interface
public:

    LocalPlayerContext();


    // Public types
    enum UserRoles{Admin = 0x0, Player = 0x02};


    QUuid createPlayer(const QString &firstName,
                       const QString &lastName,
                       const QString& playerEMail,
                       const int& role) override;

    void deletePlayerByFirstName(const QString &firstName) override;
    void deletePlayerByID(const QUuid &player) override;
    void deletePlayerByEmail(const QString &playerEMail) override;
    QUuid playerIDFromFirstName(const QString &firstName) const override;
    QUuid playerIDFromLastName(const QString &lastName) const override;

    QString playerFirstName(const QUuid &id) const override;
    QString playerLastName(const QUuid &id) const override;
    QString playerEMail(const QUuid &id) const override;
    QString playerFullName(const QUuid &id) const override;

    QList<QUuid> players() const override;

    int playerCount() const override;

    DefaultPlayerBuilder *playerBuilder() const override;
    PlayerContextInterface *setPlayerBuilder(DefaultPlayerBuilder *builder) override;

private:
    QList<DefaultPlayerInterface*> _models;
    DefaultPlayerBuilder *_playerBuilder;
};

#endif // LOCALPLAYERCONTEXT_H
