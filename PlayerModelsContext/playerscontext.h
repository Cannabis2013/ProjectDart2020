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
    QByteArray playerModels() override;
    void createPlayer(const QByteArray &json) override;
    void remove(const QVector<int> &indexes) override;
    Players playerModels(const QVector<int> &indexes) const override;
    Players playerModels(const QVector<QUuid> &ids) const override;
    Players playerModels(const QVector<QString> &names) const override;
};
#endif // PLAYERSCONTEXT_H
