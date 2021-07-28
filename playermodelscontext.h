#ifndef PLAYERMODELSCONTEXT_H
#define PLAYERMODELSCONTEXT_H

#include "iplayermodelscontext.h"

#include <iremovemodelsfromdb.h>
#include <playermodelsservices.h>
#include <QtConcurrent/QtConcurrent>

class PlayerModelsContext :
        public IPlayerModelsContext,
        public PlayerModelsServices
{
public:
    bool createPlayer(const QByteArray &json) override;
    void deletePlayersFromIndexes(const QVector<int> &indexes) override;
    void handleRequestPlayersDetails() override;
    virtual QFuture<Models> playerModels(const QByteArray &json) const override;
    // Services
    IRemoveModelsFromDb<IModelsDbContext> *removeFromDb() const;
    void setRemoveFromDb(IRemoveModelsFromDb<IModelsDbContext> *newRemoveFromDb);
private:
    IRemoveModelsFromDb<IModelsDbContext> *_removeFromDb;
};

#endif // PLAYERMODELSCONTEXT_H
