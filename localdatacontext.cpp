#include "localdatacontext.h"

QUuid LocalDataContext::createTournament(const QString &title, const int &maxPlayers, const int &keyPoint, const int &throws, const int &gameMode)
{
    auto tournament = tournamentBuilder()->buildModel([this,title,maxPlayers,keyPoint,throws,gameMode]{
        TournamentParameters params;

        params.title = title;
        params.numberOfLegs = throws;
        params.maxPlayers = maxPlayers;
        params.keyPoint = keyPoint;
        params.gameMode = gameMode;
        params.tournamentsCount = this->tournamentsCount();
        return params;
    }(),[]{
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

QUuid LocalDataContext::tournamentID(const int &index) const
{
    auto tournament = _tournaments.at(index);
    auto id = tournament->id();

    return id;
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

int LocalDataContext::tournamentsCount() const
{
    return _tournaments.count();
}

QString LocalDataContext::tournamentTitle(const QUuid &tournament) const
{
    return getTournamentFromID(tournament)->title();
}

int LocalDataContext::tournamentNumberOfThrows(const QUuid &tournament) const
{
    return getTournamentFromID(tournament)->numberOfThrows();
}

int LocalDataContext::tournamentMaximumAllowedPlayers(const QUuid &tournament) const
{
    return getTournamentFromID(tournament)->numberOfMaxAllowedPlayers();
}

QList<QUuid> LocalDataContext::tournamentAssignedPlayers(const QUuid &tournament) const
{
    QList<QUuid> assignedPlayers;
    try {
        assignedPlayers = getTournamentFromID(tournament)->assignedPlayerIdentities();
    } catch (const char *msg) {
        throw  msg;
    }
    return assignedPlayers;
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
        params.numberOfLegs = model->numberOfThrows();
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
        params.numberOfLegs = model->numberOfThrows();
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
        params.numberOfLegs = model->numberOfThrows();
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
        params.numberOfLegs = model->numberOfThrows();
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

void LocalDataContext::removeTournament(const QUuid &tournament)
{
    removeTournamentModels(tournament);

    for (int i = 0; i < _tournaments.count(); ++i) {
        auto tournamentModel = _tournaments.at(i);
        auto tournamentID = tournamentModel->id();
        if(tournamentID == tournament)
            _tournaments.removeAt(i);
    }
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
        params.numberOfLegs = model->numberOfThrows();
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
        params.numberOfLegs = model->numberOfThrows();
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
        params.numberOfLegs = model->numberOfThrows();
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

QList<QUuid> LocalDataContext::roundsID(const QUuid &tournament) const
{
    QList<QUuid> resultingList;
    for (auto r : _rounds) {
        if(r->parent() == tournament)
            resultingList << r->id();
    }

    return resultingList;
}

QUuid LocalDataContext::roundID(const QUuid &tournament, const int &roundIndex) const
{
    for (auto model : _rounds)
    {
        if(model->parent() == tournament && model->index() == roundIndex)
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

void LocalDataContext::removeEmptyRound(const QUuid &round)
{
    auto roundModel = getRoundFromID(round);
    auto children = roundSetsID(round);
    auto childrenCount = children.count();
    if(childrenCount >0)
        return;
    _rounds.removeOne(roundModel);
}

void LocalDataContext::removeEmptySet(const QUuid &set)
{
    auto setModel = getSetFromID(set);
    auto children = setPointsID(set);
    auto childrenCount = children.count();
    if(childrenCount > 0)
        return;
    _sets.removeOne(setModel);
    auto parentRoundID = setModel->parent();
    removeEmptyRound(parentRoundID);

}

void LocalDataContext::alterRoundIndex(const QUuid &, const int &, const int &)
{
    // This method is subject for a critical review as I fail to come up with any reason to alter round indexes
}

int LocalDataContext::roundIndex(const QUuid &round) const
{
    try {
        return getRoundFromID(round)->index();
    } catch (const char *msg) {
        throw msg;
    }
}

QUuid LocalDataContext::roundTournament(const QUuid &round) const
{
    auto model = getRoundFromID(round);
    auto parentID = model->parent();
    return parentID;
}

QList<QUuid> LocalDataContext::tournamentSetsID(const QUuid &tournament) const
{
    QList<QUuid> resultingList;
    for (auto model : _sets) {
        auto setID = model->id();
        auto roundModel = getRoundFromID(model->parent());
        auto tournamentModel = getTournamentFromID(roundModel->parent());
        auto tournamentID = tournamentModel->id();
        if(tournamentID == tournament)
            resultingList << setID;
    }
    return resultingList;
}

QList<QUuid> LocalDataContext::roundSetsID(const QUuid &round) const
{
    QList<QUuid> resultingList;
    for (auto model : _sets) {
        auto roundSetID = model->id();
        auto roundModel = getRoundFromID(model->parent());
        auto roundID = roundModel->id();
        if(roundID == round)
            resultingList << roundSetID;
    }
    return resultingList;
}

QList<QUuid> LocalDataContext::tournamentSetsID(const QUuid &tournament, const int &roundIndex) const
{
    QList<QUuid> resultingList;
    for (auto model : _sets) {
        auto round = getRoundFromID(model->parent());
        auto modelRoundIndex = round->index();;
        auto t = getTournamentFromID(round->parent());
        auto tournamentID = t->id();
        if(tournamentID == tournament && modelRoundIndex == roundIndex)
            resultingList << model->id();
    }

    return resultingList;
}

QUuid LocalDataContext::setID(const QUuid &tournament, const int &roundIndex, const int &setIndex) const
{
    auto sets = this->tournamentSetsID(tournament,roundIndex);
    for (auto s : sets) {
        auto index = this->setIndex(s);
        if(index == setIndex)
            return s;
    }
    throw THROW_OBJECT_WITH_INDEX_NOT_FOUND(setIndex);
}

QUuid LocalDataContext::setRound(const QUuid &set) const
{
    try {
        auto setModel = getSetFromID(set);
        auto parentID = setModel->parent();
        return parentID;

    } catch (const char *msg) {
        throw msg;
    }
}

int LocalDataContext::setIndex(const QUuid &set) const
{
    try {
        auto model = getSetFromID(set);
        return model->index();
    } catch (const char *msg) {
        throw msg;
    }
}

QUuid LocalDataContext::addSet(const QUuid &tournament, const int &roundIndex, const int &setIndex)
{
    auto roundId = roundID(tournament,roundIndex);
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

    return model->id();
}

QList<QUuid> LocalDataContext::setPointsID(const QUuid &set) const
{
    QList<QUuid> resultingList;
    for (auto pointModel : _points) {
        auto pointSetID = pointModel->parent();
        if(pointSetID == set)
            resultingList << pointSetID;
    }
    return resultingList;
}

QList<QUuid> LocalDataContext::points(const QUuid &tournament) const
{
    QList<QUuid> resultingList;
    for (auto pointModel : _points) {
        auto parentSetID = pointModel->parent();
        auto setModel = getSetFromID(parentSetID);
        auto parentRoundID = setModel->parent();
        auto roundModel = getRoundFromID(parentRoundID);
        auto parentTournamentID = roundModel->parent();
        auto tournamentModel = getTournamentFromID(parentTournamentID);
        auto compareTournamentID = tournamentModel->id();
        if(compareTournamentID == tournament)
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

QUuid LocalDataContext::addPoint(const QUuid &tournament,const QUuid &player, const int &roundIndex, const int &setIndex, const int &legIndex, const int &point)
{
    try {
        auto pointID = playerPoint(tournament,player,roundIndex,legIndex,HiddenHint);
        editPointValue(pointID,point,DisplayHint);
        return pointID;

    } catch (...) {
        auto model = pointBuilder()->buildModel(
                    [this,tournament,roundIndex,setIndex,legIndex,point,player]
        {
            PointParameters params;
            auto setId = this->setID(tournament,roundIndex,setIndex);
            params.setId = setId;
            params.playerId = player;
            params.pointValue = point;
            params.legIndex = legIndex;

            return params;
        }(),ModelOptions());

        _points.append(model);

        return model->id();
    }
}

QUuid LocalDataContext::setPointHint(const QUuid &point, const int &hint)
{
    auto pointModel = getPointFromID(point);
    auto model = pointBuilder()->buildModel([pointModel]{
        PointParameters params;
        params.id = pointModel->id();
        params.pointValue = pointModel->point();
        params.legIndex = pointModel->legIndex();
        params.setId = pointModel->parent();
        params.playerId = pointModel->player();
        return params;
    }(),[hint]{
        ModelOptions options;
        options.generateUniqueId = false;
        options.modelHint = hint;
        return options;
    }());
    int index = _points.indexOf(pointModel);
    _points.replace(index,model);
    return model->id();
}

QUuid LocalDataContext::editPointValue(const QUuid &pointId, const int &value, const int &hint)
{
    auto oldPointModel = getPointFromID(pointId);

    auto newPointModel = pointBuilder()->buildModel(
                [oldPointModel, value]
    {
        PointParameters params;
        params.id = oldPointModel->id();
        params.setId = oldPointModel->parent();
        params.pointValue = value;
        params.playerId = oldPointModel->player();
        params.legIndex = oldPointModel->legIndex();
        return params;
    }(),[hint]
    {
        ModelOptions options;
        options.generateUniqueId = false;
        options.modelHint = hint;
        return options;
    }());

    int index = _points.indexOf(oldPointModel);
    _points.replace(index,newPointModel);

    return newPointModel->id();
}

QUuid LocalDataContext::alterPointPlayer(const QUuid &pointId, const QUuid &playerId)
{
    auto model = getPointFromID(pointId);

    auto newModel = pointBuilder()->buildModel(
                [model, playerId]
    {
        PointParameters params;

        params.id = model->id();
        params.setId = model->parent();
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

    return newModel->id();
}

QUuid LocalDataContext::pointSet(const QUuid &point) const
{
    auto pointModel = getPointFromID(point);
    auto parentSetID = pointModel->parent();
    return parentSetID;
}

int LocalDataContext::pointLeg(const QUuid &point) const
{
    try {
        return getPointFromID(point)->legIndex();
    } catch (const char *msg) {
        throw msg;
    }
}

int LocalDataContext::pointValue(const QUuid &point) const
{
    auto pointModel = getPointFromID(point);
    auto pointValue = pointModel->point();
    return pointValue;
}

QUuid LocalDataContext::pointPlayer(const QUuid &point) const
{
    return getPointFromID(point)->player();
}

int LocalDataContext::pointHint(const QUuid &playerPoint) const
{
    try {
        auto pointModel = getPointFromID(playerPoint);
        auto hint = pointModel->hint();
        return hint;
    } catch (const char *msg) {
        throw msg;
    }

}

QList<QUuid> LocalDataContext::pointModels(const QUuid &player) const
{
    QList<QUuid> resultingList;
    for (auto point : _points) {
        auto pointID = point->id();
        if(point->player() == player)
            resultingList << pointID;
    }
    return resultingList;
}

QList<QUuid> LocalDataContext::playerPoints(const QUuid &tournament, const QUuid &player, const int &hint) const
{
    QList<QUuid> resultingList;
    auto totalPoints = points(tournament);
    for (auto pointID : totalPoints) {
        auto model = getPointFromID(pointID);
        auto modelHint = pointHint(pointID);
        if(modelHint != hint && hint != allHints)
            continue;
        auto pointPlayer = model->player();
        if(pointPlayer != player)
            continue;
        resultingList << pointID;
    }
    return resultingList;
}

bool LocalDataContext::removePlayerPoint(const QUuid &point)
{
    try {
        auto pointModel = getPointFromID(point);
        auto result = _points.removeOne(pointModel);
        return result;
    } catch (const char *msg) {
        return false;
    }
}

void LocalDataContext::removePlayerPointAndRelatives(const QUuid &point)
{
    try {
        auto pointModel = getPointFromID(point);
        auto parentSetID = pointModel->parent();
        auto result = _points.removeOne(pointModel);
        if(result)
        {
            removeEmptySet(parentSetID);
        }
    } catch (const char *msg) {
        return;
    }
}

DefaultDataInterface *LocalDataContext::setTournamentBuilder(ITournamentBuilder *builder)
{
    _tournamentBuilder = builder;
    return this;
}

QUuid LocalDataContext::playerPoint(const QUuid &tournament, const QUuid &player, const int &roundIndex, const int &legIndex, const int &hint)
{
    auto tournamentPoints = points(tournament);
    for (auto pointID : tournamentPoints) {
        auto pointModel = getPointFromID(pointID);
        auto modelHint = pointModel->hint();
        auto playerID = pointModel->player();
        if(playerID != player)
            continue;
        auto leg = pointLeg(pointID);
        if(leg != legIndex)
            continue;
        auto setID = pointSet(pointID);
        auto round = setRound(setID);
        auto rIndex = this->roundIndex(round);
        if(rIndex != roundIndex)
            continue;
        if(modelHint != hint && hint != allHints)
            continue;
        return pointID;
    }

    throw "Object not found";
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
        auto modelID = set->id();
        if(modelID == id)
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
    return _tournamentBuilder;
}

int LocalDataContext::playerPointsCount(const int &hint) const
{
    auto count = 0;
    for (auto pointModel : _points) {
        if(pointModel->hint() == hint || hint == allHints)
            count++;
    }
    return count;
}

bool LocalDataContext::tournamentExists(const QUuid &tournament) const
{
    for (auto model : _tournaments) {
        auto id = model->id();
        if(id == tournament)
            return true;
    }
    return false;
}

void LocalDataContext::removeTournamentModels(const QUuid &tournament)
{
    /*
     * Remove points related to tournament
     */
    auto tournamentPoints = points(tournament);
    for (int i = 0; i < tournamentPoints.count(); ++i) {
        auto tournamentPointID = tournamentPoints.at(i);
        for (int j = 0; j < _points.count(); ++j) {
            auto pointModel = _points.at(j);
            auto pointID = pointModel->id();
            if(tournamentPointID == pointID)
                _points.removeAt(j);
        }
    }
    auto tournamentSets = tournamentSetsID(tournament);
    for (int i = 0; i < tournamentSets.count(); ++i) {
        auto tournamentSetID = tournamentSets.at(i);
        for (int j = 0; j < _sets.count(); ++j){
            auto setModel = _sets.at(j);
            auto setID = setModel->id();
            if(tournamentSetID == setID)
                _sets.removeAt(j);
        }
    }
    auto tournamentRounds = roundsID(tournament);
    for (int i = 0; i < tournamentRounds.count(); ++i) {
        auto tournamentRound = tournamentRounds.at(i);
        for (int j = 0; j < _rounds.count(); ++j){
            auto roundModel = _rounds.at(j);
            auto roundID = roundModel->id();
            if(tournamentRound == roundID)
                _rounds.removeAt(j);
        }
    }
}

IRoundBuilder *LocalDataContext::roundBuilder() const
{
    return _roundBuilder;
}

ISetBuilder *LocalDataContext::setBuilder() const
{
    return _setBuilder;
}

void LocalDataContext::setSetBuilder(ISetBuilder *builder)
{
    _setBuilder = builder;
}

IPointBuilder *LocalDataContext::pointBuilder() const
{
    return _pointBuilder;
}
