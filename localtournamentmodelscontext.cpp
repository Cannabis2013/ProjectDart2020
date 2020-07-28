#include "localtournamentmodelscontext.h"

LocalTournamentModelsContext::LocalTournamentModelsContext(const QString &org, const QString &app)
{
}

LocalTournamentModelsContext::~LocalTournamentModelsContext()
{
}

QUuid LocalTournamentModelsContext::createtournament(const QString &title,
                                                     const int &keyPoint,
                                                     const int &throws,
                                                     const int &gameMode)
{
    auto tournament = tournamentBuilder()->buildModel([this,title,keyPoint,throws,gameMode]{
        TournamentParameters params;
        params.title = title;
        params.throws = throws;
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
    /*
     * TODO: Remove all models related to the tournament
     */
    removeTournamentScores(tournament);
    removeTournamentSets(tournament);
    removeTournamentRounds(tournament);
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
    return getTournamentModelFromID(tournament)->title();
}

int LocalTournamentModelsContext::tournamentNumberOfThrows(const QUuid &tournament) const
{
    return getTournamentModelFromID(tournament)->numberOfThrows();
}

QList<QUuid> LocalTournamentModelsContext::tournamentAssignedPlayers(const QUuid &tournament) const
{
    QList<QUuid> assignedPlayers;
    try {
        assignedPlayers = getTournamentModelFromID(tournament)->assignedPlayerIdentities();
    } catch (const char *msg) {
        throw  msg;
    }
    return assignedPlayers;
}


int LocalTournamentModelsContext::tournamentGameMode(const QUuid &tournament) const
{
    return getTournamentModelFromID(tournament)->gameMode();
}

int LocalTournamentModelsContext::tournamentKeyPoint(const QUuid &tournament) const
{
    auto tournamentModel = getTournamentModelFromID(tournament);
    auto keyPoint = tournamentModel->keyPoint();
    return keyPoint;
}

int LocalTournamentModelsContext::tournamentStatus(const QUuid &tournament) const
{
    return getTournamentModelFromID(tournament)->status();
}

QUuid LocalTournamentModelsContext::tournamentDeterminedWinner(const QUuid &tournament) const
{
    return getTournamentModelFromID(tournament)->winner();
}

void LocalTournamentModelsContext::alterTournamentTitle(const QUuid &tournament, const QString &title)
{
    auto model = getTournamentModelFromID(tournament);

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
        params.throws = model->numberOfThrows();
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
    auto oldModel = getTournamentModelFromID(tournament);
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
        params.throws = value;
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

void LocalTournamentModelsContext::assignPlayerToTournament(const QUuid &tournament, const QUuid &player)
{
    auto oldModel = getTournamentModelFromID(tournament);
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
        params.throws = oldModel->numberOfThrows();
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
    auto oldModel = getTournamentModelFromID(tournament);
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
        params.throws = oldModel->numberOfThrows();
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
    auto oldModel = getTournamentModelFromID(tournament);
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
        params.throws = oldModel->numberOfThrows();
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
    auto model = getTournamentModelFromID(tournament);

    auto newModel = tournamentBuilder()->buildModel(
                [model, value]
    {
        TournamentParameters params;

        params.id = model->id();
        params.title = model->title();
        params.status = model->status();
        params.gameMode = model->gameMode();
        params.keyPoint = value;
        params.throws = model->numberOfThrows();
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
    auto model = getTournamentModelFromID(tournament);

    auto newModel = tournamentBuilder()->buildModel(
                [model, player]
    {
        TournamentParameters params;

        params.id = model->id();
        params.title = model->title();
        params.status = model->status();
        params.gameMode = model->gameMode();
        params.keyPoint = model->keyPoint();
        params.throws = model->numberOfThrows();
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

QList<QUuid> LocalTournamentModelsContext::roundsID() const
{
    QList<QUuid> resultingList;
    for (auto r : _rounds)
        resultingList << r->id();

    return resultingList;
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
    auto roundModel = getRoundModelFromID(round);
    auto children = roundSetsID(round);
    auto childrenCount = children.count();
    if(childrenCount >0)
        return;
    _rounds.removeOne(roundModel);
}

void LocalTournamentModelsContext::removeEmptySet(const QUuid &set)
{
    auto setModel = getSetModelFromID(set);
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
        return getRoundModelFromID(round)->index();
    } catch (const char *msg) {
        throw msg;
    }
}

QUuid LocalTournamentModelsContext::roundTournament(const QUuid &round) const
{
    auto model = getRoundModelFromID(round);
    auto parentID = model->parent();
    return parentID;
}

QList<QUuid> LocalTournamentModelsContext::tournamentSetsID(const QUuid &tournament) const
{
    QList<QUuid> resultingList;
    for (auto model : _sets) {
        auto setID = model->id();
        auto roundModel = getRoundModelFromID(model->parent());
        auto tournamentModel = getTournamentModelFromID(roundModel->parent());
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
        auto roundModel = getRoundModelFromID(model->parent());
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
        auto round = getRoundModelFromID(model->parent());
        auto modelRoundIndex = round->index();;
        auto t = getTournamentModelFromID(round->parent());
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

QList<QUuid> LocalTournamentModelsContext::setsID() const
{
    QList<QUuid> resultingList;
    for (auto set : _sets) {
        auto id = set->id();
        resultingList << id;
    }
    return resultingList;
}

QUuid LocalTournamentModelsContext::setRound(const QUuid &set) const
{
    try {
        auto setModel = getSetModelFromID(set);
        auto parentID = setModel->parent();
        return parentID;

    } catch (const char *msg) {
        throw msg;
    }
}

int LocalTournamentModelsContext::setIndex(const QUuid &set) const
{
    try {
        auto model = getSetModelFromID(set);
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
    for (auto pointModel : _scores) {
        auto pointSetID = pointModel->parent();
        if(pointSetID == set)
            resultingList << pointSetID;
    }
    return resultingList;
}

QList<QUuid> LocalTournamentModelsContext::scores() const
{
    QList<QUuid> resultingList;
    for (auto scoreModel : _scores) {
        auto scoreID = scoreModel->id();
        resultingList << scoreID;
    }
    return resultingList;
}

QList<QUuid> LocalTournamentModelsContext::scores(const QUuid &tournament) const
{
    QList<QUuid> resultingList;
    for (auto pointModel : _scores) {
        auto parentSetID = pointModel->parent();
        auto setModel = getSetModelFromID(parentSetID);
        auto parentRoundID = setModel->parent();
        auto roundModel = getRoundModelFromID(parentRoundID);
        auto parentTournamentID = roundModel->parent();
        auto tournamentModel = getTournamentModelFromID(parentTournamentID);
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
        auto s = this->scoreSet(pointID);
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
        auto setID = scoreSet(pointID);
        if(setID == set)
            resultingList << pointID;
    }

    return resultingList;
}

QUuid LocalTournamentModelsContext::setScoreHint(const QUuid &point, const int &hint)
{
    try {
        auto pointModel = getScoreModelFromID(point);
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
        int index = _scores.indexOf(pointModel);
        _scores.replace(index,model);
        return model->id();

    } catch (const char msg) {
        throw msg;
    }
}

QUuid LocalTournamentModelsContext::editScore(const QUuid &pointId, const int &value, const int &score, const int &hint)
{
    auto oldPointModel = getScoreModelFromID(pointId);

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

    int index = _scores.indexOf(oldPointModel);
    _scores.replace(index,newPointModel);

    return newPointModel->id();
}

QUuid LocalTournamentModelsContext::alterPointPlayer(const QUuid &pointId, const QUuid &playerId)
{
    auto model = getScoreModelFromID(pointId);

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

    _scores.append(newModel);

    return newModel->id();
}

QUuid LocalTournamentModelsContext::scoreSet(const QUuid &point) const
{
    auto pointModel = getScoreModelFromID(point);
    auto parentSetID = pointModel->parent();
    return parentSetID;
}

int LocalTournamentModelsContext::scoreThrowIndex(const QUuid &point) const
{
    try {
        auto scoreModel = getScoreModelFromID(point);
        auto throwIndex = scoreModel->throwIndex();
        return throwIndex;
    } catch (const char *msg) {
        throw msg;
    }
}

int LocalTournamentModelsContext::scorePointValue(const QUuid &point) const
{
    try {
        auto pointModel = getScoreModelFromID(point);
        auto pointValue = pointModel->point();
        return pointValue;

    }  catch (const char *msg) {
        throw msg;
    }
}

int LocalTournamentModelsContext::scoreValue(const QUuid &point)
{
    try {
        auto pointModel = getScoreModelFromID(point);
        auto score = pointModel->score();
        return score;

    }  catch (const char *msg) {
        throw msg;
    }
}

QUuid LocalTournamentModelsContext::scorePlayer(const QUuid &point) const
{
    return getScoreModelFromID(point)->player();
}

int LocalTournamentModelsContext::scoreHint(const QUuid &playerPoint) const
{
    try {
        auto pointModel = getScoreModelFromID(playerPoint);
        auto hint = pointModel->hint();
        return hint;
    } catch (const char *msg) {
        throw msg;
    }

}

QList<QUuid> LocalTournamentModelsContext::pointModels(const QUuid &player) const
{
    QList<QUuid> resultingList;
    for (auto point : _scores) {
        auto pointID = point->id();
        if(point->player() == player)
            resultingList << pointID;
    }
    return resultingList;
}

void LocalTournamentModelsContext::removeTournamentRounds(const QUuid &tournament)
{
    for (int i = 0; i < _rounds.count(); ++i) {
        auto model = _rounds.at(i);
        if(model->parent() == tournament)
            _rounds.removeAt(i--);
    }
}

void LocalTournamentModelsContext::removeTournamentSets(const QUuid &tournament)
{
    for (int i = 0; i < _sets.count(); ++i) {
        auto setModel = _sets.at(i);
        auto roundID = setModel->parent();
        auto roundModel = getRoundModelFromID(roundID);
        auto tournamentID = roundModel->parent();
        if(tournamentID == tournament)
            _sets.removeAt(i--);
    }
}

void LocalTournamentModelsContext::removeTournamentScores(const QUuid &tournament)
{
    for (int i = 0; i < _scores.count(); ++i) {
        auto scoreModel = _scores.at(i);
        auto setID = scoreModel->parent();
        auto setModel = getSetModelFromID(setID);
        auto roundID = setModel->parent();
        auto roundModel = getRoundModelFromID(roundID);
        auto tournamentID = roundModel->parent();
        if(tournamentID == tournament)
            _scores.removeAt(i--);
    }
}

QList<QUuid> LocalTournamentModelsContext::playerPoints(const QUuid &tournament, const QUuid &player, const int &hint) const
{
    QList<QUuid> resultingList;
    auto totalPoints = scores(tournament);
    for (auto pointID : totalPoints) {
        auto model = getScoreModelFromID(pointID);
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
        auto pointModel = getScoreModelFromID(point);
        auto result = _scores.removeOne(pointModel);
        return result;
    } catch (const char *msg) {
        return false;
    }
}

void LocalTournamentModelsContext::removePlayerPointAndRelatives(const QUuid &point)
{
    try {
        auto pointModel = getScoreModelFromID(point);
        auto parentSetID = pointModel->parent();
        auto result = _scores.removeOne(pointModel);
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
        auto pointModel = getScoreModelFromID(pointID);
        auto modelHint = pointModel->hint();
        auto playerID = pointModel->player();
        if(playerID != player)
            continue;
        auto leg = scoreThrowIndex(pointID);
        if(leg != throwIndex)
            continue;
        auto setID = scoreSet(pointID);
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

const DefaultTournamentInterface *LocalTournamentModelsContext::getTournamentModelFromID(const QUuid &id) const
{
    for (auto tournament : _tournaments) {
        if(tournament->id() == id)
            return tournament;
    }

    throw THROW_OBJECT_WITH_ID_NOT_FOUND(id.toString());
}

const DefaultRoundInterface *LocalTournamentModelsContext::getRoundModelFromID(const QUuid &id) const
{
    for (auto round : _rounds) {
        if(round->id() == id)
            return round;
    }

    throw THROW_OBJECT_WITH_ID_NOT_FOUND(id.toString());
}

const DefaultSetInterface *LocalTournamentModelsContext::getSetModelFromID(const QUuid &id) const
{
    for (auto set : _sets)
    {
        auto modelID = set->id();
        if(modelID == id)
            return set;
    }

    throw THROW_OBJECT_WITH_ID_NOT_FOUND(id.toString());
}

const DefaultPointInterface *LocalTournamentModelsContext::getScoreModelFromID(const QUuid &id) const
{
    for (auto point : _scores)
    {
        if(point->id() == id)
            return point;
    }

    throw THROW_OBJECT_WITH_ID_NOT_FOUND(id.toString());
}

void LocalTournamentModelsContext::clearInconsistentModels()
{
    removeInconsistentScores();
    removeInconsistentSets();
    removeInconsistentRounds();
}

void LocalTournamentModelsContext::removeInconsistentScores()
{
    QVector<const IScore<QUuid>*> inconsistentModels;
    for (int i = 0; i < _scores.count(); ++i) {
        auto scoreModel = _scores.at(i);
        try {
            auto setID = scoreModel->parent();
            auto setModel = getSetModelFromID(setID);
            auto roundID = setModel->parent();
            auto roundModel = getRoundModelFromID(roundID);
            auto tournamentID = roundModel->parent();
            getTournamentModelFromID(tournamentID);
        }  catch (...) {
            _scores.removeAt(i--);
        }
    }
}

void LocalTournamentModelsContext::removeInconsistentSets()
{
    QVector<const ISet<QUuid,QList<QUuid>>*> inconsistentModels;
    for (int i = 0; i < _sets.count(); ++i) {
        auto setModel = _sets.at(i);
        try {
            auto roundID = setModel->parent();
            auto roundModel = getRoundModelFromID(roundID);
            auto tournamentID = roundModel->parent();
            getTournamentModelFromID(tournamentID);
        }  catch (...) {
            _sets.removeAt(i--);
        }
    }
}

void LocalTournamentModelsContext::removeInconsistentRounds()
{
    QVector<int> inconsistentModelIndexes;
    for (int i = 0; i < _rounds.count(); ++i) {
        auto roundModel = _rounds.at(i);
        try {
            auto tournamentID = roundModel->parent();
            getTournamentModelFromID(tournamentID);
        }  catch (...) {
            _rounds.removeAt(i--);
        }
    }
}

void LocalTournamentModelsContext::buildTournament(const QUuid &id,
                                                 const QString &title,
                                                 const int &keyPoint,
                                                 const int &throws,
                                                 const int &gameMode,
                                                 const QUuid &winner)
{
    auto tournament = tournamentBuilder()->buildModel([id,title,keyPoint,throws,gameMode,winner]{
        TournamentParameters params;
        params.id = id;
        params.title = title;
        params.keyPoint = keyPoint;
        params.gameMode = gameMode;
        params.throws = throws;
        params.winner = winner;
        return params;
    }(),[]{
        ModelOptions options;
        options.generateUniqueId = false;
        return options;
    }());
    _tournaments.append(tournament);
}

void LocalTournamentModelsContext::buildRound(const QUuid &tournament, const int &index, const QUuid &id)
{
    auto round = roundBuilder()->buildModel(
                [id,tournament,index]
    {
        RoundParameters params;
        params.id = id;
        params.tournamentId = tournament;
        params.roundIndex = index;
        return params;
    }(),[]
    {
        ModelOptions options;
        options.generateUniqueId = false;
        return options;
    }());
    _rounds.append(round);
}

void LocalTournamentModelsContext::buildSet(const QUuid &id, const QUuid &round, const int &setIndex)
{
    auto model = setBuilder()->buildModel(
                [id,round,setIndex]{
        SetParameters params;
        params.id = id;
        params.roundId = round;
        params.index = setIndex;
        return params;
    }(),[]
    {
        ModelOptions options;
        options.generateUniqueId = false;
        return options;
    }());

    _sets << model;
}

void LocalTournamentModelsContext::buildScoreModel(const QUuid &id,
                                                   const QUuid &player,
                                                   const QUuid &set,
                                                   const int &point,
                                                   const int &throwIndex,
                                                   const int &score)
{
    auto model = pointBuilder()->buildModel(
                [id,set,throwIndex,point,player,score]
    {
        PointParameters params;
        params.id = id;
        params.setId = set;
        params.playerId = player;
        params.pointValue = point;
        params.throwIndex = throwIndex;
        params.scoreValue = score;

        return params;
    }(),[]{
        ModelOptions options;
        options.modelHint = ModelDisplayHint::DisplayHint;
        options.generateUniqueId = false;
        return options;
    }());

    _scores.append(model);
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
    for (int i = 0; i < _scores.count(); ++i) {
        auto model = _scores.at(i);
        auto id = model->id();
        if(id == point)
        {
            _scores.removeAt(i);
            return;
        }
    }
}

int LocalTournamentModelsContext::playerPointsCount(const int &hint) const
{
    auto count = 0;
    for (auto pointModel : _scores) {
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
        options.generateUniqueId = true;
        options.modelHint = ModelDisplayHint::DisplayHint;
        return options;
    }());

    _scores.append(model);

    return score;
}


void LocalTournamentModelsContext::removeTournamentModels(const QUuid &tournament)
{
    /*
     * Remove points related to tournament
     */
    auto tournamentPoints = scores(tournament);
    for (int i = 0; i < tournamentPoints.count(); ++i) {
        auto tournamentPointID = tournamentPoints.at(i);
        for (int j = 0; j < _scores.count(); ++j) {
            auto pointModel = _scores.at(j);
            auto pointID = pointModel->id();
            if(tournamentPointID == pointID)
                _scores.removeAt(j);
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
    Q_UNIMPLEMENTED();
}

