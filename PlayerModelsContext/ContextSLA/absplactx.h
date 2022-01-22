#ifndef ABSPLACTX_H
#define ABSPLACTX_H
#include <qobject.h>
#include <quuid.h>
#include "DbSLAs/PlayersDbSLAs.h"
class AbsPlaCtx : public QObject, public PlayersDbSLAs
{
    Q_OBJECT
public:
    Q_INVOKABLE virtual QByteArray players() = 0;
    Q_INVOKABLE virtual bool createPlayer(const QByteArray &json) = 0;
    Q_INVOKABLE virtual bool remove(const QVector<int> &indexes) = 0;
    typedef IPlayer Player;
    typedef QVector<Player*> Players;
    virtual Player *player(const QUuid &id) const = 0;
    virtual Player *player(const QString &name) const = 0;
    virtual Players players(const QVector<int> &indexes) const = 0;
    virtual Players players(const QVector<QUuid> &ids) const = 0;
    virtual Players players(const QVector<QString> &names) const = 0;
public slots:
signals:
    void sendPlayersID(const QVector<QUuid> &playersID);
    void playersDeleted();
    void sendPlayers(const QByteArray& json);
    void playerAdded(const bool &status);
    void playerAddedError(const QString &msg);
};
#endif // ABSPLACTX_H
