#ifndef DARTSVERIFYCONSISTENCY_H
#define DARTSVERIFYCONSISTENCY_H
#include "TournamentsSLAs/idartsconsistency.h"

class AbsPlaCtx;
class QString;
template<typename T> class QVector;
class DartsModelsServices;
template<typename T> class IModel;
class DartsVerifyConsistency : public IDartsConsistency
{
public:
    typedef IModel<QUuid> Model;
    typedef QVector<Model*> Models;
    bool verify(const QUuid &tournamentID, const DartsModelsServices *services) const override;
private:
    Model *getTournament(const QUuid &tournamentID, const DartsModelsServices *services) const;
    Models getInputs(const QUuid &tournamentID, const DartsModelsServices *services) const;
    bool verifyTournamentPlayers(Model *tournament, AbsPlaCtx *playerContext) const;
    bool verifyPlayerIDs(const QVector<QUuid> &playerIds, const AbsPlaCtx *playersContext) const;
    bool verifyPlayerNames(const QVector<QString> &playerNames, const AbsPlaCtx *playersContext) const;
    bool verifyInputsPlayers(const Models &models, const AbsPlaCtx *playersContext) const;
};
#endif // DARTSVERIFYCONSISTENCY_H
