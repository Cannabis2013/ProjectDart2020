#ifndef DARTSINFORESPONSE_H
#define DARTSINFORESPONSE_H

#include "src/DartsController/indexes/IDartIndexes.h"
#include "src/DartsController/players/IDartPlayers.h"
#include "src/DartsController/responses/IDartsInfoResponse.h"
#include "src/DartsController/scores/IDartsScores.h"

class DartsInfoResponse : public IDartsInfoResponse
{
        // IDartInfoResponse interface
public:
        DartsInfoResponse(IDartsScores* scores, IDartPlayers* players, IDartIndexes *_indexes);
        virtual InitialValueInfo initialInfo() override;
        virtual TurnInfo currentTurnInfo() override;
        virtual WinnerInfo winnerInfo() override;
private:
        // Services
        IDartsScores *_scores;
        IDartPlayers *_players;
        IDartIndexes *_indexes;
};

#endif // DARTSINFORESPONSE_H
