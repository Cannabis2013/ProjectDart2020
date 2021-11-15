#ifndef TOURNAMENTPLAYERS_H
#define TOURNAMENTPLAYERS_H
#include "DartsModelsContext/DartsPlayersSLAs/itournamentplayers.h"
class TournamentPlayers : public ITournamentPlayers
{
public:
    virtual QVector<QUuid> playerIds() const override
    {
        return _ids;
    }
    virtual TournamentPlayers *setPlayerIds(const QVector<QUuid> &playerIds) override
    {
        _ids = playerIds;
        return this;
    }
    virtual QVector<QString> playerNames() const override
    {
        return _names;
    }
    virtual TournamentPlayers *setPlayerNames(const QVector<QString> &playerNames) override
    {
        _names = playerNames;
        return this;
    }
private:
    QVector<QUuid> _ids;
    QVector<QString> _names;
};
#endif // TOURNAMENTPLAYERS_H
