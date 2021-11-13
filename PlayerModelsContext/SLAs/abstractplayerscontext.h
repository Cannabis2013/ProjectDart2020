#ifndef ABSTRACTPLAYERSCONTEXT_H
#define ABSTRACTPLAYERSCONTEXT_H
#include <qobject.h>
#include "ModelsContext/ModelsSLAs/imodel.h"
#include <quuid.h>
#include <qvector.h>
class AbstractPlayersContext : public QObject
{
    Q_OBJECT
public:
    typedef IModel<QUuid> Player;
    typedef QVector<IModel<QUuid>*> Players;
    virtual Player *playerModel(const QUuid &id) const = 0;
    virtual Players playerModels(const QVector<int> &indexes) const = 0;
    virtual Players playerModels(const QVector<QUuid> &ids) const = 0;
    Q_INVOKABLE virtual void createPlayer(const QByteArray &json) = 0;
    Q_INVOKABLE virtual void deletePlayersFromIndexes(const QVector<int> &indexes) = 0;
public slots:
    virtual void handleRequestPlayersDetails() = 0;
signals:
    void sendPlayersID(const QVector<QUuid> &playersID);
    void playersDeletedStatus(const bool &status);
    void sendPlayers(const QByteArray& json);
    void playerAddedSucces();
    void playerAddedError(const QString &msg);
};

#endif // ABSTRACTPLAYERSCONTEXT_H
