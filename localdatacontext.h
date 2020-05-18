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
    LocalDataContext()
    {
    }
    
    // IDataContext interface
    QUuid createTournament(const QString &title,
                           const int &maxPlayers,
                           const int &keyPoint,
                           const int &legs,
                           const int &gameMode) override
    {
        auto tournament = tournamentBuilder()->buildModel(
                    [title,maxPlayers,keyPoint,legs,gameMode]
        {
            TournamentParameters params;

            params.title = title;
            params.numberOfLegs = legs;
            params.maxPlayers = maxPlayers;
            params.keyPoint = keyPoint;
            params.gameMode = gameMode;

            return params;
        }(),[]
        {
            ModelOptions options;

            options.generateUniqueId = true;

            return options;

        }());

        _tournaments.append(tournament);

        return tournament->id();
    }
    void deleteTournament(const QUuid &tournament) override
    {
        removeTournamentModel(tournament);
    }
    QList<QUuid> tournaments() const override
    {
        QList<QUuid> resultingList;

        for (auto tournament : _tournaments)
        {
            auto id = tournament->id();

            resultingList << id;
        }

        return resultingList;
    }
    QString tournamentTitle(const QUuid &tournament) const override
    {
        return getTournamentFromID(tournament)->title();
    }
    int tournamentNumberOfLegs(const QUuid &tournament) const override
    {
        return getTournamentFromID(tournament)->numberOfLegs();
    }
    int tournamentMaximumAllowedPlayers(const QUuid &tournament) const override
    {
        return getTournamentFromID(tournament)->numberOfMaxAllowedPlayers();
    }
    QList<QUuid> tournamentAssignedPlayers(const QUuid &tournament) const override
    {
        return getTournamentFromID(tournament)->assignedPlayerIdentities();
    }
    int tournamentGameMode(const QUuid &tournament) const override
    {
        return getTournamentFromID(tournament)->gameMode();
    }
    int tournamentKeyPoint(const QUuid &tournament) const override
    {
        return getTournamentFromID(tournament)->keyPoint();
    }
    int tournamentStatus(const QUuid &tournament) const override
    {
        return getTournamentFromID(tournament)->status();
    }
    QUuid tournamentDeterminedWinner(const QUuid &tournament) const override
    {
        return getTournamentFromID(tournament)->winner();
    }
    void alterTournamentTitle(const QUuid &tournament, const QString &title) override
    {
        auto model = getTournamentFromID(tournament);

        auto newModel = tournamentBuilder()->buildModel(
                        [model, title]
                        {
                            TournamentParameters params;

                            params.id = model->id();
                            params.title = title;
                            params.status = model->status();
                            params.gameMode = model->gameMode();
                            params.keyPoint = model->keyPoint();
                            params.maxPlayers = model->numberOfMaxAllowedPlayers();
                            params.playerIdentities = model->assignedPlayerIdentities();
                            params.numberOfLegs = model->numberOfLegs();
                            params.winner = model->winner();

                            return params;
                        }(),[]
                        {
                            ModelOptions options;

                            options.generateUniqueId = false;

                            return options;
                        }());

        removeTournamentModel(model->id());

        _tournaments.append(newModel);
    }
    void alterTournamentNumberOfLegs(const QUuid &tournament, const int &value) override
    {
        auto model = getTournamentFromID(tournament);

        auto newModel = tournamentBuilder()->buildModel(
                        [model, value]
                        {
                            TournamentParameters params;

                            params.id = model->id();
                            params.title = model->title();
                            params.status = model->status();
                            params.gameMode = model->gameMode();
                            params.keyPoint = model->keyPoint();
                            params.maxPlayers = model->numberOfMaxAllowedPlayers();
                            params.playerIdentities = model->assignedPlayerIdentities();
                            params.numberOfLegs = value;
                            params.winner = model->winner();

                            return params;
                        }(),[]
                        {
                            ModelOptions options;

                            options.generateUniqueId = false;

                            return options;
                        }());

        removeTournamentModel(model->id());

        _tournaments.append(newModel);
    }
    void alterTournamentMaxPlayers(const QUuid &tournament, const int &value) override
    {
        auto model = getTournamentFromID(tournament);

        auto newModel = tournamentBuilder()->buildModel(
                        [model, value]
                        {
                            TournamentParameters params;

                            params.id = model->id();
                            params.title = model->title();
                            params.status = model->status();
                            params.gameMode = model->gameMode();
                            params.keyPoint = model->keyPoint();
                            params.maxPlayers = value;
                            params.playerIdentities = model->assignedPlayerIdentities();
                            params.numberOfLegs = model->numberOfLegs();
                            params.winner = model->winner();

                            return params;
                        }(),[]
                        {
                            ModelOptions options;

                            options.generateUniqueId = false;

                            return options;
                        }());

        removeTournamentModel(model->id());


        _tournaments.append(newModel);
    }
    void tournamentAddPlayer(const QUuid &tournament, const QUuid &player) override
    {
        auto model = getTournamentFromID(tournament);
        auto pList = model->assignedPlayerIdentities();
        pList.append(player);
        auto newModel = tournamentBuilder()->buildModel(
                        [model, pList]
                        {
                            TournamentParameters params;

                            params.id = model->id();
                            params.title = model->title();
                            params.status = model->status();
                            params.gameMode = model->gameMode();
                            params.keyPoint = model->keyPoint();
                            params.maxPlayers = model->numberOfMaxAllowedPlayers();
                            params.playerIdentities = model->assignedPlayerIdentities();
                            params.numberOfLegs = model->numberOfLegs();
                            params.winner = model->winner();
                            params.playerIdentities = pList;

                            return params;
                        }(),[]
                        {
                            ModelOptions options;

                            options.generateUniqueId = false;

                            return options;
                        }());

        removeTournamentModel(model->id());

        _tournaments.append(newModel);
    }
    void tournamentRemovePlayer(const QUuid &tournament, const QUuid &player) override
    {
        auto model = getTournamentFromID(tournament);

        auto pList = model->assignedPlayerIdentities();
        pList.removeOne(player);

        auto newModel = tournamentBuilder()->buildModel(
                        [model, pList]
                        {
                            TournamentParameters params;

                            params.id = model->id();
                            params.title = model->title();
                            params.status = model->status();
                            params.gameMode = model->gameMode();
                            params.keyPoint = model->keyPoint();
                            params.maxPlayers = model->numberOfMaxAllowedPlayers();
                            params.playerIdentities = model->assignedPlayerIdentities();
                            params.numberOfLegs = model->numberOfLegs();
                            params.winner = model->winner();
                            params.playerIdentities = pList;

                            return params;
                        }(),[]
                        {
                            ModelOptions options;

                            options.generateUniqueId = false;

                            return options;
                        }());

        removeTournamentModel(model->id());

        _tournaments.append(newModel);
    }
    void alterTournamentGameMode(const QUuid &tournament, const int &mode) override
    {
        auto model = getTournamentFromID(tournament);

        auto newModel = tournamentBuilder()->buildModel(
                        [model, mode]
                        {
                            TournamentParameters params;

                            params.id = model->id();
                            params.title = model->title();
                            params.status = model->status();
                            params.gameMode = mode;
                            params.keyPoint = model->keyPoint();
                            params.maxPlayers = model->numberOfMaxAllowedPlayers();
                            params.playerIdentities = model->assignedPlayerIdentities();
                            params.numberOfLegs = model->numberOfLegs();
                            params.winner = model->winner();

                            return params;
                        }(),[]
                        {
                            ModelOptions options;

                            options.generateUniqueId = false;

                            return options;
                        }());

        removeTournamentModel(model->id());

        _tournaments.append(newModel);
    }
    void alterTournamentKeyPoint(const QUuid &tournament, const int &value) override
    {
        auto model = getTournamentFromID(tournament);

        auto newModel = tournamentBuilder()->buildModel(
                        [model, value]
                        {
                            TournamentParameters params;

                            params.id = model->id();
                            params.title = model->title();
                            params.status = model->status();
                            params.gameMode = model->gameMode();
                            params.keyPoint = value;
                            params.maxPlayers = model->numberOfMaxAllowedPlayers();
                            params.numberOfLegs = model->numberOfLegs();
                            params.playerIdentities = model->assignedPlayerIdentities();
                            params.winner = model->winner();

                            return params;
                        }(),[]
                        {
                            ModelOptions options;

                            options.generateUniqueId = false;

                            return options;
                        }());

        removeTournamentModel(model->id());

        _tournaments.append(newModel);
    }
    void alterTournamentDeterminedWinner(const QUuid &tournament, const QUuid &player) override
    {
        auto model = getTournamentFromID(tournament);

        auto newModel = tournamentBuilder()->buildModel(
                        [model, player]
                        {
                            TournamentParameters params;

                            params.id = model->id();
                            params.title = model->title();
                            params.status = model->status();
                            params.gameMode = model->gameMode();
                            params.keyPoint = model->keyPoint();
                            params.maxPlayers = model->numberOfMaxAllowedPlayers();
                            params.numberOfLegs = model->numberOfLegs();
                            params.playerIdentities = model->assignedPlayerIdentities();
                            params.winner = player;

                            return params;
                        }(),[]
                        {
                            ModelOptions options;

                            options.generateUniqueId = false;

                            return options;
                        }());

        removeTournamentModel(model->id());

        _tournaments.append(newModel);
    }
    QList<QUuid> rounds(const QUuid &tournament) const override
    {
        QList<QUuid> resultingList;
        for (auto r : _rounds) {
            if(r->tournament() == tournament)
                resultingList << r->id();
        }

        return resultingList;
    }
    QUuid round(const QUuid &tournament, const int &roundIndex) const override
    {
        for (auto model : _rounds)
        {
            if(model->tournament() == tournament && model->index() == roundIndex)
                return model->id();
        }

        throw THROW_OBJECT_WITH_INDEX_NOT_FOUND(roundIndex);
    }
    QUuid addRound(const QUuid &tournament, const int &index) override
    {
        auto round = roundBuilder()->buildModel(
                    [tournament,index]
        {
            RoundParameters params;

            params.tournamentId = tournament;
            params.roundIndex = index;

            return params;
        }(),[]
        {
            ModelOptions options;

            options.generateUniqueId = true;

            return options;
        }());

        auto roundId = round->id();

        _rounds.append(round);

        return roundId;
    }
    void alterRoundIndex(const QUuid &tournament, const int &oldIndex,const int &newIndex) override
    {
        // This method is subject for a critical review as I fail to come up with a reason to alter round indexes
    }
    int roundIndex(const QUuid &round) const override
    {
        return getRoundFromID(round)->index();
    }
    QUuid roundTournament(const QUuid &round) const override
    {

        return getRoundFromID(round)->tournament();
    }

    QList<QUuid> sets(const QUuid &tournament) const override
    {
        QList<QUuid> resultingList;
        for (auto model : _sets) {
            auto r = getRoundFromID(model->round());
            auto t = getTournamentFromID(r->tournament());
            auto tId = t->id();
            if(tId == tournament)
                resultingList << tId;
        }

        return resultingList;
    }
    QList<QUuid> sets(const QUuid &tournament, const QUuid &round) const override
    {
        QList<QUuid> resultingList;
        for (auto model : _sets) {
            auto r = getRoundFromID(model->round());
            auto rId = r->id();;
            auto t = getTournamentFromID(r->tournament());
            auto tId = t->id();
            if(tId == tournament && rId == round)
                resultingList << tId;
        }

        return resultingList;
    }
    QList<QUuid> sets(const QUuid &tournament, const int &roundIndex) const override
    {
        QList<QUuid> resultingList;
        for (auto model : _sets) {
            auto r = getRoundFromID(model->round());
            auto rIndex = r->index();;
            auto t = getTournamentFromID(r->tournament());
            auto tId = t->id();
            if(tId == tournament && rIndex == roundIndex)
                resultingList << tId;
        }

        return resultingList;
    }
    QUuid set(const QUuid &tournament, const int &roundIndex, const int &setIndex) const override
    {
        auto sets = this->sets(tournament,roundIndex);
        for (auto s : sets) {
            if(this->setIndex(s) == setIndex)
                return s;
        }

        return QUuid();
    }
    QUuid setRound(const QUuid &set) const override
    {
        return getSetFromID(set)->round();
    }
    int setIndex(const QUuid &set) const override
    {
        return getSetFromID(set)->index();
    }
    QUuid addSet(const QUuid &tournament, const int &roundIndex, const int &setIndex) override
    {
        auto roundId = round(tournament,roundIndex);
        auto model = setBuilder()->buildModel(
                    [roundId,setIndex]{
            SetParameters params;

            params.roundId = roundId;
            params.index = setIndex;

            return params;
        }(),[]
        {
            ModelOptions options;

            options.generateUniqueId = true;

            return options;
        }());

        _sets << model;
    }
    QList<QUuid> points(const QUuid &tournament) const override
    {
        QList<QUuid> resultingList;
        for (auto pointModel : _points) {
            auto setModel = getSetFromID(pointModel->set());
            auto roundModel = getRoundFromID(setModel->round());
            auto tournamentModel = getTournamentFromID(roundModel->tournament());
            if(tournamentModel->id() == tournament)
               resultingList << pointModel->id();
        }

        return resultingList;
    }
    QList<QUuid> points(const QUuid &tournament, const QUuid &round) const override
    {
        QList<QUuid> resultingList;
        auto tPoints = this->points(tournament);
        for (auto pointID : tPoints) {
            auto s = this->pointSet(pointID);
            auto r = this->setRound(s);
            if(r == round)
                resultingList << pointID;
        }

        return resultingList;
    }
    QList<QUuid> points(const QUuid &tournament, const QUuid &round, const QUuid &set) const override
    {
        QList<QUuid> resultingList;
        auto p = this->points(tournament,round);
        for (auto pointID : p) {
            auto setID = pointSet(pointID);
            if(setID == set)
                resultingList << pointID;
        }

        return resultingList;
    }
    QUuid addPoint(const QUuid &tournament,
                   const int &roundIndex,
                   const int &setIndex,
                   const int &legIndex,
                   const int &point,
                   const QUuid &player) override
    {
        auto model = pointBuilder()->buildModel(
                    [this,tournament,roundIndex,setIndex,legIndex,point,player]
        {
            PointParameters params;

            auto sId = this->set(tournament,roundIndex,setIndex);

            params.setId = sId;
            params.playerId = player;
            params.pointValue = point;
            params.legIndex = legIndex;

            return params;
        }(),ModelOptions());

        _points.append(model);

        return model->id();
    }
    QUuid alterPointValue(const QUuid &pointId, const int &value) override
    {
        auto model = getPointFromID(pointId);

        auto newModel = pointBuilder()->buildModel(
                        [model, value]
                        {
                            PointParameters params;

                            params.id = model->id();
                            params.setId = model->set();
                            params.pointValue = value;
                            params.playerId = model->player();

                            return params;
                        }(),[]
                        {
                            ModelOptions options;

                            options.generateUniqueId = false;

                            return options;
                        }());

        removePointModel(model->id());

        _points.append(newModel);

        return newModel->id();
    }
    QUuid alterPointPlayer(const QUuid &pointId, const QUuid &playerId) override
    {
        auto model = getPointFromID(pointId);

        auto newModel = pointBuilder()->buildModel(
                        [model, playerId]
                        {
                            PointParameters params;

                            params.id = model->id();
                            params.setId = model->set();
                            params.pointValue = model->point();
                            params.playerId = playerId;

                            return params;
                        }(),[]
                        {
                            ModelOptions options;

                            options.generateUniqueId = false;

                            return options;
                        }());

        removePointModel(model->id());

        _points.append(newModel);
    }
    QUuid pointSet(const QUuid &point) const override
    {
        return getPointFromID(point)->set();
    }
    int pointValue(const QUuid &point) const override
    {
        return getPointFromID(point)->point();
    }
    QUuid pointPlayer(const QUuid &point) const override
    {
        return getPointFromID(point)->player();
    }
    QList<QUuid> playerPoints(const QUuid &player) const override
    {
        QList<QUuid> resultingList;

        for (auto point : _points) {
            if(point->player() == player)
                resultingList << player;
        }

        return resultingList;
    }
    QList<QUuid> playerPoints(const QUuid &tournament, const QUuid &player) const override
    {
        QList<QUuid> resultingList;
        auto tPoints = points(tournament);
        for (auto pointID : tPoints) {
            if(getPointFromID(pointID)->player() == player)
                resultingList << pointID;
        }

        return resultingList;
    }

    LocalDataContext *setTournamentBuilder(ITournamentBuilder *builder)
    {

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
