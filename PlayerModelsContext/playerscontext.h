#ifndef PLAYERSCONTEXT_H
#define PLAYERSCONTEXT_H
#include <QtConcurrent/QtConcurrent>
#include <qjsondocument.h>
#include "PlayerModelsContext/SLAs/abstractplayerscontext.h"
#include <qjsonobject.h>
#include "PlayerModelsContext/DbSLAs/PlayersDbSLAs.h"
#include "AsyncUtils/runlater.h"
class PlayersContext : public AbstractPlayersContext,
                       public PlayersDbSLAs
{
    Q_OBJECT
public:
    Player *playerModel(const QUuid &id) const override;
    Player *playerModel(const QString &name) const override;
    QByteArray players() override;
    bool createPlayer(const QByteArray &json) override;
    bool remove(const QVector<int> &indexes) override;
    Players players(const QVector<int> &indexes) const override;
    Players players(const QVector<QUuid> &ids) const override;
    Players players(const QVector<QString> &names) const override;
};
#endif // PLAYERSCONTEXT_H
