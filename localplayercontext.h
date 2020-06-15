#ifndef LOCALPLAYERCONTEXT_H
#define LOCALPLAYERCONTEXT_H

#include "iplayercontext.h"
#include "idatamodelbuilder.h"
#include <quuid.h>
#include <QString>
#include <qlist.h>
#include <iplayermodel.h>

namespace PlayerContext {
    struct PlayerModelOptions;
    struct PlayerBuilderParameters;
    class LocalPlayerContext;
}

class PlayerModelOptions
{
public:
    bool generateUniqueId;
    bool customUuid = false;
};

class PlayerBuilderParameters
{
public:
    QString firstName;
    QString lastName;
    QString mailAdress;

    int role;
};

typedef IPlayerModel<QUuid,QString> DefaultPlayerInterface;
typedef IDataModelBuilder<DefaultPlayerInterface,PlayerBuilderParameters, PlayerModelOptions> PlayerBuilderInterface;
typedef IPlayerContext<QUuid,QList<QUuid>,QString> PlayerContextInterface;

class LocalPlayerContext : public PlayerContextInterface
{
    // IPlayerDataContext interface
public:

    // Public types

    enum UserRoles{Admin = 0x0, Player = 0x02};

    LocalPlayerContext();

    QUuid createPlayer(const QString &firstName,
                       const QString &lastName,
                       const QString& playerEMail,
                       const int& role) override;

    void deletePlayerByFirstName(const QString &firstName) override;
    void deletePlayerByID(const QUuid &player) override;
    void deletePlayerByEmail(const QString &playerEMail) override;
    QUuid playerIDFromForname(const QString &firstName) const override;
    QUuid playerIDFromSurname(const QString &lastName) const override;

    QString playerFirstName(const QUuid &id) const override;
    QString playerLastName(const QUuid &id) const override;

    QString playerFullName(const QUuid &id) const override;

    QList<QUuid> players() const override;

    int playerCount() const override;

    PlayerBuilderInterface *playerBuilder() const;
    void setPlayerBuilder(PlayerBuilderInterface *builder);

private:
    QList<DefaultPlayerInterface*> _models;
    PlayerBuilderInterface *_builder;
};

#endif // LOCALPLAYERCONTEXT_H
