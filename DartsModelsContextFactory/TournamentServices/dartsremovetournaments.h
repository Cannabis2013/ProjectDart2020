#ifndef DARTSREMOVETOURNAMENTS_H
#define DARTSREMOVETOURNAMENTS_H
#include "TournamentsSLAs/IDartsRemoveTournaments.h"
template<typename T> class IDbContext;
template<typename T> class IModel;
class QUuid;
class DartsInputServices;
class DartsServices;
class DMCServices;
class DartsRemoveTournaments : public IDartsRemoveTournaments
{
public:
    typedef IModel<QUuid> Model;
    typedef IDbContext<Model> DbContext;
    DartsRemoveTournaments(DMCServices *services);
    virtual void remove(const Indexes &indexes) override;
private:
    QVector<QUuid> getTournamentIDs(const Indexes &indexes);
    void removeTournamentInputs(const QUuid &tournamentID);
    Indexes getInputIndexes(const QUuid &tournamentID);
    void removeModels(const Indexes &indexes, DbContext *dbContext);
    DMCServices *_services;
    DartsServices *_tnmServices;
    DartsInputServices *_iptServices;
    DbContext *_tnmdb;
    DbContext *_iptdb;
};
#endif // DARTSREMOVETOURNAMENTS_H
