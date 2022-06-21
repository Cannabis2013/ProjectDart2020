#ifndef REMOVETOURNAMENTSFROMDB_H
#define REMOVETOURNAMENTSFROMDB_H

#include <DartsModelsContext/Contracts/Routines/idartsremovetournaments.h>


template<typename T> class IModel;
class QUuid;

class RemoveTournamentsFromDb : public IDartsRemoveTournaments
{
public:
    typedef IModel<QUuid> Model;
    virtual bool remove(const Indexes &indexes, DartsModelsServices *services) override;
private:
    void removeTournaments(const Indexes &indexes, DartsModelsServices *services);
    bool persistChanges(DartsModelsServices *services);
    QVector<QUuid> getTournamentIDs(const Indexes &indexes, DartsModelsServices *services);
    void removeTournamentInputs(const QUuid &tournamentID, DartsModelsServices *services);
    Indexes getInputIndexes(const QUuid &tournamentID, DartsModelsServices *services);
    void removeModels(const Indexes &indexes, DartsModelsServices *services);
    DartsModelsServices *_services;
};
#endif // REMOVETOURNAMENTSFROMDB_H
