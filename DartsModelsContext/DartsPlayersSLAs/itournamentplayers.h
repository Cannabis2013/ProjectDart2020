#ifndef ITOURNAMENTPLAYERS_H
#define ITOURNAMENTPLAYERS_H
#include <quuid.h>
#include <qvector.h>
class ITournamentPlayers
{
public:
    virtual QVector<QUuid> playerIds() const = 0;
    virtual ITournamentPlayers* setPlayerIds(const QVector<QUuid> &playerIdentities) = 0;
    virtual QVector<QString> playerNames() const = 0;
    virtual ITournamentPlayers* setPlayerNames(const QVector<QString> &playerIdentities) = 0;
};
#endif // ITOURNAMENTPLAYERS_H
