#ifndef PLAYERMODELSCONTEXT_H
#define PLAYERMODELSCONTEXT_H

#include "PlayerModelsContext/SLAs/iplayermodelscontext.h"
#include "PlayerModelsContext/SLAs/playermodelsslas.h"
#include <QtConcurrent/QtConcurrent>

class PlayerModelsContext :
        public IPlayerModelsContext,
        public PlayerModelsSLAs
{
public:
    void createPlayer(const QByteArray &json) override;
    void deletePlayersFromIndexes(const QVector<int> &indexes) override;
    void handleRequestPlayersDetails() override;
    virtual QFuture<Models> playerModels(const QByteArray &json) const override;
};

#endif // PLAYERMODELSCONTEXT_H
