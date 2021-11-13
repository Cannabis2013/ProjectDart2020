#ifndef PLAYERSCONTEXT_H
#define PLAYERSCONTEXT_H
#include <QtConcurrent/QtConcurrent>
#include <qjsondocument.h>
#include "PlayerModelsContext/SLAs/abstractplayerscontext.h"
#include <qjsonobject.h>
#include "PlayerModelsContext/DbSLAs/PlayersDbSLAs.h"
#include "AsyncUtils/runnable.h"
class PlayersContext :
        public AbstractPlayersContext,
        public PlayersDbSLAs
{
public:
    Player *playerModel(const QUuid &id) const override;
    void createPlayer(const QByteArray &json) override;
    void deletePlayersFromIndexes(const QVector<int> &indexes) override;
    void handleRequestPlayersDetails() override;
    Players playerModels(const QVector<int> &indexes) const override;
    Players playerModels(const QVector<QUuid> &ids) const override;

};
#endif // PLAYERSCONTEXT_H
