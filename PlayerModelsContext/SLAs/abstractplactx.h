#ifndef ABSTRACTPLACTX_H
#define ABSTRACTPLACTX_H
#include <qobject.h>
#include "ModelsContext/ModelsSLAs/imodel.h"
#include <quuid.h>
#include <qvector.h>
class AbstractPlaCtx : public QObject
{
    Q_OBJECT
public:
    typedef IModel<QUuid> Player;
    typedef QVector<IModel<QUuid>*> Players;
    virtual Player *playerModel(const QUuid &id) const = 0;
    virtual Player *playerModel(const QString &name) const = 0;
    virtual Players playerModels(const QVector<int> &indexes) const = 0;
    virtual Players playerModels(const QVector<QUuid> &ids) const = 0;
    virtual Players playerModels(const QVector<QString> &names) const = 0;
    Q_INVOKABLE virtual QByteArray playerModels() = 0;
    Q_INVOKABLE virtual void createPlayer(const QByteArray &json) = 0;
    Q_INVOKABLE virtual void remove(const QVector<int> &indexes) = 0;
public slots:
signals:
    void sendPlayersID(const QVector<QUuid> &playersID);
    void playersDeleted();
    void sendPlayers(const QByteArray& json);
    void playerAdded();
    void playerAddedError(const QString &msg);
};
#endif // ABSTRACTPLACTX_H
