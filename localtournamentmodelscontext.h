#ifndef TOURNAMENTMODELCONTEXT_H
#define TOURNAMENTMODELCONTEXT_H

#include <quuid.h>
#include "modelbuildercollection.h"
#include "idatacontext.h"
#include "iplayermodel.h"
#include "iplayerbuildercontext.h"
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qfile.h>


#define THROW_OBJECT_WITH_ID_NOT_FOUND(x) QString("Model with ID: '%1' does not exists in the current context").arg(x).toStdString();
#define THROW_OBJECT_WITH_INDEX_NOT_FOUND(x) QString("Model with index: '%1' does not exists in the current context").arg(x).toStdString();


typedef IPlayerModel<QUuid,QString> DefaultModelInterface;
typedef IPlayerBuilderParameters<QString,QUuid> DefaultParameters;
typedef IDataContext<QUuid,QList<QUuid>,QString,ITournamentBuilder> DefaultDataInterface;


class LocalTournamentModelsContext :
        public DefaultDataInterface
{
public:
    enum ModelDisplayHint{HiddenHint = 0x9,DisplayHint = 0xA, allHints = 0xB};
    /*
     * Tournament related section
     */
    QUuid createTournament(const QString &title,
                           const int &keyPoint,
                           const int &throws,
                           const int &gameMode,
                           const int &winCondition) override;
    void removeTournament(const QUuid &tournament) override;
    void removeModelsRelatedToTournament(const QUuid &tournament) override;
    QUuid tournamentIDFromIndex(const int &index) override;
    QList<QUuid> tournaments() override;
    int tournamentsCount() override;
    QString tournamentTitle(const QUuid &tournament) override;
    int tournamentNumberOfThrows(const QUuid &tournament) override;
    QList<QUuid> tournamentAssignedPlayers(const QUuid &tournament) override;
    int tournamentGameMode(const QUuid &tournament) override;
    int tournamentWinningKeyCondition(const QUuid &tournament) override;
    int tournamentKeyPoint(const QUuid &tournament) override;
    int tournamentStatus(const QUuid &tournament) override;
    QUuid tournamentDeterminedWinner(const QUuid &tournament) override;
    void assignPlayerToTournament(const QUuid &tournament, const QUuid &player) override;
    void tournamentRemovePlayer(const QUuid &tournament, const QUuid &player) override;
    void alterTournamentTitle(const QUuid &tournament, const QString &title) override;
    void alterTournamentNumberOfLegs(const QUuid &tournament, const int &value) override;
    void alterTournamentGameMode(const QUuid &tournament, const int &mode) override;
    void alterTournamentKeyPoint(const QUuid &tournament, const int &value) override;
    void alterTournamentDeterminedWinner(const QUuid &tournament, const QUuid &player) override;
    /*
     * Round related section
     */
    QList<QUuid> roundsID() override;
    QList<QUuid> roundsID(const QUuid &tournament) override;
    QUuid roundID(const QUuid &tournament, const int &roundIndex) override;
    QUuid addRound(const QUuid &tournament, const int &index) override;
    void alterRoundIndex(const QUuid &, const int &, const int &) override;
    int roundIndex(const QUuid &roundID) override;
    QUuid roundTournament(const QUuid &roundID) override;
    /*
     * Set related section
     */
    QUuid setID(const QUuid &tournament, const int &roundIndex, const int &setIndex) override;
    QList<QUuid> tournamentSetsID(const QUuid &tournament) override;
    QList<QUuid> roundSetsID(const QUuid &roundID) override;
    QList<QUuid> tournamentSetsID(const QUuid &tournament, const int &roundIndex) override;
    QList<QUuid> setsID() override;
    QUuid setRound(const QUuid &setID) override;
    int setIndex(const QUuid &setID) override;
    QUuid addSet(const QUuid &tournament, const int &roundIndex, const int &setIndex) override;
    QList<QUuid> setPointsID(const QUuid &setID) override;
    /*
     * Scores related section
     */
    QUuid playerScore(const QUuid &tournament, const QUuid &player , const int &roundIndex, const int &throwIndex, const int &hint) override;
    QList<QUuid> scores() override;
    QList<QUuid> scores(const QUuid &tournament) override;
    QList<QUuid> scores(const QUuid &tournament, const QUuid &roundID) override;
    QList<QUuid> scores(const QUuid &tournament, const QUuid &roundID, const QUuid &setID) override;
    QList<QUuid> scores(const QUuid &tournament, const int &hint) override;
    QList<QUuid> playerScores(const QUuid &tournament, const QUuid &player, const int &hint) override;
    int playerScoreCount(const int &hint) override;
    QUuid setScoreHint(const QUuid &point, const int &hint) override;
    QUuid editScore(const QUuid &pointId, const int &value, const int &score,const int &hint) override;
    QUuid alterPointPlayer(const QUuid &pointId, const QUuid &playerId) override;
    QUuid scoreSet(const QUuid &playerScore) override;
    int scoreThrowIndex(const QUuid &playerScore) override;
    int scorePointValue(const QUuid &playerScore) override;
    int scoreValue(const QUuid &point) override;
    QUuid scorePlayer(const QUuid &playerScore) override;
    int scoreHint(const QUuid &playerScore) override;
    bool removeScore(const QUuid &point) override;
    void removePlayerScoreAndRelatives(const QUuid &point) override;

    int addScore(const QUuid &tournament, const QUuid &player, const int &point, const int &roundIndex, const int &setIndex, const int &throwIndex, const int &score) override;

    void removeHiddenScores(const QUuid &tournament) override;

    void removeInconsistentModels() override;

private:
    int score(const QUuid &tournament, const QUuid &player) override;
    int score(const QUuid &player) override;

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
                       const QUuid &winner) override;

    void buildRound(const QUuid &tournament, const int &index, const QUuid &id) override;
    void buildSet(const QUuid &id, const QUuid &round, const int &setIndex) override;
    void buildScoreModel(const QUuid &id,
                         const QUuid &player,
                         const QUuid &set,
                         const int &point,
                         const int &throwIndex,
                         const int &score) override;
    // Builder methods
    ITournamentBuilder * tournamentBuilder() override
    {
        return _tournamentBuilder;
    }
    DefaultDataInterface *setTournamentBuilder(ITournamentBuilder *builder) override
    {
        _tournamentBuilder = builder;
        return this;
    }

    IRoundBuilder *roundBuilder();
    void setRoundBuilder(IRoundBuilder *roundBuilder);
    ISetBuilder *setBuilder();
    void setSetBuilder(ISetBuilder *builder);
    IPointBuilder *pointBuilder();

    ITournamentBuilder *_tournamentBuilder = new TournamentModelBuilder();
    IRoundBuilder *_roundBuilder = new RoundBuilder();
    ISetBuilder *_setBuilder = new SetBuilder();
    IPointBuilder *_pointBuilder = new PointBuilder();

    QList<const DefaultTournamentInterface*> _tournaments;
    QList<const DefaultRoundInterface *> _rounds;
    QList<const DefaultSetInterface *> _sets;
    QList<const DefaultPointInterface*> _scores;

    friend class LocalDataContext;

};

#endif // TOURNAMENTMODELCONTEXT_H
