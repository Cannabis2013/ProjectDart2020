#ifndef LOCALDATACONTEXT_H
#define LOCALDATACONTEXT_H

#include "idatacontext.h"
#include <quuid.h>
#include <qstring.h>
#include <qlist.h>

#include "modelbuildercollection.h"

#define THROW_OBJECT_WITH_ID_NOT_FOUND(x) QString("Model with ID: '%1' does not exists in the current context").arg(x).toStdString();
#define THROW_OBJECT_WITH_INDEX_NOT_FOUND(x) QString("Model with index: '%1' does not exists in the current context").arg(x).toStdString();

typedef IDataContext<QUuid,QList<QUuid>,QString,ITournamentBuilder> DefaultDataInterface;

class LocalDataContext : public DefaultDataInterface
{
public:
    /*
     * Public types
     */
    enum ModelDisplayHint{HiddenHint = 0x1,DisplayHint = 0x2, allHints = 0x4};
    /*
     * Tournament related section
     */
    QUuid createTournament(const QString &title,
                           const int &maxPlayers,
                           const int &keyPoint,
                           const int &throws,
                           const int &gameMode) override;
    void deleteTournament(const QUuid &tournament) override;
    QUuid tournamentID(const int &index) const override;
    QList<QUuid> tournaments() const override;
    int tournamentsCount() const override;
    QString tournamentTitle(const QUuid &tournament) const override;
    int tournamentNumberOfThrows(const QUuid &tournament) const override;
    int tournamentMaximumAllowedPlayers(const QUuid &tournament) const override;
    QList<QUuid> tournamentAssignedPlayers(const QUuid &tournament) const override;
    int tournamentGameMode(const QUuid &tournament) const override;
    int tournamentKeyPoint(const QUuid &tournament) const override;
    int tournamentStatus(const QUuid &tournament) const override;
    QUuid tournamentDeterminedWinner(const QUuid &tournament) const override;
    bool tournamentExists(const QUuid &tournament) const override;
    void tournamentAddPlayer(const QUuid &tournament, const QUuid &player) override;
    void tournamentRemovePlayer(const QUuid &tournament, const QUuid &player) override;
    void removeTournament(const QUuid &tournament) override;
    void removeTournamentModels(const QUuid &tournament) override;
    void alterTournamentTitle(const QUuid &tournament, const QString &title) override;
    void alterTournamentNumberOfLegs(const QUuid &tournament, const int &value) override;
    void alterTournamentMaxPlayers(const QUuid &tournament, const int &value) override;
    void alterTournamentGameMode(const QUuid &tournament, const int &mode) override;
    void alterTournamentKeyPoint(const QUuid &tournament, const int &value) override;
    void alterTournamentDeterminedWinner(const QUuid &tournament, const QUuid &player) override;
    /*
     * Round related section
     */
    QList<QUuid> roundsID(const QUuid &tournament) const override;
    QUuid roundID(const QUuid &tournament, const int &roundIndex) const override;
    QUuid addRound(const QUuid &tournament, const int &index) override;
    void alterRoundIndex(const QUuid &, const int &, const int &) override;
    int roundIndex(const QUuid &roundID) const override;
    QUuid roundTournament(const QUuid &roundID) const override;
    /*
     * Set related section
     */
    QList<QUuid> tournamentSetsID(const QUuid &tournament) const override;
    QList<QUuid> roundSetsID(const QUuid &roundID) const override;
    QList<QUuid> tournamentSetsID(const QUuid &tournament, const int &roundIndex) const override;
    QUuid setID(const QUuid &tournament, const int &roundIndex, const int &setIndex) const override;
    QUuid setRound(const QUuid &setID) const override;
    int setIndex(const QUuid &setID) const override;
    QUuid addSet(const QUuid &tournament, const int &roundIndex, const int &setIndex) override;
    QList<QUuid> setPointsID(const QUuid &setID) const override;
    /*
     * Point related section
     */
    QList<QUuid> points(const QUuid &tournament) const override;
    QList<QUuid> points(const QUuid &tournament, const QUuid &roundID) const override;
    QList<QUuid> points(const QUuid &tournament, const QUuid &roundID, const QUuid &setID) const override;
    QUuid addPoint(const QUuid &tournament, const QUuid &player,
                   const int &roundIndex,
                   const int &setIndex,
                   const int &legIndex,
                   const int &playerPoint) override;
    QUuid setPointHint(const QUuid &point, const int &hint) override;
    QUuid editPointValue(const QUuid &pointId, const int &value, const int &hint) override;
    QUuid alterPointPlayer(const QUuid &pointId, const QUuid &playerId) override;
    QUuid pointSet(const QUuid &playerPoint) const override;
    int pointLeg(const QUuid &playerPoint) const override;
    int pointValue(const QUuid &playerPoint) const override;
    QUuid pointPlayer(const QUuid &playerPoint) const override;
    int pointHint(const QUuid &playerPoint) const override;
    QUuid playerPoint(const QUuid &tournament, const QUuid &player , const int &roundIndex, const int &legIndex, const int &hint) override;
    QList<QUuid> playerPoints(const QUuid &tournament, const QUuid &player, const int &hint) const override;
    bool removePlayerPoint(const QUuid &point) override;
    void removePlayerPointAndRelatives(const QUuid &point) override;
    DefaultDataInterface *setTournamentBuilder(ITournamentBuilder *builder) override;
    ITournamentBuilder *tournamentBuilder() const override;
    int playerPointsCount(const int &hint) const override;

private:
    QList<QUuid> pointModels(const QUuid &player) const;
    void removeEmptyRound(const QUuid &round);
    void removeEmptySet(const QUuid &setID);
    const DefaultTournamentInterface *getTournamentFromID(const QUuid &id) const;
    const DefaultRoundInterface *getRoundFromID(const QUuid &id) const;
    const DefaultSetInterface *getSetFromID(const QUuid &id) const;
    const DefaultPointInterface *getPointFromID(const QUuid &id) const;
    // Removes model with given id. If no model with that id is found, this method does nothing.
    void removeTournamentModel(const QUuid &tournament);
    void removePointModel(const QUuid &playerPoint);
    // Builder methods
    IRoundBuilder *roundBuilder() const;
    void setRoundBuilder(IRoundBuilder *roundBuilder);
    ISetBuilder *setBuilder() const;
    void setSetBuilder(ISetBuilder *builder);
    IPointBuilder *pointBuilder() const;
    // Builders
    ITournamentBuilder *_tournamentBuilder = new TournamentBuilder();
    IRoundBuilder *_roundBuilder = new RoundBuilder();
    ISetBuilder *_setBuilder = new SetBuilder();
    IPointBuilder *_pointBuilder = new PointBuilder();
    //Models
    QList<const DefaultTournamentInterface*> _tournaments;
    QList<const DefaultRoundInterface *> _rounds;
    QList<const DefaultSetInterface *> _sets;
    QList<const DefaultPointInterface*> _points;
};

#endif // LOCALDATACONTEXT_H
