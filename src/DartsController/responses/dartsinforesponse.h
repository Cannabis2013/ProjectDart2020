#ifndef DARTSINFORESPONSE_H
#define DARTSINFORESPONSE_H

#include "src/DartsController/indexes/IDartsIndexes.h"
#include "src/DartsController/players/IDartPlayers.h"
#include "src/DartsController/responses/IDartsInfoResponse.h"

class DartsInfoResponse : public IDartsInfoResponse
{
        // IDartInfoResponse interface
public:
    DartsInfoResponse(IDartPlayers* players,
                      IDartsIndexes *_indexes);
        virtual TurnInfo currentTurnInfo() override;
        virtual WinnerInfo winnerInfo() override;
private:
        // Services
        IDartPlayers *_players;
        IDartsIndexes *_indexes;
};

#endif // DARTSINFORESPONSE_H
