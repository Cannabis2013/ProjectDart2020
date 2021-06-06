#ifndef DETERMINETOURNAMENTGAMEMODE_H
#define DETERMINETOURNAMENTGAMEMODE_H

#include "abstracttournamentgamemodeservice.h"

class DetermineTournamentGameMode : public AbstractTournamentGameModeService
{
    Q_OBJECT
public slots:
    void handleTournamentGameMode(const QUuid &tournamentId, const int &gameMode) override
    {
        if (gameMode == FirstToPost)
            emit requestDartsDetails(tournamentId);
    }
private:
    // Private types
    enum GameModes {
        FirstToPost = 0x1,
        RoundBased =0x2,
        CircularDart = 0x3
    };
};

#endif // DETERMINETOURNAMENTGAMEMODE_H
