#ifndef ILOCALDATACONTEXT_H
#define ILOCALDATACONTEXT_H

template<class TUuid, class TList, class TString, class TTournamentBuilder>
class IDataContext
{
public:
    virtual ~IDataContext() = default;
    virtual TUuid createTournament(const TString &title,
                                   const int &keyPoint,
                                   const int &throws,
                                   const int &gameMode,
                                   const int &winCondition) = 0;

    virtual void removeTournament(const TUuid &tournament) = 0;
    virtual void removeModelsRelatedToTournament(const TUuid &tournament) = 0;
    virtual TList tournaments() = 0;
    virtual int tournamentsCount() = 0;
    virtual TUuid tournamentIDFromIndex(const int &index) = 0;
    virtual TString tournamentTitle(const TUuid &tournament) = 0;
    virtual int tournamentNumberOfThrows(const TUuid &tournament) = 0;
    virtual TList tournamentAssignedPlayers(const TUuid &tournament) = 0;
    virtual int tournamentGameMode(const TUuid &tournament) = 0;
    virtual int tournamentLastThrowKeyCode(const TUuid &tournament) = 0;
    virtual int tournamentKeyPoint(const TUuid &tournament) = 0;
    virtual int tournamentStatus(const TUuid &tournament) = 0;
    virtual TUuid tournamentDeterminedWinner(const TUuid &tournament) = 0;
    virtual void alterTournamentTitle(const TUuid &tournament, const TString &title) = 0;
    virtual void alterTournamentNumberOfLegs(const TUuid &tournament, const int &value) = 0;
    virtual void assignPlayerToTournament(const TUuid &tournament, const TUuid &player) = 0;
    virtual void tournamentRemovePlayer(const TUuid &tournament, const TUuid &player) = 0;
    virtual void alterTournamentGameMode(const TUuid &tournament, const int &mode) = 0;
    virtual void alterTournamentKeyPoint(const TUuid &tournament, const int &value) = 0;
    virtual void alterTournamentDeterminedWinner(const TUuid &tournament, const TUuid &player) = 0;

    virtual TList roundsID() = 0;
    virtual TList roundsID(const TUuid &tournament) = 0;
    virtual TUuid roundID(const TUuid &tournament, const int &roundIndex) = 0;
    virtual TList roundSetsID(const TUuid &roundID) = 0;

    virtual TUuid addRound(const TUuid &tournament, const int &index) = 0;
    virtual void alterRoundIndex(const TUuid &tournament,const int &oldIndex, const int &newIndex) = 0;
    virtual int roundIndex(const TUuid &roundID) = 0;
    virtual TUuid roundTournament(const TUuid &roundID) = 0;

    virtual TList tournamentSetsID(const TUuid &tournament) = 0;
    virtual TList tournamentSetsID(const TUuid &tournament, const int &roundIndex) = 0;

    virtual TUuid setID(const TUuid &tournament, const int &roundIndex, const int &setIndex) = 0;
    virtual TList setsID() = 0;
    virtual TUuid setRound(const TUuid &setID) = 0;
    virtual int setIndex(const TUuid &setID) = 0;
    virtual TUuid addSet(const TUuid &tournament, const int &roundIndex, const int &setIndex) = 0;
    virtual TList setPointsID(const TUuid &setID) = 0;
    /*
     * Scores related
     */
    virtual TList scores() = 0;
    virtual TList scores(const TUuid &tournament) = 0;
    virtual TList scores(const TUuid &tournament, const int &hint) = 0;
    virtual TList scores(const TUuid &tournament, const TUuid &roundID) = 0;
    virtual TList scores(const TUuid &tournament, const TUuid &roundID, const TUuid &setID) = 0;
    virtual TUuid setScoreHint(const TUuid &point, const int &hint) = 0;
    virtual TUuid editScore(const TUuid &pointId, const int &value,const int &score,const int &hint) = 0;
    virtual TUuid alterPointPlayer(const TUuid &pointId, const TUuid &playerId) = 0;
    virtual TUuid scoreSet(const TUuid &playerScore) = 0;
    virtual int scorePointValue(const TUuid &playerScore) = 0;
    virtual int scoreValue(const TUuid &playerScore) = 0;
    virtual TUuid scorePlayer(const TUuid &playerScore) = 0;
    virtual int scoreHint(const TUuid &playerScore) = 0;
    virtual int scoreThrowIndex(const TUuid &playerScore) = 0;
    virtual TUuid playerScore(const TUuid &tournament,const TUuid &player, const int &roundIndex, const int & throwIndex, const int &hint) = 0;
    virtual TList playerScores(const TUuid &tournament, const TUuid &player, const int &hint) = 0;
    virtual bool removeScore(const TUuid &point) = 0;
    virtual void removePlayerScoreAndRelatives(const TUuid &point) = 0;
    virtual int playerScoreCount(const int &hint) = 0;
    virtual int score(const TUuid &tournament, const TUuid &player) = 0;
    virtual int score(const TUuid &player) = 0;

    virtual int addScore(const TUuid &tournament,
                         const TUuid &player,
                         const int &point,
                         const int &roundIndex,
                         const int &setIndex,
                         const int &throwIndex,
                         const int &score) = 0;
    virtual void removeHiddenScores(const TUuid &tournament) = 0;
    /*
     * Builders
     */
    virtual IDataContext *setTournamentBuilder(TTournamentBuilder *builder) = 0;
    virtual TTournamentBuilder *tournamentBuilder() = 0;

    /*
     * Consistency checks
     */
    virtual void removeInconsistentModels() = 0;

    virtual void buildTournament(const TUuid &id,
                        const TString &title,
                        const int &keyPoint,
                        const int &throws,
                       const int &gameMode,
                       const TUuid &winner) = 0;
    virtual void buildRound(const TUuid &tournament, const int &index, const TUuid &id) = 0;
    virtual void buildSet(const TUuid &id, const TUuid &round, const int &setIndex) = 0;
    virtual void buildScoreModel(const TUuid &id,
                         const TUuid &player,
                         const TUuid &set,
                         const int &point,
                         const int &throwIndex,
                         const int &score) = 0;
};

#endif // ILOCALDATACONTEXT_H
