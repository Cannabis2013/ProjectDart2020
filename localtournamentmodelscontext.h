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
                           const int &gameMode) override;
    void deleteTournament(const QUuid &tournament) override;
    QUuid tournamentIDFromIndex(const int &index) const override;
    QList<QUuid> tournaments() const override;
    int tournamentsCount() const override;
    QString tournamentTitle(const QUuid &tournament) const override;
    int tournamentNumberOfThrows(const QUuid &tournament) const override;
    QList<QUuid> tournamentAssignedPlayers(const QUuid &tournament) const override;
    int tournamentGameMode(const QUuid &tournament) const override;
    int tournamentKeyPoint(const QUuid &tournament) const override;
    int tournamentStatus(const QUuid &tournament) const override;
    QUuid tournamentDeterminedWinner(const QUuid &tournament) const override;
    void assignPlayerToTournament(const QUuid &tournament, const QUuid &player) override;
    void tournamentRemovePlayer(const QUuid &tournament, const QUuid &player) override;
    void removeTournament(const QUuid &tournament) override;
    void removeTournamentModels(const QUuid &tournament) override;
    void alterTournamentTitle(const QUuid &tournament, const QString &title) override;
    void alterTournamentNumberOfLegs(const QUuid &tournament, const int &value) override;
    void alterTournamentGameMode(const QUuid &tournament, const int &mode) override;
    void alterTournamentKeyPoint(const QUuid &tournament, const int &value) override;
    void alterTournamentDeterminedWinner(const QUuid &tournament, const QUuid &player) override;
    /*
     * Round related section
     */
    QList<QUuid> roundsID() const override;
    QList<QUuid> roundsID(const QUuid &tournament) const override;
    QUuid roundID(const QUuid &tournament, const int &roundIndex) const override;
    QUuid addRound(const QUuid &tournament, const int &index) override;
    void alterRoundIndex(const QUuid &, const int &, const int &) override;
    int roundIndex(const QUuid &roundID) const override;
    QUuid roundTournament(const QUuid &roundID) const override;
    /*
     * Set related section
     */
    QUuid setID(const QUuid &tournament, const int &roundIndex, const int &setIndex) const override;
    QList<QUuid> tournamentSetsID(const QUuid &tournament) const override;
    QList<QUuid> roundSetsID(const QUuid &roundID) const override;
    QList<QUuid> tournamentSetsID(const QUuid &tournament, const int &roundIndex) const override;
    QList<QUuid> setsID() const override;
    QUuid setRound(const QUuid &setID) const override;
    int setIndex(const QUuid &setID) const override;
    QUuid addSet(const QUuid &tournament, const int &roundIndex, const int &setIndex) override;
    QList<QUuid> setPointsID(const QUuid &setID) const override;
    /*
     * Scores related section
     */
    QList<QUuid> scores() const override;
    QList<QUuid> scores(const QUuid &tournament) const override;
    QList<QUuid> scores(const QUuid &tournament, const QUuid &roundID) const override;
    QList<QUuid> scores(const QUuid &tournament, const QUuid &roundID, const QUuid &setID) const override;

    QUuid setScoreHint(const QUuid &point, const int &hint) override;
    QUuid editScore(const QUuid &pointId, const int &value, const int &score,const int &hint) override;
    QUuid alterPointPlayer(const QUuid &pointId, const QUuid &playerId) override;
    QUuid scoreSet(const QUuid &playerPoint) const override;
    int scoreThrowIndex(const QUuid &playerPoint) const override;
    int scorePointValue(const QUuid &playerPoint) const override;
    int scoreValue(const QUuid &point) override;
    QUuid scorePlayer(const QUuid &playerPoint) const override;
    QUuid playerPoint(const QUuid &tournament, const QUuid &player , const int &roundIndex, const int &throwIndex, const int &hint) override;
    int scoreHint(const QUuid &playerPoint) const override;
    QList<QUuid> playerPoints(const QUuid &tournament, const QUuid &player, const int &hint) const override;
    bool removePlayerPoint(const QUuid &point) override;
    void removePlayerPointAndRelatives(const QUuid &point) override;
    int playerPointsCount(const int &hint) const override;

    int addScore(const QUuid &tournament, const QUuid &player, const int &point, const int &roundIndex, const int &setIndex, const int &throwIndex, const int &score) override;

    void removeInconsistentModels() override;

private:
    int score(const QUuid &tournament, const QUuid &player) const override;
    int score(const QUuid &player) const override;

    QList<QUuid> pointModels(const QUuid &player) const;

    void removeTournamentRounds(const QUuid &tournament);
    void removeTournamentSets(const QUuid &tournament);
    void removeTournamentScores(const QUuid &tournament);

    void removeEmptyRound(const QUuid &round);
    void removeEmptySet(const QUuid &setID);

    void removeTournamentModel(const QUuid &tournament);
    void removePointModel(const QUuid &playerPoint);

    const DefaultTournamentInterface *getTournamentModelFromID(const QUuid &id) const;
    const DefaultRoundInterface *getRoundModelFromID(const QUuid &id) const;
    const DefaultSetInterface *getSetModelFromID(const QUuid &id) const;
    const DefaultPointInterface *getScoreModelFromID(const QUuid &id) const;

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
    ITournamentBuilder * tournamentBuilder() const override
    {
        return _tournamentBuilder;
    }
    DefaultDataInterface *setTournamentBuilder(ITournamentBuilder *builder) override
    {
        _tournamentBuilder = builder;
        return this;
    }

    IRoundBuilder *roundBuilder() const;
    void setRoundBuilder(IRoundBuilder *roundBuilder);
    ISetBuilder *setBuilder() const;
    void setSetBuilder(ISetBuilder *builder);
    IPointBuilder *pointBuilder() const;

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
