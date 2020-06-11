#ifndef LOCALDATACONTEXT_H
#define LOCALDATACONTEXT_H

#include "idatacontext.h"
#include <quuid.h>
#include <qstring.h>
#include <qlist.h>

#include "modelbuildercollection.h"

#include "igenericdatamodelbuilder.h"
#include "modelbuildercontext.h"

#define THROW_OBJECT_WITH_ID_NOT_FOUND(x) QString("Model with ID: '%1' does not exists in the current context").arg(x).toStdString();
#define THROW_OBJECT_WITH_INDEX_NOT_FOUND(x) QString("Model with index: '%1' does not exists in the current context").arg(x).toStdString();

typedef IDataContext<QUuid,QList<QUuid>,QString> DefaultDataInterface;

class LocalDataContext : public DefaultDataInterface
{
public:
    LocalDataContext();
    
    // IDataContext interface
    QUuid createTournament(const QString &title,
                           const int &maxPlayers,
                           const int &keyPoint,
                           const int &legs,
                           const int &gameMode) override;
    void deleteTournament(const QUuid &tournament) override;
    QUuid tournamentID(const int &index) const override;
    QList<QUuid> tournaments() const override;
    int tournamentsCount() const override;
    QString tournamentTitle(const QUuid &tournament) const override;
    int tournamentNumberOfLegs(const QUuid &tournament) const override;
    int tournamentMaximumAllowedPlayers(const QUuid &tournament) const override;
    QList<QUuid> tournamentAssignedPlayers(const QUuid &tournament) const override;
    int tournamentGameMode(const QUuid &tournament) const override;
    int tournamentKeyPoint(const QUuid &tournament) const override;
    int tournamentStatus(const QUuid &tournament) const override;
    QUuid tournamentDeterminedWinner(const QUuid &tournament) const override;
    void alterTournamentTitle(const QUuid &tournament, const QString &title) override;
    void alterTournamentNumberOfLegs(const QUuid &tournament, const int &value) override;
    void alterTournamentMaxPlayers(const QUuid &tournament, const int &value) override;
    void tournamentAddPlayer(const QUuid &tournament, const QUuid &player) override;
    void tournamentRemovePlayer(const QUuid &tournament, const QUuid &player) override;
    void alterTournamentGameMode(const QUuid &tournament, const int &mode) override;
    void alterTournamentKeyPoint(const QUuid &tournament, const int &value) override;
    void alterTournamentDeterminedWinner(const QUuid &tournament, const QUuid &player) override;

    QList<QUuid> rounds(const QUuid &tournament) const override;
    QUuid round(const QUuid &tournament, const int &roundIndex) const override;
    QUuid addRound(const QUuid &tournament, const int &index) override;
    void alterRoundIndex(const QUuid &tournament, const int &oldIndex,const int &newIndex) override;
    int roundIndex(const QUuid &round) const override;
    QUuid roundTournament(const QUuid &round) const override;

    QList<QUuid> sets(const QUuid &tournament) const override;
    QList<QUuid> sets(const QUuid &tournament, const QUuid &round) const override;
    QList<QUuid> sets(const QUuid &tournament, const int &roundIndex) const override;
    QUuid set(const QUuid &tournament, const int &roundIndex, const int &setIndex) const override;
    QUuid setRound(const QUuid &set) const override;
    int setIndex(const QUuid &set) const override;
    QUuid addSet(const QUuid &tournament, const int &roundIndex, const int &setIndex) override;
    QList<QUuid> points(const QUuid &tournament) const override;
    QList<QUuid> points(const QUuid &tournament, const QUuid &round) const override;
    QList<QUuid> points(const QUuid &tournament, const QUuid &round, const QUuid &set) const override;
    QUuid addPoint(const QUuid &tournament,
                   const int &roundIndex,
                   const int &setIndex,
                   const int &legIndex,
                   const int &point,
                   const QUuid &player) override;
    QUuid alterPointValue(const QUuid &pointId, const int &value) override;
    QUuid alterPointPlayer(const QUuid &pointId, const QUuid &playerId) override;
    QUuid pointSet(const QUuid &point) const override;
    int pointValue(const QUuid &point) const override;
    QUuid pointPlayer(const QUuid &point) const override;
    QList<QUuid> playerPoints(const QUuid &player) const override;
    QList<QUuid> playerPoints(const QUuid &tournament, const QUuid &player) const override;
    QUuid point(const QUuid &tournament, int roundIndex, int setIndex, int legIndex) override;

    DefaultDataInterface *setTournamentBuilder(ITournamentBuilder *builder)
    {
        _tournamentBuilder = builder;
        return this;
    }

private:
    const DefaultTournamentInterface *getTournamentFromID(const QUuid &id) const;
    const DefaultRoundInterface *getRoundFromID(const QUuid &id) const;
    const DefaultSetInterface *getSetFromID(const QUuid &id) const;
    const DefaultPointInterface *getPointFromID(const QUuid &id) const;

    // Removes model with given id. If no model with that id is found, this method does nothing.
    void removeTournamentModel(const QUuid &tournament);
    void removePointModel(const QUuid &point);

    ITournamentBuilder *tournamentBuilder() const;

    IRoundBuilder *roundBuilder() const;
    void setRoundBuilder(IRoundBuilder *roundBuilder);

    ISetBuilder *setBuilder() const;
    IPointBuilder *pointBuilder() const;

    QList<DefaultTournamentInterface*> _tournaments;
    QList<DefaultRoundInterface *> _rounds;
    QList<DefaultSetInterface *> _sets;
    QList<DefaultPointInterface*> _points;

    ITournamentBuilder *_tournamentBuilder;
};

#endif // LOCALDATACONTEXT_H
