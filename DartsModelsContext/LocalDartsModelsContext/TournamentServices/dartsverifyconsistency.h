#ifndef DARTSVERIFYCONSISTENCY_H
#define DARTSVERIFYCONSISTENCY_H

#include <DartsModelsContext/Contracts/Tournament/idartsconsistency.h>
#include <PlayerModelsContext/Contracts/ContextSLA/abstractplayercontext.h>
#include <QVector>

template<typename T> class IModel;
class DartsVerifyConsistency : public IDartsConsistency
{
public:
      typedef IModel<QUuid> Model;
      typedef QVector<Model *> Models;
      bool verify(const QUuid &tournamentID,
                  const DartsModelsServices *services) const override;

private:
      Model *getTournament(const QUuid &tournamentID,
                           const DartsModelsServices *services) const;
      Models getInputs(const QUuid &tournamentID,
                       const DartsModelsServices *services) const;
      bool verifyTournamentPlayers(Model *tournament,
                                   AbstractPlayerContext *playerContext) const;
      bool verifyPlayerIDs(const QVector<QUuid> &playerIds,
                           const AbstractPlayerContext *playersContext) const;
      bool verifyPlayerNames(const QVector<QString> &playerNames,
                             const AbstractPlayerContext *playersContext) const;
      bool verifyInputsPlayers(
          const Models &models,
          const AbstractPlayerContext *playersContext) const;
};
#endif // DARTSVERIFYCONSISTENCY_H
