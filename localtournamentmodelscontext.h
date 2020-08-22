#ifndef TOURNAMENTMODELCONTEXT_H
#define TOURNAMENTMODELCONTEXT_H

#include <quuid.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qfile.h>
#include "abstracttournamentmodelscontext.h"
#include "gamemodelscontext.h"


#define THROW_OBJECT_WITH_ID_NOT_FOUND(x) QString("Model with ID: '%1' does not exists in the current context").arg(x).toStdString();
#define THROW_OBJECT_WITH_INDEX_NOT_FOUND(x) QString("Model with index: '%1' does not exists in the current context").arg(x).toStdString();

typedef ITournament<QUuid,QList<QUuid>,QString> DefaultTournamentInterface;
typedef IRound<QUuid, QList<QUuid>> DefaultRoundInterface;
typedef ISet<QUuid,QList<QUuid>> DefaultSetInterface;
typedef IScore<QUuid> DefaultPointInterface;

typedef IDataModelBuilder<DefaultTournamentInterface, TournamentParameters,ModelOptions> ITournamentBuilder;
typedef IDataModelBuilder<DefaultRoundInterface, RoundParameters,ModelOptions> IRoundBuilder;
typedef IDataModelBuilder<DefaultSetInterface, SetParameters,ModelOptions> ISetBuilder;
typedef IDataModelBuilder<DefaultPointInterface, PointParameters,ModelOptions> IPointBuilder;


class LocalTournamentModelsContext :
        public AbstractTournamentModelsContext
{
Q_OBJECT

public:
    /*
     * Public types
     */
    enum ModelsContextResponse{
        UpdateSuccessFull,
        UpdateUnSuccessFull,
        DataProvidedOk,
        DataProvidedFail
    };
    enum ModelDisplayHint{
        HiddenHint = 0x9,
        DisplayHint = 0xA,
        allHints = 0xB
    };

    // Builder methods
    ITournamentBuilder *tournamentBuilder();
    LocalTournamentModelsContext *setTournamentBuilder(ITournamentBuilder *builder);
    IRoundBuilder *roundBuilder();
    LocalTournamentModelsContext *setRoundBuilder(IRoundBuilder *builder);
    ISetBuilder *setBuilder() const;
    LocalTournamentModelsContext *setSetBuilder(ISetBuilder *builder);
    IPointBuilder *pointBuilder();
    LocalTournamentModelsContext *setPointBuilder(IPointBuilder *builder);
    /*
     * Testing purposes
     */
    void createDummyModels();
    void assignToTournament(const int &index, const QList<QUuid> &list);

public slots:
    void handleCreateTournament(const QString &title,
                                       const int &keyPoint,
                                       const int &throws,
                                       const int &gameMode,
                                       const int &winCondition) override;
    void handleAssignPlayers(const QUuid &tournament, const QList<QUuid> &playersID) override;
    void handleDeleteTournaments(const QVector<int>&indexes) override;
    void handleGetAssignedPlayersToTournament(const QUuid &tournament) override;
    void handleTransmitPlayerScores(const QUuid &tournament,
                                    const QList<QPair<QUuid, QString> > &playerPairs) override;
    void handleTransmitTournaments() override;
    void handleAssembleTournamentMeta(const QUuid &tournament) override;
    void handleTournamentIDFromIndex(const int &index) override;
    void handleRequestForTournamentDetails(const QUuid &tournamentID,
                                           const PlayerPairs &assignedPlayerPairs) override;
    void handleRequestTournamentIndexes(const QUuid &tournament) override;
    void addScore(const QUuid &tournament,
                 const QUuid &playerID,
                 const int &roundIndex,
                 const int &setIndex,
                 const int &throwIndex,
                 const int &point,
                 const int &score) override;
private:
    void updateDataContext(const QUuid &tournament, const QUuid &player, const int &roundIndex, const int &setIndex);
    /*
     * Tournament related section
     */
    QUuid createTournament(const QString &title,
                           const int &keyPoint,
                           const int &throws,
                           const int &gameMode,
                           const int &winCondition) ;
    void removeTournament(const QUuid &tournament) ;
    void removeModelsRelatedToTournament(const QUuid &tournament) ;
    QUuid tournamentIDFromIndex(const int &index) ;
    QList<QUuid> tournaments() ;
    int tournamentsCount() ;
    QString tournamentTitle(const QUuid &tournament) ;
    int tournamentNumberOfThrows(const QUuid &tournament) ;
    QList<QUuid> tournamentAssignedPlayers(const QUuid &tournament) ;
    int tournamentGameMode(const QUuid &tournament) ;
    int tournamentLastThrowKeyCode(const QUuid &tournament) ;
    int tournamentKeyPoint(const QUuid &tournament) ;
    int tournamentStatus(const QUuid &tournament) ;
    QUuid tournamentDeterminedWinner(const QUuid &tournament) ;
    void assignPlayerToTournament(const QUuid &tournament, const QUuid &player) ;
    void tournamentRemovePlayer(const QUuid &tournament, const QUuid &player) ;
    void alterTournamentTitle(const QUuid &tournament, const QString &title) ;
    void alterTournamentNumberOfLegs(const QUuid &tournament, const int &value) ;
    void alterTournamentGameMode(const QUuid &tournament, const int &mode) ;
    void alterTournamentKeyPoint(const QUuid &tournament, const int &value) ;
    void alterTournamentDeterminedWinner(const QUuid &tournament, const QUuid &player) ;
    /*
     * Round related section
     */
    QList<QUuid> roundsID() ;
    QList<QUuid> roundsID(const QUuid &tournament) ;
    QUuid roundID(const QUuid &tournament, const int &roundIndex) ;
    QUuid addRound(const QUuid &tournament, const int &index) ;
    void alterRoundIndex(const QUuid &, const int &, const int &) ;
    int roundIndex(const QUuid &roundID) ;
    QUuid roundTournament(const QUuid &roundID) ;
    /*
     * Set related section
     */
    QUuid setID(const QUuid &tournament, const int &roundIndex, const int &setIndex) ;
    QList<QUuid> tournamentSetsID(const QUuid &tournament) ;
    QList<QUuid> roundSetsID(const QUuid &roundID) ;
    QList<QUuid> tournamentSetsID(const QUuid &tournament, const int &roundIndex) ;
    QList<QUuid> setsID() ;
    QUuid setRound(const QUuid &setID) ;
    int setIndex(const QUuid &setID) ;
    QUuid addSet(const QUuid &tournament, const int &roundIndex, const int &setIndex) ;
    QList<QUuid> setPointsID(const QUuid &setID) ;
    /*
     * Scores related section
     */
    QUuid playerScore(const QUuid &tournament, const QUuid &player , const int &roundIndex, const int &throwIndex, const int &hint) ;
    QList<QUuid> scores() ;
    QList<QUuid> scores(const QUuid &tournament) ;
    QList<QUuid> scores(const QUuid &tournament, const QUuid &roundID) ;
    QList<QUuid> scores(const QUuid &tournament, const QUuid &roundID, const QUuid &setID) ;
    QList<QUuid> scores(const QUuid &tournament, const int &hint) ;
    QList<QUuid> playerScores(const QUuid &tournament, const QUuid &player, const int &hint) ;
    int playerScoreCount(const int &hint) ;
    QUuid setScoreHint(const QUuid &point, const int &hint) ;
    QUuid editScore(const QUuid &pointId, const int &value, const int &score,const int &hint) ;
    QUuid alterPointPlayer(const QUuid &pointId, const QUuid &playerId) ;
    QUuid scoreSet(const QUuid &playerScore) ;
    int scoreThrowIndex(const QUuid &playerScore) ;
    int scorePointValue(const QUuid &playerScore) ;
    int scoreValue(const QUuid &point) ;
    QUuid scorePlayer(const QUuid &playerScore) ;
    int scoreHint(const QUuid &playerScore) ;
    bool removeScore(const QUuid &point) ;
    void removePlayerScoreAndRelatives(const QUuid &point) ;


    void removeHiddenScores(const QUuid &tournament) ;

    void removeInconsistentModels() ;

    int score(const QUuid &tournament, const QUuid &player) ;
    int score(const QUuid &player) ;

    QList<QUuid> pointModels(const QUuid &player);

    void removeTournamentRounds(const QUuid &tournament);
    void removeTournamentSets(const QUuid &tournament);
    void removeTournamentScores(const QUuid &tournament);

    void removeEmptyRound(const QUuid &round);
    void removeEmptySet(const QUuid &setID);

    void removeTournamentModel(const QUuid &tournament);
    void removePointModel(const QUuid &playerScore);

    const DefaultTournamentInterface *getTournamentModelFromID(const QUuid &id);
    const DefaultRoundInterface *getRoundModelFromID(const QUuid &id);
    const DefaultSetInterface *getSetModelFromID(const QUuid &id);
    const DefaultPointInterface *getScoreModelFromID(const QUuid &id);

    /*
     * Consistency checks
     */
    void removeInconsistentScores();
    void removeInconsistentSets();
    void removeInconsistentRounds();
    /*
     * Add existing models from persistence
     */

    void buildTournament(const QUuid &id,
                        const QString &title,
                        const int &keyPoint,
                        const int &throws,
                       const int &gameMode,
                       const QUuid &winner) ;

    void buildRound(const QUuid &tournament, const int &index, const QUuid &id) ;
    void buildSet(const QUuid &id, const QUuid &round, const int &setIndex) ;
    void buildScoreModel(const QUuid &id,
                         const QUuid &player,
                         const QUuid &set,
                         const int &point,
                         const int &throwIndex,
                         const int &score);

    ITournamentBuilder *_tournamentBuilder;
    IRoundBuilder *_roundBuilder;
    ISetBuilder *_setBuilder;
    IPointBuilder *_pointBuilder;

    QList<const DefaultTournamentInterface*> _tournaments;
    QList<const DefaultRoundInterface *> _rounds;
    QList<const DefaultSetInterface *> _sets;
    QList<const DefaultPointInterface*> _scores;
};

#endif // TOURNAMENTMODELCONTEXT_H
