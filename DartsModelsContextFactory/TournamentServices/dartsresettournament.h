#ifndef DARTSRESETTOURNAMENT_H
#define DARTSRESETTOURNAMENT_H
#include "TournamentsSLAs/idartsresettournament.h"
class DartsServices;
template<typename T> class IDbContext;
template<typename T> class IModel;
class DartsModelsServices;
class DartsResetTournament : public IDartsResetTournament
{
public:
    typedef IModel<QUuid> Model;
    typedef IDbContext<Model> DbContext;
    DartsResetTournament(DartsModelsServices *services);
    void reset(const QUuid &tournamentID) const override;
private:
    void removeTournamentInputs(const QUuid &tournamentID) const;
    void resetTournament(const QUuid &tournamentID) const;
    DartsModelsServices *_services;
    DartsServices *_tnmServices;
    DbContext *_dartsDb;
    DbContext *_iptsDb;
};

#endif // DARTSRESETTOURNAMENT_H
