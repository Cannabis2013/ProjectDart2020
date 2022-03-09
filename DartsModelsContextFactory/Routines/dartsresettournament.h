#ifndef DARTSRESETTOURNAMENT_H
#define DARTSRESETTOURNAMENT_H
#include "Routines/idartsresettournament.h"
class TournamentServices;
template<typename T> class IDbContext;
template<typename T> class IModel;
class DartsModelsServices;
class DartsResetTournament : public IDartsResetTournament
{
public:
    typedef IModel<QUuid> Model;
    typedef IDbContext<Model> DbContext;
    bool reset(const QUuid &tournamentID, DartsModelsServices *services) override;
private:
    void removeTournamentInputs(const QUuid &tournamentID, DartsModelsServices *services) const;
    void resetTournament(const QUuid &tournamentID, DartsModelsServices *services) const;
    bool persistChanges(DartsModelsServices *services);
};

#endif // DARTSRESETTOURNAMENT_H
