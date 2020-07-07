#ifndef ILOCALDATACONTEXT_H
#define ILOCALDATACONTEXT_H

template<class TUuid, class TList,class TString, class TTournamentBuilder>
class IDataContext
{
public:
    virtual TUuid createTournament(const TString &title, const int &maxPlayers,
                                   const int &keyPoint, 
                                   const int &legs, 
                                   const int &gameMode) = 0;

    virtual void deleteTournament(const TUuid &tournament) = 0;

    virtual TList tournaments() const = 0;
    virtual int tournamentsCount() const = 0;

    virtual TUuid tournamentID(const int &index) const = 0;
    virtual TString tournamentTitle(const TUuid &tournament) const = 0;
    virtual int tournamentNumberOfLegs(const TUuid &tournament) const = 0;
    virtual int tournamentMaximumAllowedPlayers(const TUuid &tournament) const = 0;
    virtual TList tournamentAssignedPlayers(const TUuid &tournament) const = 0;
    virtual int tournamentGameMode(const TUuid &tournament) const = 0;
    virtual int tournamentKeyPoint(const TUuid &tournament) const = 0;
    virtual int tournamentStatus(const TUuid &tournament) const = 0;
    virtual TUuid tournamentDeterminedWinner(const TUuid &tournament) const = 0;
    

    virtual void alterTournamentTitle(const TUuid &tournament, const TString &title) = 0;
    virtual void alterTournamentNumberOfLegs(const TUuid &tournament, const int &value) = 0;
    virtual void alterTournamentMaxPlayers(const TUuid &tournament, const int &value) = 0;
    virtual void tournamentAddPlayer(const TUuid &tournament, const TUuid &player) = 0;
    virtual void tournamentRemovePlayer(const TUuid &tournament, const TUuid &player) = 0;
    virtual void alterTournamentGameMode(const TUuid &tournament, const int &mode) = 0;
    virtual void alterTournamentKeyPoint(const TUuid &tournament, const int &value) = 0;
    virtual void alterTournamentDeterminedWinner(const TUuid &tournament, const TUuid &player) = 0;

    virtual TList rounds(const TUuid &tournament) const = 0;

    virtual TUuid round(const TUuid &tournament, const int &roundIndex) const  = 0;

    virtual TUuid addRound(const TUuid &tournament, const int &index) = 0;
    virtual void alterRoundIndex(const TUuid &tournament,const int &oldIndex, const int &newIndex) = 0;

    virtual int roundIndex(const TUuid &round) const = 0;
    virtual TUuid roundTournament(const TUuid &round) const = 0;

    virtual TList sets(const TUuid &tournament) const = 0;
    virtual TList sets(const TUuid &tournament, const TUuid &round) const = 0;
    virtual TList sets(const TUuid &tournament, const int &roundIndex) const = 0;

    virtual TUuid set(const TUuid &tournament, const int &roundIndex, const int &setIndex) const = 0;

    virtual TUuid setRound(const TUuid &set) const = 0;
    virtual int setIndex(const TUuid &set) const = 0;

    virtual TUuid addSet(const TUuid &tournament, const int &roundIndex, const int &setIndex) = 0;

    virtual TList points(const TUuid &tournament) const = 0;
    virtual TList points(const TUuid &tournament, const TUuid &round) const = 0;
    virtual TList points(const TUuid &tournament, const TUuid &round, const TUuid &set) const = 0;


    virtual TUuid addPoint(const TUuid &tournament,
                           const int &roundIndex,
                           const int &setIndex,
                           const int &legIndex,
                           const int &playerPoint,
                           const TUuid &player) = 0;

    virtual TUuid alterPointValue(const TUuid &pointId, const int &value) = 0;
    virtual TUuid alterPointPlayer(const TUuid &pointId, const TUuid &playerId) = 0;

    virtual TUuid pointSet(const TUuid &playerPoint) const = 0;
    virtual int pointValue(const TUuid &playerPoint) const = 0;
    virtual TUuid pointPlayer(const TUuid &playerPoint) const = 0;
    virtual int pointLeg(const TUuid &playerPoint) const = 0;

    /*
     * Retrieve player scores
     */
    virtual TUuid playerPoint(const TUuid &tournament,const TUuid &player, int roundIndex, int legIndex) = 0;
    virtual TList playerPoints(const TUuid &player) const = 0;
    virtual TList playerPoints(const TUuid &tournament, const TUuid &player) const = 0;
    /*
     * Builders
     */
    virtual IDataContext<TUuid, TList,TString, TTournamentBuilder> *setTournamentBuilder(TTournamentBuilder *builder) = 0;

    /*
     * Consistency checks
     */
    virtual bool tournamentExists(const TUuid &tournament) const = 0;
};

#endif // ILOCALDATACONTEXT_H
