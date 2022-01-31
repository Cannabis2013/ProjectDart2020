#ifndef DMCSERVICES_H
#define DMCSERVICES_H
#include "ForeignContextSLAs/DartsPlayerServices.h"
#include "TournamentsSLAs/dartsservices.h"
#include "InputSLAs/dartsinputservices.h"
#include "IndexesSLAs/dartsindexservices.h"
#include "TournamentsDbSLAs/persistenceservices.h"
#include "ContextSLA/absplactx.h"
class DMCServices
{
public:
    DartsServices *tournamentServices() const {return _tournamentServices;}
    void setTournamentServices(DartsServices *service) {_tournamentServices = service;}

    DartsInputServices *inputServices() const {return _inputServices;}
    void setInputServices(DartsInputServices *service) {_inputServices = service;}

    DartsIndexServices *indexServices() const {return _indexServices;}
    void setIndexServices(DartsIndexServices *service) {_indexServices = service;}

    PersistenceServices *persistenceServices() const {return _persistenceServices;}
    void setPersistenceServices(PersistenceServices *service) {_persistenceServices = service;}

    DartsPlayerServices *playerServices() const {return _playerServices;}
    void setPlayerServices(DartsPlayerServices *service) {_playerServices = service;}

    AbsPlaCtx *playersContext() const {return _playersContext;}
    void setPlayersContext(AbsPlaCtx *newPlayersContext) {_playersContext = newPlayersContext;}
private:
    DartsServices *_tournamentServices;
    DartsInputServices *_inputServices;
    DartsIndexServices *_indexServices;
    PersistenceServices *_persistenceServices;
    DartsPlayerServices *_playerServices;
    AbsPlaCtx *_playersContext;
};
#endif // DMCSERVICES_H
