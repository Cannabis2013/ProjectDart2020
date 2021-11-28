#ifndef PLAYERSDBCONTEXT_H
#define PLAYERSDBCONTEXT_H
#include <quuid.h>
#include "PlayerModelsContext/DbSLAs/IPlayersDbContext.h"
#include "ModelsContext/DbSLAs/imodelsdbcontext.h"
#include "PlayerModelsContext/Services/playermodel.h"
class PlayersDbContext : public IPlayersDbContext
{
public:
    PlayersDbContext *add(IModel<QUuid> *player) override;
    IModel<QUuid> *model(const int &index) const override;
    IModel<QUuid>* model(std::function<bool (IModel<QUuid>*)> predFunct) const override;
    QVector<IModel<QUuid>*> models() const override;
    QVector<IModel<QUuid>*> models(std::function<bool(IModel<QUuid>*)> predFunct) const override;
    PlayersDbContext *remove(const int &index) override;
    IPlayersDbContext *remove(const QVector<int> &indexes) override;
    int indexOf(IModel<QUuid> *player) const override;
    PlayersDbContext *replace(const int &index, IModel<QUuid> *player) override;
private:
    QVector<IModel<QUuid>*> _models;
};
#endif // LOCALTOURNAMENTMODELDB_H
