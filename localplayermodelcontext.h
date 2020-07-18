#ifndef LOCALPLAYERCONTEXT_H
#define LOCALPLAYERCONTEXT_H

#include "iplayercontext.h"
#include "localplayerbuilder.h"
#include "iplayermodel.h"
#include <quuid.h>
#include <QString>
#include <qlist.h>
#include <qobject.h>

namespace PlayerContext {
    class LocalPlayerContext;
    class PlayerModelOptions;
    class PlayerBuilderParameters;
}

typedef IPlayerModel<QUuid,QString> DefaultPlayerInterface;
typedef IDataModelBuilder<DefaultPlayerInterface,IPlayerBuilderParameters<QString>,IPlayerBuilderConfiguration> DefaultPlayerBuilder;
typedef IPlayerContext<QUuid,QList<QUuid>,QString,DefaultPlayerBuilder> PlayerContextInterface;

class LocalPlayerModelContext :
        public QObject,
        public PlayerContextInterface
{
    Q_OBJECT
    // IPlayerDataContext interface
public:
    /*
     * Public constructor
     *  - Initalize player builder
     *  - Read settings from persistence
     */
    LocalPlayerModelContext();
    // Public types
    enum UserRoles{Admin = 0x0, Player = 0x02};
    QUuid createPlayer(const QString &firstName,
                       const QString &lastName,
                       const QString& playerEMail,
                       const int& role) override;
    void deletePlayerByFirstName(const QString &firstName) override;
    void deletePlayerByID(const QUuid &player) override;
    void deletePlayerByEmail(const QString &playerEMail) override;
    QUuid playerIDFromFullName(const QString &fullName) const override;
    QUuid playerIDFromIndex(const int &index) const override;
    QString playerFirstName(const QUuid &id) const override;
    QString playerLastName(const QUuid &id) const override;
    QString playerEMail(const QUuid &id) const override;
    QString playerFullName(const QUuid &id) const override;
    QList<QUuid> players() const override;
    int playersCount() const override;
    DefaultPlayerBuilder *playerBuilder() const override;
    PlayerContextInterface *setPlayerBuilder(DefaultPlayerBuilder *builder) override;
private:

    DefaultPlayerInterface *getModel(const QString &firstName, const QString & lastName) const;

    QList<DefaultPlayerInterface*> _models;
    DefaultPlayerBuilder *_playerBuilder;
};

#endif // LOCALPLAYERCONTEXT_H
