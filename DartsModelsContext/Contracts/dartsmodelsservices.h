#ifndef DARTSMODELSSERVICES_H
#define DARTSMODELSSERVICES_H

#include <DartsModelsContext/Contracts/Tournament/tournamentservices.h>
#include <DartsModelsContext/Contracts/Input/dartsinputservices.h>
#include <DartsModelsContext/Contracts/Index/dartsindexservices.h>
#include <DartsModelsContext/Contracts/Player/DartsPlayerServices.h>
#include <PlayerModelsContext/Contracts/ContextSLA/abstractplayercontext.h>


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

        AbstractPlayerContext *playersContext() const {return _playersContext;}
        void setPlayersContext(AbstractPlayerContext *newPlayersContext) {_playersContext = newPlayersContext;}
private:
        TournamentServices *_tournamentServices;
        DartsInputServices *_inputServices;
        DartsIndexServices *_indexServices;
        DartsPlayerServices *_playerServices;
        AbstractPlayerContext *_playersContext;
};
#endif // DARTSMODELSSERVICES_H
