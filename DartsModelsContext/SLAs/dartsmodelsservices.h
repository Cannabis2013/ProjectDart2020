#ifndef DARTSMODELSSERVICES_H
#define DARTSMODELSSERVICES_H
#include "ForeignContextSLAs/DartsPlayerServices.h"
#include "TournamentsSLAs/tournamentservices.h"
#include "InputSLAs/dartsinputservices.h"
#include "IndexesSLAs/dartsindexservices.h"
#include "ContextSLA/absplactx.h"
class DartsModelsServices
{
public:
    TournamentServices *tournamentServices() const {return _tournamentServices;}
    void setTournamentServices(TournamentServices *service) {_tournamentServices = service;}

    DartsInputServices *inputServices() const {return _inputServices;}
    void setInputServices(DartsInputServices *service) {_inputServices = service;}

    DartsIndexServices *indexServices() const {return _indexServices;}
    void setIndexServices(DartsIndexServices *service) {_indexServices = service;}

    DartsPlayerServices *playerServices() const {return _playerServices;}
    void setPlayerServices(DartsPlayerServices *service) {_playerServices = service;}

    AbsPlaCtx *playersContext() const {return _playersContext;}
    void setPlayersContext(AbsPlaCtx *newPlayersContext) {_playersContext = newPlayersContext;}
private:
    TournamentServices *_tournamentServices;
    DartsInputServices *_inputServices;
    DartsIndexServices *_indexServices;
    DartsPlayerServices *_playerServices;
    AbsPlaCtx *_playersContext;
};
#endif // DARTSMODELSSERVICES_H
