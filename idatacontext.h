#ifndef ILOCALDATACONTEXT_H
#define ILOCALDATACONTEXT_H

template<class TUuid, class TList, class TString, class TTournamentBuilder>
class IDataContext
{
public:
    virtual ~IDataContext() = default;
    virtual TUuid createtournament(const TString &title,
                                   const int &keyPoint, 
                                   const int &throws,
                                   const int &gameMode) = 0;

    virtual void deleteTournament(const TUuid &tournament) = 0;
    virtual TList tournaments() const = 0;
    virtual int tournamentsCount() const = 0;
    virtual TUuid tournamentIDFromIndex(const int &index) const = 0;
    virtual TString tournamentTitle(const TUuid &tournament) const = 0;
    virtual int tournamentNumberOfThrows(const TUuid &tournament) const = 0;
    virtual TList tournamentAssignedPlayers(const TUuid &tournament) const = 0;
    virtual int tournamentGameMode(const TUuid &tournament) const = 0;
    virtual int tournamentKeyPoint(const TUuid &tournament) const = 0;
    virtual int tournamentStatus(const TUuid &tournament) const = 0;
    virtual TUuid tournamentDeterminedWinner(const TUuid &tournament) const = 0;
    virtual void removeTournament(const TUuid &tournament) = 0;
    virtual void removeTournamentModels(const TUuid &tournament) = 0;
    virtual void alterTournamentTitle(const TUuid &tournament, const TString &title) = 0;
    virtual void alterTournamentNumberOfLegs(const TUuid &tournament, const int &value) = 0;
    virtual void assignPlayerToTournament(const TUuid &tournament, const TUuid &player) = 0;
    virtual void tournamentRemovePlayer(const TUuid &tournament, const TUuid &player) = 0;
    virtual void alterTournamentGameMode(const TUuid &tournament, const int &mode) = 0;
    virtual void alterTournamentKeyPoint(const TUuid &tournament, const int &value) = 0;
    virtual void alterTournamentDeterminedWinner(const TUuid &tournament, const TUuid &player) = 0;

    virtual TList roundsID() const = 0;
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
    virtual TList setsID() const = 0;
    virtual TUuid setRound(const TUuid &setID) const = 0;
    virtual int setIndex(const TUuid &setID) const = 0;
    virtual TUuid addSet(const TUuid &tournament, const int &roundIndex, const int &setIndex) = 0;
    virtual TList setPointsID(const TUuid &setID) const = 0;
    /*
     * Scores related
     */
    virtual TList scores() const = 0;
    virtual TList scores(const TUuid &tournament) const = 0;
    virtual TList scores(const TUuid &tournament, const TUuid &roundID) const = 0;
    virtual TList scores(const TUuid &tournament, const TUuid &roundID, const TUuid &setID) const = 0;
    virtual TUuid setScoreHint(const TUuid &point, const int &hint) = 0;
    virtual TUuid editScore(const TUuid &pointId, const int &value,const int &score,const int &hint) = 0;
    virtual TUuid alterPointPlayer(const TUuid &pointId, const TUuid &playerId) = 0;
    virtual TUuid scoreSet(const TUuid &playerPoint) const = 0;
    virtual int scorePointValue(const TUuid &playerPoint) const = 0;
    virtual int scoreValue(const TUuid &playerPoint) = 0;
    virtual TUuid pointPlayer(const TUuid &playerPoint) const = 0;
    virtual int scoreHint(const TUuid &playerPoint) const = 0;
    virtual int pointThrowIndex(const TUuid &playerPoint) const = 0;
    virtual TUuid playerPoint(const TUuid &tournament,const TUuid &player, const int &roundIndex, const int & throwIndex, const int &hint) = 0;
    virtual TList playerPoints(const TUuid &tournament, const TUuid &player, const int &hint) const = 0;
    virtual bool removePlayerPoint(const TUuid &point) = 0;
    virtual void removePlayerPointAndRelatives(const TUuid &point) = 0;
    virtual int playerPointsCount(const int &hint) const = 0;

    virtual int score(const TUuid &tournament, const TUuid &player) const = 0;
    virtual int score(const TUuid &player) const = 0;

    virtual int addScore(const TUuid &tournament,
                         const TUuid &player,
                         const int &point,
                         const int &roundIndex,
                         const int &setIndex,
                         const int &throwIndex,
                         const int &score) = 0;

    /*
     * Builders
     */
    virtual IDataContext *setTournamentBuilder(TTournamentBuilder *builder) = 0;
    virtual TTournamentBuilder *tournamentBuilder() const = 0;

    /*
     * Consistency checks
     */
    virtual bool tournamentExists(const TUuid &tournament) const = 0;
};

#endif // ILOCALDATACONTEXT_H
