#ifndef PROJECTDARTINTERFACE_H
#define PROJECTDARTINTERFACE_H

#include "idatacontext.h"
#include "iplayercontext.h"

template<class TUuid,
         class TString,
         class TList>
class ProjectDartInterface
{
public:
    /*
     * Data context interface
     *
     *  - create/read/update/delete/edit tournaments
     *  - create/read/update/delete/edit rounds
     */

    virtual TUuid createTournament(const TString &title, const int &maxPlayers,
                                   const int &keyPoint,
                                   const int &numberOfLegsPerRound,
                                   const int &gameMode) = 0;

    virtual bool assignPlayerToTournament(const TUuid& tournament, const TUuid& player) = 0;
    virtual bool unAssignPlayerFromTournament(const TUuid& tournament, const TUuid& player) = 0;

    virtual TString tournamentTitleFromID(const TUuid& tournament) const = 0;
    virtual int numberOfPlayersAssignedToTournament(const TUuid& tournament) const = 0;
    virtual int maxPlayersAllowedToTournament(const TUuid& tournament) const = 0;

    virtual int currentScore(const TUuid &tournament, const TUuid &player) const = 0;

    virtual TList tournaments() const = 0;

    // Gamecontroller interface
    virtual ProjectDartInterface* startGame() = 0;
    virtual ProjectDartInterface* stopGame() = 0;

    virtual TUuid undoTurn() = 0;
    virtual TUuid redoTurn() = 0;

    virtual TUuid reportPointScored(const int &point) = 0;

    virtual TUuid currentPlayerID() const = 0;

    virtual TUuid currentActiveTournament() const = 0;

    virtual int currentRoundIndex() const = 0;
    virtual int currentSetIndex() const = 0;
    virtual int currentLegIndex() const = 0;

    virtual int gameStatus() const = 0;

    // Player interface
    virtual TList players() const = 0;

    virtual TUuid createPlayer(const TString& firstName, const TString& lastName, const TString &email) = 0;
    virtual void deletePlayer(const TUuid& player) = 0;

    virtual TString playerFirstName(const TUuid& player) const = 0;
    virtual TString playerLastName(const TUuid& player) const = 0;
    virtual TString playerMailAdress(const TUuid& player) const = 0;
    virtual int playerRole(const TUuid& player) const = 0;
};

#endif // PROJECTDARTINTERFACE_H
