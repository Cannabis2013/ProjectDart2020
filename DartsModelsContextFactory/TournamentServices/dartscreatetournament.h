#ifndef DARTSCREATETOURNAMENT_H
#define DARTSCREATETOURNAMENT_H
#include "TournamentsSLAs/idartscreatetournament.h"
class IDartsConvertPlayer;
class AbsPlaCtx;
template<typename T> class IDartsBuilder;
class QString;
class DartsPlayer;
template<typename T> class IModel;
class QUuid;
class DartsModelsServices;
class DartsCreateTournament : public IDartsCreateTournament<IModel<QUuid>>
{
public:
    typedef IModel<QUuid> Model;
    typedef DartsPlayer Player;
    typedef QVector<Player> Players;
    typedef IDartsBuilder<Model> ModelBuilder;
    DartsCreateTournament(DartsModelsServices *services);
    virtual Model *create(const ByteArray &byteArray, const Indexes &playerIndexes) const override;
private:
    Players convertPlayers(const ByteArray &playersBa) const;
    void addTournamentDetails(Model *model, const Players &players) const;
    QVector<QUuid> createPlayerIds(const Players &players) const;
    QVector<QString> createPlayerNames(const Players &players) const;
    ModelBuilder *_dartsBuilder;
    AbsPlaCtx *_playersContext;
    IDartsConvertPlayer *_playerConverter;
};

#endif // DARTSCREATETOURNAMENT_H
