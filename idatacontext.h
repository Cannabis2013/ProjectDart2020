#ifndef ILOCALDATACONTEXT_H
#define ILOCALDATACONTEXT_H

template<class TUuid, class TList,class TString, class TTournamentBuilder, class TPlayerBuilder>
class IDataContext
{
public:
    virtual TUuid createTournament(const TString &title, const int &maxPlayers,
                                   const int &keyPoint, 
                                   const int &throws,
                                   const int &gameMode) = 0;

    virtual void deleteTournament(const TUuid &tournament) = 0;
    virtual TList tournaments() const = 0;
    virtual int tournamentsCount() const = 0;
    virtual TUuid tournamentIDFromIndex(const int &index) const = 0;
    virtual TString tournamentTitle(const TUuid &tournament) const = 0;
    virtual int tournamentNumberOfThrows(const TUuid &tournament) const = 0;
    virtual int tournamentMaximumAllowedPlayers(const TUuid &tournament) const = 0;
    virtual TList tournamentAssignedPlayers(const TUuid &tournament) const = 0;
    virtual int tournamentGameMode(const TUuid &tournament) const = 0;
    virtual int tournamentKeyPoint(const TUuid &tournament) const = 0;
    virtual int tournamentStatus(const TUuid &tournament) const = 0;
    virtual TUuid tournamentDeterminedWinner(const TUuid &tournament) const = 0;
    virtual void removeTournament(const TUuid &tournament) = 0;
    virtual void removeTournamentModels(const TUuid &tournament) = 0;
    virtual void alterTournamentTitle(const TUuid &tournament, const TString &title) = 0;
    virtual void alterTournamentNumberOfLegs(const TUuid &tournament, const int &value) = 0;
    virtual void alterTournamentMaxPlayers(const TUuid &tournament, const int &value) = 0;
    virtual void tournamentAddPlayer(const TUuid &tournament, const TUuid &player) = 0;
    virtual void tournamentRemovePlayer(const TUuid &tournament, const TUuid &player) = 0;
    virtual void alterTournamentGameMode(const TUuid &tournament, const int &mode) = 0;
    virtual void alterTournamentKeyPoint(const TUuid &tournament, const int &value) = 0;
    virtual void alterTournamentDeterminedWinner(const TUuid &tournament, const TUuid &player) = 0;

    virtual TList roundsID(const TUuid &tournament) const = 0;
    virtual TUuid roundID(const TUuid &tournament, const int &roundIndex) const  = 0;
    virtual TList roundSetsID(const TUuid &roundID) const = 0;

    virtual TUuid addRound(const TUuid &tournament, const int &index) = 0;
    virtual void alterRoundIndex(const TUuid &tournament,const int &oldIndex, const int &newIndex) = 0;
    virtual int roundIndex(const TUuid &roundID) const = 0;
    virtual TUuid roundTournament(const TUuid &roundID) const = 0;

    virtual TList tournamentSetsID(const TUuid &tournament) const = 0;
    virtual TList tournamentSetsID(const TUuid &tournament, const int &roundIndex) const = 0;

    virtual TUuid setID(const TUuid &tournament, const int &roundIndex, const int &setIndex) const = 0;
    virtual TUuid setRound(const TUuid &setID) const = 0;
    virtual int setIndex(const TUuid &setID) const = 0;
    virtual TUuid addSet(const TUuid &tournament, const int &roundIndex, const int &setIndex) = 0;
    virtual TList setPointsID(const TUuid &setID) const = 0;
    /*
     * Point related section
     */
    virtual TList scores(const TUuid &tournament) const = 0;
    virtual TList scores(const TUuid &tournament, const TUuid &roundID) const = 0;
    virtual TList scores(const TUuid &tournament, const TUuid &roundID, const TUuid &setID) const = 0;
    virtual TUuid setScoreHint(const TUuid &point, const int &hint) = 0;
    virtual TUuid editScore(const TUuid &pointId, const int &value,const int &score,const int &hint) = 0;
    virtual TUuid alterPointPlayer(const TUuid &pointId, const TUuid &playerId) = 0;
    virtual TUuid pointSet(const TUuid &playerPoint) const = 0;
    virtual int pointValue(const TUuid &playerPoint) const = 0;
    virtual int playerScore(const TUuid &playerPoint) = 0;
    virtual TUuid pointPlayer(const TUuid &playerPoint) const = 0;
    virtual int pointHint(const TUuid &playerPoint) const = 0;
    virtual int pointLeg(const TUuid &playerPoint) const = 0;
    virtual TUuid playerPoint(const TUuid &tournament,const TUuid &player, const int &roundIndex, const int & throwIndex, const int &hint) = 0;
    virtual TList playerPoints(const TUuid &tournament, const TUuid &player, const int &hint) const = 0;
    virtual bool removePlayerPoint(const TUuid &point) = 0;
    virtual void removePlayerPointAndRelatives(const TUuid &point) = 0;
    virtual int playerPointsCount(const int &hint) const = 0;

    virtual TUuid addScore(const TUuid &tournament, const TUuid &player,
                   const int &roundIndex,
                   const int &setIndex,
                   const int &legIndex,
                   const int &point) = 0;

    virtual int score(const TUuid &tournament, const TUuid &player) const = 0;
    virtual int score(const TUuid &player) const = 0;
    /*
     * Player related stuff
     */
    virtual TUuid createPlayer(const TString& firstName,
                               const TString& lastName,
                               const TString& playerEMail,
                               const int& role = 0x00) = 0;
    virtual void deletePlayerByFirstName(const TString &firstName) = 0;
    virtual void deletePlayerByID(const TUuid &player) = 0;
    virtual void deletePlayerByEmail(const TString &playerEMail) = 0;
    virtual TUuid playerIDFromFullName(const TString &fullName) const = 0;
    virtual TUuid playerIDFromIndex(const int &index) const = 0;
    virtual TString playerFirstName(const TUuid& id) const = 0;
    virtual TString playerLastName(const TUuid& id) const = 0;

    virtual TString playerFullName(const TUuid& id) const = 0;

    virtual TString playerEMail(const TUuid& id) const = 0;

    virtual TList players() const = 0;

    virtual int playersCount() const = 0;

    virtual IDataContext<TUuid, TList,TString, TTournamentBuilder, TPlayerBuilder> *setPlayerBuilder(TPlayerBuilder *builder) = 0;
    virtual TPlayerBuilder *playerBuilder() const = 0;

    /*
     * Builders
     */
    virtual IDataContext<TUuid, TList,TString, TTournamentBuilder, TPlayerBuilder> *setTournamentBuilder(TTournamentBuilder *builder) = 0;
    virtual TTournamentBuilder *tournamentBuilder() const = 0;

    /*
     * Consistency checks
     */
    virtual bool tournamentExists(const TUuid &tournament) const = 0;
};

#endif // ILOCALDATACONTEXT_H
