#ifndef DARTSCREATETOURNAMENT_H
#define DARTSCREATETOURNAMENT_H
#include "TournamentsSLAs/idartscreatetournament.h"
class QString;
class DartsPlayer;
template<typename T> class IModel;
class QUuid;
class DMCServices;
class DartsCreateTournament : public IDartsCreateTournament<IModel<QUuid>>
{
public:
    typedef DartsPlayer Player;
    typedef QVector<Player> Players;
    DartsCreateTournament(DMCServices *services);
    virtual Model *create(const ByteArray &byteArray, const Indexes &playerIndexes) const override;
private:
    Players convertPlayers(const ByteArray &playersBa) const;
    void addTournamentDetails(Model *model, const Players &players) const;
    QVector<QUuid> createPlayerIds(const Players &players) const;
    QVector<QString> createPlayerNames(const Players &players) const;
    DMCServices *_services;
};

#endif // DARTSCREATETOURNAMENT_H
