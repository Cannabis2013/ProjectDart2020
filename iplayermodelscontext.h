#ifndef IPLAYERMODELSCONTEXT_H
#define IPLAYERMODELSCONTEXT_H

#include <qobject.h>
#include "imodel.h"
#include <quuid.h>
#include <qvector.h>
#include <qfuture.h>

class IPlayerModelsContext : public QObject
{
    Q_OBJECT
public:
    typedef QVector<const IModel<QUuid>*> Models;
    virtual QFuture<Models> playerModels(const QByteArray &json) const = 0;
public slots:
    virtual void createPlayer(const QByteArray &json) = 0;
    virtual void deletePlayersFromIndexes(const QVector<int> &indexes) = 0;
    virtual void handleRequestPlayersDetails() = 0;

signals:
    void sendPlayersID(const QVector<QUuid> &playersID);
    void playersDeletedStatus(const bool &status);
    void sendPlayers(const QByteArray& json);
    void playerAddedSucces();
    void playerAddedError(const QString &msg);
};

#endif // IPLAYERMODELSCONTEXT_H
