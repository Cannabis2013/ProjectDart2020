#ifndef PLAYERSDBCONTEXT_H
#define PLAYERSDBCONTEXT_H

#include <quuid.h>
#include "ModelsContext/DbSLAs/IDbPersistence.h"
#include "PlayerModelsContext/DbSLAs/IPlayersDbContext.h"
#include "ModelsContext/DbSLAs/imodelsdbcontext.h"
#include "PlayerModelsContext/Services/playermodel.h"
#include "ModelsContext/DbSLAs/modelsdbioservices.h"

class PlayersDbContext :
        public IPlayersDbContext,
        protected ModelsDbIOSLAs
{
public:
    PlayersDbContext(FileReaderInterface *fileReader, FileWriteInterface *fileWriter);
    virtual PlayersDbContext *add(IModel<QUuid> *player) override;
    virtual IModel<QUuid> *model(const int &index) const override;
    virtual QVector<IModel<QUuid>*> models() const override;
    virtual PlayersDbContext *remove(const int &index) override;
    virtual IPlayersDbContext *remove(const QVector<int> &indexes) override;
    virtual int indexOf(IModel<QUuid> *player) const override;
    virtual PlayersDbContext *replace(const int &index, IModel<QUuid> *player) override;
    void fetchModels(const IPlayerContextModelBuilder *modelBuilder) override;
    void saveChanges(const IPlayerContextJsonBuilder *jsonBuilder) override;
private:
    const QString _fileName = "PlayerModels";
    QVector<IModel<QUuid>*> _playerModels;
};
#endif // LOCALTOURNAMENTMODELDB_H
