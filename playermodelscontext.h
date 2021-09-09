#ifndef PLAYERMODELSCONTEXT_H
#define PLAYERMODELSCONTEXT_H

#include "iplayermodelscontext.h"
#include <playermodelsservices.h>
#include <QtConcurrent/QtConcurrent>

class PlayerModelsContext :
        public IPlayerModelsContext,
        public PlayerModelsServices
{
public:
    void createPlayer(const QByteArray &json) override;
    void deletePlayersFromIndexes(const QVector<int> &indexes) override;
    void handleRequestPlayersDetails() override;
    virtual QFuture<Models> playerModels(const QByteArray &json) const override;
};

#endif // PLAYERMODELSCONTEXT_H
