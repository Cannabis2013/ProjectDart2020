#ifndef PLAYERMODELSCONTEXT_H
#define PLAYERMODELSCONTEXT_H

#include "PlayerModelsContext/SLAs/abstractplayerscontext.h"
#include <QtConcurrent/QtConcurrent>
#include "PlayerModelsContext/DbSLAs/PlayersDbSLAs.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
class PlayerModelsContext :
        public AbstractPlayersContext,
        public PlayersDbSLAs
{
public:
    void createPlayer(const QByteArray &json) override;
    void deletePlayersFromIndexes(const QVector<int> &indexes) override;
    void handleRequestPlayersDetails() override;
    virtual Models playerModels(const QByteArray &json) const override;
private:
    QVector<int> getIndexesFromJson(const QByteArray &json) const;
};

#endif // PLAYERMODELSCONTEXT_H
