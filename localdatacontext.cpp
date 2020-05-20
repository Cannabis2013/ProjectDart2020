#include "localdatacontext.h"

LocalDataContext::LocalDataContext()
{
}

QUuid LocalDataContext::createTournament(const QString &title, const int &maxPlayers, const int &keyPoint, const int &legs, const int &gameMode)
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

void LocalDataContext::deleteTournament(const QUuid &tournament)
{
    removeTournamentModel(tournament);
}

QList<QUuid> LocalDataContext::tournaments() const
{
    QList<QUuid> resultingList;

    for (auto tournament : _tournaments)
    {
        auto id = tournament->id();

        resultingList << id;
    }

    return resultingList;
}

QString LocalDataContext::tournamentTitle(const QUuid &tournament) const
{
    return getTournamentFromID(tournament)->title();
}

int LocalDataContext::tournamentNumberOfLegs(const QUuid &tournament) const
{
    return getTournamentFromID(tournament)->numberOfLegs();
}

int LocalDataContext::tournamentMaximumAllowedPlayers(const QUuid &tournament) const
{
    return getTournamentFromID(tournament)->numberOfMaxAllowedPlayers();
}

QList<QUuid> LocalDataContext::tournamentAssignedPlayers(const QUuid &tournament) const
{
    return getTournamentFromID(tournament)->assignedPlayerIdentities();
}

int LocalDataContext::tournamentGameMode(const QUuid &tournament) const
{
    return getTournamentFromID(tournament)->gameMode();
}

int LocalDataContext::tournamentKeyPoint(const QUuid &tournament) const
{
    return getTournamentFromID(tournament)->keyPoint();
}

int LocalDataContext::tournamentStatus(const QUuid &tournament) const
{
    return getTournamentFromID(tournament)->status();
}

QUuid LocalDataContext::tournamentDeterminedWinner(const QUuid &tournament) const
{
    return getTournamentFromID(tournament)->winner();
}

void LocalDataContext::alterTournamentTitle(const QUuid &tournament, const QString &title)
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

void LocalDataContext::alterTournamentNumberOfLegs(const QUuid &tournament, const int &value)
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

void LocalDataContext::alterTournamentMaxPlayers(const QUuid &tournament, const int &value)
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

void LocalDataContext::tournamentAddPlayer(const QUuid &tournament, const QUuid &player)
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

void LocalDataContext::tournamentRemovePlayer(const QUuid &tournament, const QUuid &player)
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

void LocalDataContext::alterTournamentGameMode(const QUuid &tournament, const int &mode)
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

void LocalDataContext::alterTournamentKeyPoint(const QUuid &tournament, const int &value)
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

void LocalDataContext::alterTournamentDeterminedWinner(const QUuid &tournament, const QUuid &player)
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

QList<QUuid> LocalDataContext::rounds(const QUuid &tournament) const
{
    QList<QUuid> resultingList;
    for (auto r : _rounds) {
        if(r->tournament() == tournament)
            resultingList << r->id();
    }

    return resultingList;
}

QUuid LocalDataContext::round(const QUuid &tournament, const int &roundIndex) const
{
    for (auto model : _rounds)
    {
        if(model->tournament() == tournament && model->index() == roundIndex)
            return model->id();
    }

    throw THROW_OBJECT_WITH_INDEX_NOT_FOUND(roundIndex);
}

QUuid LocalDataContext::addRound(const QUuid &tournament, const int &index)
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

void LocalDataContext::alterRoundIndex(const QUuid &tournament, const int &oldIndex, const int &newIndex)
{
    // This method is subject for a critical review as I fail to come up with a reason to alter round indexes
}

int LocalDataContext::roundIndex(const QUuid &round) const
{
    return getRoundFromID(round)->index();
}

QUuid LocalDataContext::roundTournament(const QUuid &round) const
{

    return getRoundFromID(round)->tournament();
}

QList<QUuid> LocalDataContext::sets(const QUuid &tournament) const
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

QList<QUuid> LocalDataContext::sets(const QUuid &tournament, const QUuid &round) const
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

QList<QUuid> LocalDataContext::sets(const QUuid &tournament, const int &roundIndex) const
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

QUuid LocalDataContext::set(const QUuid &tournament, const int &roundIndex, const int &setIndex) const
{
    auto sets = this->sets(tournament,roundIndex);
    for (auto s : sets) {
        if(this->setIndex(s) == setIndex)
            return s;
    }

    return QUuid();
}

QUuid LocalDataContext::setRound(const QUuid &set) const
{
    return getSetFromID(set)->round();
}

int LocalDataContext::setIndex(const QUuid &set) const
{
    return getSetFromID(set)->index();
}

QUuid LocalDataContext::addSet(const QUuid &tournament, const int &roundIndex, const int &setIndex)
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

QList<QUuid> LocalDataContext::points(const QUuid &tournament) const
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

QList<QUuid> LocalDataContext::points(const QUuid &tournament, const QUuid &round) const
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

QList<QUuid> LocalDataContext::points(const QUuid &tournament, const QUuid &round, const QUuid &set) const
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

QUuid LocalDataContext::addPoint(const QUuid &tournament, const int &roundIndex, const int &setIndex, const int &legIndex, const int &point, const QUuid &player)
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

QUuid LocalDataContext::alterPointValue(const QUuid &pointId, const int &value)
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

QUuid LocalDataContext::alterPointPlayer(const QUuid &pointId, const QUuid &playerId)
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

QUuid LocalDataContext::pointSet(const QUuid &point) const
{
    return getPointFromID(point)->set();
}

int LocalDataContext::pointValue(const QUuid &point) const
{
    return getPointFromID(point)->point();
}

QUuid LocalDataContext::pointPlayer(const QUuid &point) const
{
    return getPointFromID(point)->player();
}

QList<QUuid> LocalDataContext::playerPoints(const QUuid &player) const
{
    QList<QUuid> resultingList;

    for (auto point : _points) {
        if(point->player() == player)
            resultingList << player;
    }

    return resultingList;
}

QList<QUuid> LocalDataContext::playerPoints(const QUuid &tournament, const QUuid &player) const
{
    QList<QUuid> resultingList;
    auto tPoints = points(tournament);
    for (auto pointID : tPoints) {
        if(getPointFromID(pointID)->player() == player)
            resultingList << pointID;
    }

    return resultingList;
}

QUuid LocalDataContext::point(const QUuid &tournament, int roundIndex, int setIndex, int legIndex)
{

}

const DefaultTournamentInterface *LocalDataContext::getTournamentFromID(const QUuid &id) const
{
    for (auto tournament : _tournaments) {
        if(tournament->id() == id)
            return tournament;
    }

    throw THROW_OBJECT_WITH_ID_NOT_FOUND(id.toString());
}

const DefaultRoundInterface *LocalDataContext::getRoundFromID(const QUuid &id) const
{
    for (auto round : _rounds) {
        if(round->id() == id)
            return round;
    }

    throw THROW_OBJECT_WITH_ID_NOT_FOUND(id.toString());
}

const DefaultSetInterface *LocalDataContext::getSetFromID(const QUuid &id) const
{
    for (auto set : _sets)
    {
        if(set->id() == id)
            return set;
    }

    throw THROW_OBJECT_WITH_ID_NOT_FOUND(id.toString());
}

const DefaultPointInterface *LocalDataContext::getPointFromID(const QUuid &id) const
{
    for (auto point : _points)
    {
        if(point->id() == id)
            return point;
    }

    throw THROW_OBJECT_WITH_ID_NOT_FOUND(id.toString());
}

void LocalDataContext::removeTournamentModel(const QUuid &tournament)
{
    for (int i = 0; i < _tournaments.count(); ++i) {
        auto model = _tournaments.at(i);
        auto id = model->id();
        if(id == tournament)
        {
            _tournaments.removeAt(i);
            return;
        }
    }
}

void LocalDataContext::removePointModel(const QUuid &point)
{
    for (int i = 0; i < _points.count(); ++i) {
        auto model = _points.at(i);
        auto id = model->id();
        if(id == point)
        {
            _points.removeAt(i);
            return;
        }
    }
}

ITournamentBuilder *LocalDataContext::tournamentBuilder() const
{

}

IRoundBuilder *LocalDataContext::roundBuilder() const
{

}

ISetBuilder *LocalDataContext::setBuilder() const
{

}

IPointBuilder *LocalDataContext::pointBuilder() const
{

}
