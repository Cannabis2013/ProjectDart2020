#ifndef PLAYERSDBCONTEXT_H
#define PLAYERSDBCONTEXT_H
#include <qvector.h>
#include "DbSLAs/IPlayersDbContext.h"
class IPlayer;
class PlayersDbContext : public IPlayersDbContext<IPlayer>
{
public:
    void add(Model *player) override;
    Model *model(const int &index) const override;
    Model *model(std::function<bool (Model*)> predFunct) const override;
    QVector<Model*> models() const override;
    QVector<Model*> models(std::function<bool(Model*)> predFunct) const override;
    void remove(const int &index) override;
    void remove(const QVector<int> &indexes) override;
    int indexOf(Model *player) const override;
    void replace(const int &index, Model *player) override;
private:
    QVector<Model*> _models;
};
#endif // LOCALTOURNAMENTMODELDB_H
