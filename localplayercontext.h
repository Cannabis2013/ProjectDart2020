#ifndef LOCALPLAYERCONTEXT_H
#define LOCALPLAYERCONTEXT_H

#include "iplayercontext.h"
#include "igenericdatamodelbuilder.h"
#include <quuid.h>
#include <QString>
#include <qlist.h>
#include <iplayermodel.h>

struct PlayerBuilderParameters
{
    QString firstName;
    QString lastName;
    QString mailAdress;

    int role;
};

struct ModelOptions
{
    bool generateUniqueId;
    bool customUuid = false;
};

typedef IPlayerModel<QUuid,QString> DefaultPlayerInterface;
typedef IGenericDataModelBuilder<DefaultPlayerInterface,PlayerBuilderParameters, ModelOptions> DefaultPlayerBuilderInterface;
typedef IPlayerContext<QUuid,QList<QUuid>,QString> DefaultDataInterface;

class LocalPlayerContext : public DefaultDataInterface
{
    // IPlayerDataContext interface
public:

    // Public types

    enum UserRoles{Admin = 0x0, Player = 0x02};

    LocalPlayerContext();

    QUuid createPlayer(const QString &firstName,
                       const QString &lastName,
                       const QString& email,
                       const int& role) override;

    void deletePlayerByFirstName(const QString &firstName) override;
    void deletePlayerByID(const QUuid &player) override;
    void deletePlayerByEmail(const QString &email) override;
    QUuid playerIDFromForname(const QString &firstName) const override;
    QUuid playerIDFromSurname(const QString &lastName) const override;

    QString playerFirstName(const QUuid &id) const override;
    QString playerLastName(const QUuid &id) const override;

    QString playerFullName(const QUuid &id) const override;

    QList<QUuid> players() const override;

    int playerCount() const override;

    void setPlayerBuilder(DefaultPlayerBuilderInterface *interface);
    DefaultPlayerBuilderInterface *playerBuilder() const;

private:
    QList<DefaultPlayerInterface*> _models;
    DefaultPlayerBuilderInterface *_builder;
};

#endif // LOCALPLAYERCONTEXT_H
