#include "localtournamentmodelscontext.h"

LocalTournamentModelsContext::LocalTournamentModelsContext(const QString &org, const QString &app):
    AbstractPersistence(org,app)
{
    read();
}

LocalTournamentModelsContext::~LocalTournamentModelsContext()
{
    write();
}

void LocalTournamentModelsContext::read()
{
    auto count = settings()->beginReadArray("Tournaments");
    for (int i = 0; i < count; ++i) {
        settings()->setArrayIndex(i);
        auto id = settings()->value("ID",QUuid());
        auto title = settings()->value("Title");
        auto keyPoint = settings()->value("KeyPoint");
        auto gameMode = settings()->value("GameMode");
        auto throws = settings()->value("Throws");
        auto winner = settings()->value("Winner");

        auto tournament = tournamentBuilder()->buildModel([this,id,title,keyPoint,throws,gameMode]{
            TournamentParameters params;

            params.id = id.toUuid();
            params.title = title.toString();
            params.numberOfLegs = throws.toInt();
            params.keyPoint = keyPoint.toInt();
            params.gameMode = gameMode.toInt();
            params.tournamentsCount = this->tournamentsCount();
            return params;
        }(),[]{
            ModelOptions options;
            options.generateUniqueId = false;
            return options;
        }());

        auto pCount = settings()->beginReadArray("AssignedPlayers");
        for (int j = 0; j < pCount; ++j) {
            settings()->setArrayIndex(j);
            auto playerID = settings()->value("ID").toUuid();
            tournament->assignPlayerIdentity(playerID);
        }
        _tournaments.append(tournament);
    }
}

void LocalTournamentModelsContext::write()
{
    /*
     * Persist tournament models
     */

    auto tournamentsCount = this->tournamentsCount();
    auto tournamentsID = tournaments();
    settings()->beginWriteArray("Tournaments",tournamentsCount);
    for (int i = 0; i < tournamentsCount; ++i) {
        settings()->setArrayIndex(i);
        auto id = tournamentsID.at(i);
        auto title = tournamentTitle(id);
        auto keyPoint = tournamentKeyPoint(id);
        auto gameMode = tournamentGameMode(id);
        auto winner = tournamentDeterminedWinner(id);
        auto throws = tournamentNumberOfThrows(id);
        settings()->setValue("ID",QVariant(id));
        settings()->setValue("Title",QVariant(title));
        settings()->setValue("KeyPoint",QVariant(keyPoint));
        settings()->setValue("GameMode",QVariant(gameMode));
        settings()->setValue("Throws",QVariant(throws));
        settings()->setValue("Winner",QVariant(winner));
        auto players = tournamentAssignedPlayers(id);
        auto count = players.count();
        settings()->beginWriteArray("AssignedPlayers",count);
        for (int j = 0; j < count; ++j) {
            settings()->setArrayIndex(j);
            auto playerID = players.at(j);
            settings()->setValue("ID",QVariant(playerID));
        }
        settings()->endArray();
    }
    settings()->endArray();
}

QUuid LocalTournamentModelsContext::createTournament(const QString &title, const int &keyPoint, const int &throws, const int &gameMode)
{
    auto tournament = tournamentBuilder()->buildModel([this,title,keyPoint,throws,gameMode]{
        TournamentParameters params;

        params.title = title;
        params.numberOfLegs = throws;
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

void LocalTournamentModelsContext::deleteTournament(const QUuid &tournament)
{
    removeTournamentModel(tournament);
}

QUuid LocalTournamentModelsContext::tournamentIDFromIndex(const int &index) const
{
    try {
        auto tournament = _tournaments.at(index);
        auto id = tournament->id();
        return id;

    }  catch (...) {
        throw "MODEL_NOT_FOUND";
    }
}

QList<QUuid> LocalTournamentModelsContext::tournaments() const
{
    QList<QUuid> resultingList;

    for (auto tournament : _tournaments)
    {
        auto id = tournament->id();

        resultingList << id;
    }

    return resultingList;
}

int LocalTournamentModelsContext::tournamentsCount() const
{
    return _tournaments.count();
}

QString LocalTournamentModelsContext::tournamentTitle(const QUuid &tournament) const
{
    return getTournamentFromID(tournament)->title();
}

int LocalTournamentModelsContext::tournamentNumberOfThrows(const QUuid &tournament) const
{
    return getTournamentFromID(tournament)->numberOfThrows();
}

QList<QUuid> LocalTournamentModelsContext::tournamentAssignedPlayers(const QUuid &tournament) const
{
    QList<QUuid> assignedPlayers;
    try {
        assignedPlayers = getTournamentFromID(tournament)->assignedPlayerIdentities();
    } catch (const char *msg) {
        throw  msg;
    }
    return assignedPlayers;
}


int LocalTournamentModelsContext::tournamentGameMode(const QUuid &tournament) const
{
    return getTournamentFromID(tournament)->gameMode();
}

int LocalTournamentModelsContext::tournamentKeyPoint(const QUuid &tournament) const
{
    return getTournamentFromID(tournament)->keyPoint();
}

int LocalTournamentModelsContext::tournamentStatus(const QUuid &tournament) const
{
    return getTournamentFromID(tournament)->status();
}

QUuid LocalTournamentModelsContext::tournamentDeterminedWinner(const QUuid &tournament) const
{
    return getTournamentFromID(tournament)->winner();
}

void LocalTournamentModelsContext::alterTournamentTitle(const QUuid &tournament, const QString &title)
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

void LocalTournamentModelsContext::alterTournamentNumberOfLegs(const QUuid &tournament, const int &value)
{
    auto oldModel = getTournamentFromID(tournament);
    auto newModel = tournamentBuilder()->buildModel(
                [oldModel, value]
    {
        TournamentParameters params;

        params.id = oldModel->id();
        params.title = oldModel->title();
        params.status = oldModel->status();
        params.gameMode = oldModel->gameMode();
        params.keyPoint = oldModel->keyPoint();
        params.playerIdentities = oldModel->assignedPlayerIdentities();
        params.numberOfLegs = value;
        params.winner = oldModel->winner();

        return params;
    }(),[]
    {
        ModelOptions options;

        options.generateUniqueId = false;

        return options;
    }());
    auto index = _tournaments.indexOf(oldModel);
    _tournaments.replace(index,newModel);
}

void LocalTournamentModelsContext::tournamentAddPlayer(const QUuid &tournament, const QUuid &player)
{
    auto oldModel = getTournamentFromID(tournament);
    auto pList = oldModel->assignedPlayerIdentities();
    pList.append(player);
    auto newModel = tournamentBuilder()->buildModel(
                [oldModel, pList]
    {
        TournamentParameters params;
        params.id = oldModel->id();
        params.title = oldModel->title();
        params.status = oldModel->status();
        params.gameMode = oldModel->gameMode();
        params.keyPoint = oldModel->keyPoint();
        params.numberOfLegs = oldModel->numberOfThrows();
        params.winner = oldModel->winner();
        params.playerIdentities = pList;
        return params;
    }(),[]
    {
        ModelOptions options;
        options.generateUniqueId = false;
        return options;
    }());
    auto index = _tournaments.indexOf(oldModel);
    _tournaments.replace(index,newModel);
}

void LocalTournamentModelsContext::tournamentRemovePlayer(const QUuid &tournament, const QUuid &player)
{
    auto oldModel = getTournamentFromID(tournament);
    auto pList = oldModel->assignedPlayerIdentities();
    pList.removeOne(player);
    auto newModel = tournamentBuilder()->buildModel(
                [oldModel, pList]
    {
        TournamentParameters params;
        params.id = oldModel->id();
        params.title = oldModel->title();
        params.status = oldModel->status();
        params.gameMode = oldModel->gameMode();
        params.keyPoint = oldModel->keyPoint();
        params.playerIdentities = oldModel->assignedPlayerIdentities();
        params.numberOfLegs = oldModel->numberOfThrows();
        params.winner = oldModel->winner();
        params.playerIdentities = pList;
        return params;
    }(),[]
    {
        ModelOptions options;
        options.generateUniqueId = false;
        return options;
    }());
    auto index = _tournaments.indexOf(oldModel);
    _tournaments.replace(index,newModel);
}

void LocalTournamentModelsContext::removeTournament(const QUuid &tournament)
{
    removeTournamentModels(tournament);

    for (int i = 0; i < _tournaments.count(); ++i) {
        auto tournamentModel = _tournaments.at(i);
        auto tournamentID = tournamentModel->id();
        if(tournamentID == tournament)
            _tournaments.removeAt(i);
    }
}

void LocalTournamentModelsContext::alterTournamentGameMode(const QUuid &tournament, const int &mode)
{
    auto oldModel = getTournamentFromID(tournament);
    auto newModel = tournamentBuilder()->buildModel(
                [oldModel, mode]
    {
        TournamentParameters params;
        params.id = oldModel->id();
        params.title = oldModel->title();
        params.status = oldModel->status();
        params.gameMode = mode;
        params.keyPoint = oldModel->keyPoint();
        params.playerIdentities = oldModel->assignedPlayerIdentities();
        params.numberOfLegs = oldModel->numberOfThrows();
        params.winner = oldModel->winner();
        return params;
    }(),[]
    {
        ModelOptions options;
        options.generateUniqueId = false;
        return options;
    }());
    auto index = _tournaments.indexOf(oldModel);
    _tournaments.replace(index,newModel);
}

void LocalTournamentModelsContext::alterTournamentKeyPoint(const QUuid &tournament, const int &value)
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

void LocalTournamentModelsContext::alterTournamentDeterminedWinner(const QUuid &tournament, const QUuid &player)
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

QList<QUuid> LocalTournamentModelsContext::roundsID(const QUuid &tournament) const
{
    QList<QUuid> resultingList;
    for (auto r : _rounds) {
        if(r->parent() == tournament)
            resultingList << r->id();
    }

    return resultingList;
}

QUuid LocalTournamentModelsContext::roundID(const QUuid &tournament, const int &roundIndex) const
{
    for (auto model : _rounds)
    {
        if(model->parent() == tournament && model->index() == roundIndex)
            return model->id();
    }

    throw THROW_OBJECT_WITH_INDEX_NOT_FOUND(roundIndex);
}

QUuid LocalTournamentModelsContext::addRound(const QUuid &tournament, const int &index)
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

void LocalTournamentModelsContext::removeEmptyRound(const QUuid &round)
{
    auto roundModel = getRoundFromID(round);
    auto children = roundSetsID(round);
    auto childrenCount = children.count();
    if(childrenCount >0)
        return;
    _rounds.removeOne(roundModel);
}

void LocalTournamentModelsContext::removeEmptySet(const QUuid &set)
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

void LocalTournamentModelsContext::alterRoundIndex(const QUuid &, const int &, const int &)
{
    // This method is subject for a critical review as I fail to come up with any reason to alter round indexes
}

int LocalTournamentModelsContext::roundIndex(const QUuid &round) const
{
    try {
        return getRoundFromID(round)->index();
    } catch (const char *msg) {
        throw msg;
    }
}

QUuid LocalTournamentModelsContext::roundTournament(const QUuid &round) const
{
    auto model = getRoundFromID(round);
    auto parentID = model->parent();
    return parentID;
}

QList<QUuid> LocalTournamentModelsContext::tournamentSetsID(const QUuid &tournament) const
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

QList<QUuid> LocalTournamentModelsContext::roundSetsID(const QUuid &round) const
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

QList<QUuid> LocalTournamentModelsContext::tournamentSetsID(const QUuid &tournament, const int &roundIndex) const
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

QUuid LocalTournamentModelsContext::setID(const QUuid &tournament, const int &roundIndex, const int &setIndex) const
{
    auto sets = this->tournamentSetsID(tournament,roundIndex);
    for (auto s : sets) {
        auto index = this->setIndex(s);
        if(index == setIndex)
            return s;
    }
    throw THROW_OBJECT_WITH_INDEX_NOT_FOUND(setIndex);
}

QUuid LocalTournamentModelsContext::setRound(const QUuid &set) const
{
    try {
        auto setModel = getSetFromID(set);
        auto parentID = setModel->parent();
        return parentID;

    } catch (const char *msg) {
        throw msg;
    }
}

int LocalTournamentModelsContext::setIndex(const QUuid &set) const
{
    try {
        auto model = getSetFromID(set);
        return model->index();
    } catch (const char *msg) {
        throw msg;
    }
}

QUuid LocalTournamentModelsContext::addSet(const QUuid &tournament, const int &roundIndex, const int &setIndex)
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

QList<QUuid> LocalTournamentModelsContext::setPointsID(const QUuid &set) const
{
    QList<QUuid> resultingList;
    for (auto pointModel : _points) {
        auto pointSetID = pointModel->parent();
        if(pointSetID == set)
            resultingList << pointSetID;
    }
    return resultingList;
}

QList<QUuid> LocalTournamentModelsContext::scores(const QUuid &tournament) const
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

QList<QUuid> LocalTournamentModelsContext::scores(const QUuid &tournament, const QUuid &round) const
{
    QList<QUuid> resultingList;
    auto tPoints = this->scores(tournament);
    for (auto pointID : tPoints) {
        auto s = this->pointSet(pointID);
        auto r = this->setRound(s);
        if(r == round)
            resultingList << pointID;
    }

    return resultingList;
}

QList<QUuid> LocalTournamentModelsContext::scores(const QUuid &tournament, const QUuid &round, const QUuid &set) const
{
    QList<QUuid> resultingList;
    auto p = this->scores(tournament,round);
    for (auto pointID : p) {
        auto setID = pointSet(pointID);
        if(setID == set)
            resultingList << pointID;
    }

    return resultingList;
}

QUuid LocalTournamentModelsContext::setScoreHint(const QUuid &point, const int &hint)
{
    try {
        auto pointModel = getPointFromID(point);
        auto model = pointBuilder()->buildModel([pointModel]{
            PointParameters params;
            params.id = pointModel->id();
            params.pointValue = pointModel->point();
            params.throwIndex = pointModel->throwIndex();
            params.setId = pointModel->parent();
            params.playerId = pointModel->player();
            params.scoreValue = pointModel->score();
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

    } catch (const char msg) {
        throw msg;
    }
}

QUuid LocalTournamentModelsContext::editScore(const QUuid &pointId, const int &value, const int &score, const int &hint)
{
    auto oldPointModel = getPointFromID(pointId);

    auto newPointModel = pointBuilder()->buildModel(
                [oldPointModel, score, value]
    {
        PointParameters params;
        params.id = oldPointModel->id();
        params.setId = oldPointModel->parent();
        params.pointValue = value;
        params.playerId = oldPointModel->player();
        params.throwIndex = oldPointModel->throwIndex();
        params.scoreValue = score;
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

QUuid LocalTournamentModelsContext::alterPointPlayer(const QUuid &pointId, const QUuid &playerId)
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

QUuid LocalTournamentModelsContext::pointSet(const QUuid &point) const
{
    auto pointModel = getPointFromID(point);
    auto parentSetID = pointModel->parent();
    return parentSetID;
}

int LocalTournamentModelsContext::pointLeg(const QUuid &point) const
{
    try {
        return getPointFromID(point)->throwIndex();
    } catch (const char *msg) {
        throw msg;
    }
}

int LocalTournamentModelsContext::scorePointValue(const QUuid &point) const
{
    try {
        auto pointModel = getPointFromID(point);
        auto pointValue = pointModel->point();
        return pointValue;

    }  catch (const char *msg) {
        throw msg;
    }
}

int LocalTournamentModelsContext::scoreValue(const QUuid &point)
{
    try {
        auto pointModel = getPointFromID(point);
        auto score = pointModel->score();
        return score;

    }  catch (const char *msg) {
        throw msg;
    }
}

QUuid LocalTournamentModelsContext::pointPlayer(const QUuid &point) const
{
    return getPointFromID(point)->player();
}

int LocalTournamentModelsContext::scoreHint(const QUuid &playerPoint) const
{
    try {
        auto pointModel = getPointFromID(playerPoint);
        auto hint = pointModel->hint();
        return hint;
    } catch (const char *msg) {
        throw msg;
    }

}

QList<QUuid> LocalTournamentModelsContext::pointModels(const QUuid &player) const
{
    QList<QUuid> resultingList;
    for (auto point : _points) {
        auto pointID = point->id();
        if(point->player() == player)
            resultingList << pointID;
    }
    return resultingList;
}

QList<QUuid> LocalTournamentModelsContext::playerPoints(const QUuid &tournament, const QUuid &player, const int &hint) const
{
    QList<QUuid> resultingList;
    auto totalPoints = scores(tournament);
    for (auto pointID : totalPoints) {
        auto model = getPointFromID(pointID);
        auto modelHint = scoreHint(pointID);
        if(modelHint != hint && hint != allHints)
            continue;
        auto pointPlayer = model->player();
        if(pointPlayer != player)
            continue;
        resultingList << pointID;
    }
    return resultingList;
}

bool LocalTournamentModelsContext::removePlayerPoint(const QUuid &point)
{
    try {
        auto pointModel = getPointFromID(point);
        auto result = _points.removeOne(pointModel);
        return result;
    } catch (const char *msg) {
        return false;
    }
}

void LocalTournamentModelsContext::removePlayerPointAndRelatives(const QUuid &point)
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

QUuid LocalTournamentModelsContext::playerPoint(const QUuid &tournament, const QUuid &player, const int &roundIndex, const int &throwIndex, const int &hint)
{
    auto tournamentPoints = scores(tournament);
    for (auto pointID : tournamentPoints) {
        auto pointModel = getPointFromID(pointID);
        auto modelHint = pointModel->hint();
        auto playerID = pointModel->player();
        if(playerID != player)
            continue;
        auto leg = pointLeg(pointID);
        if(leg != throwIndex)
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

const DefaultTournamentInterface *LocalTournamentModelsContext::getTournamentFromID(const QUuid &id) const
{
    for (auto tournament : _tournaments) {
        if(tournament->id() == id)
            return tournament;
    }

    throw THROW_OBJECT_WITH_ID_NOT_FOUND(id.toString());
}

const DefaultRoundInterface *LocalTournamentModelsContext::getRoundFromID(const QUuid &id) const
{
    for (auto round : _rounds) {
        if(round->id() == id)
            return round;
    }

    throw THROW_OBJECT_WITH_ID_NOT_FOUND(id.toString());
}

const DefaultSetInterface *LocalTournamentModelsContext::getSetFromID(const QUuid &id) const
{
    for (auto set : _sets)
    {
        auto modelID = set->id();
        if(modelID == id)
            return set;
    }

    throw THROW_OBJECT_WITH_ID_NOT_FOUND(id.toString());
}

const DefaultPointInterface *LocalTournamentModelsContext::getPointFromID(const QUuid &id) const
{
    for (auto point : _points)
    {
        if(point->id() == id)
            return point;
    }

    throw THROW_OBJECT_WITH_ID_NOT_FOUND(id.toString());
}

void LocalTournamentModelsContext::removeTournamentModel(const QUuid &tournament)
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

void LocalTournamentModelsContext::removePointModel(const QUuid &point)
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

int LocalTournamentModelsContext::playerPointsCount(const int &hint) const
{
    auto count = 0;
    for (auto pointModel : _points) {
        if(pointModel->hint() == hint || hint == allHints)
            count++;
    }
    return count;
}

int LocalTournamentModelsContext::addScore(const QUuid &tournament,
                                          const QUuid &player,
                                          const int &point,
                                          const int &roundIndex,
                                          const int &setIndex,
                                          const int &throwIndex,
                                          const int &score)
{
    auto setID = this->setID(tournament,roundIndex,setIndex);
    auto model = pointBuilder()->buildModel(
                [setID,throwIndex,point,player,score]
    {
        PointParameters params;
        auto setId = setID;
        params.setId = setId;
        params.playerId = player;
        params.pointValue = point;
        params.throwIndex = throwIndex;
        params.scoreValue = score;

        return params;
    }(),[]{
        ModelOptions options;
        options.modelHint = ModelDisplayHint::DisplayHint;
        return options;
    }());

    _points.append(model);

    return score;
}


bool LocalTournamentModelsContext::tournamentExists(const QUuid &tournament) const
{
    for (auto model : _tournaments) {
        auto id = model->id();
        if(id == tournament)
            return true;
    }
    return false;
}

void LocalTournamentModelsContext::removeTournamentModels(const QUuid &tournament)
{
    /*
     * Remove points related to tournament
     */
    auto tournamentPoints = scores(tournament);
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

IRoundBuilder *LocalTournamentModelsContext::roundBuilder() const
{
    return _roundBuilder;
}

ISetBuilder *LocalTournamentModelsContext::setBuilder() const
{
    return _setBuilder;
}

void LocalTournamentModelsContext::setSetBuilder(ISetBuilder *builder)
{
    _setBuilder = builder;
}

IPointBuilder *LocalTournamentModelsContext::pointBuilder() const
{
    return _pointBuilder;
}

int LocalTournamentModelsContext::score(const QUuid &tournament, const QUuid &player) const
{
    int totalScore = tournamentKeyPoint(tournament);
    auto playerScore = playerPoints(tournament,player, ModelDisplayHint::DisplayHint);
    for (auto scoreID : playerScore) {
        auto point = scorePointValue(scoreID);
        totalScore -= point;
    }
    return totalScore;
}

int LocalTournamentModelsContext::score(const QUuid &player) const
{

}

