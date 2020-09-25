#include "localtournamentmodelscontext.h"

void LocalTournamentModelsContext::read()
{
    QJsonObject JSONObject;
    try {
        JSONObject = readJSONFromFile("TournamentModels");
    } catch (...) {
        return;
    }
    auto tournamentsJSONArray = JSONObject["TournamentsData"].toArray();
    auto roundsJSONArray = JSONObject["RoundsData"].toArray();
    auto setsJSONArray = JSONObject["SetsData"].toArray();
    auto scoresJSONArray = JSONObject["ScoresData"].toArray();

    extractTournamentModelsFromJSON(tournamentsJSONArray);
    extractRoundModelsFromJSON(roundsJSONArray);
    extractSetModelsFromJSON(setsJSONArray);
    extractScoreModelsFromJSON(scoresJSONArray);

    // Do inconsistency check

    removeInconsistentModels();
}

void LocalTournamentModelsContext::write()
{
    /*
     * Persist tournament models
     */
    QJsonObject modelJSON;
    modelJSON["TournamentsData"] = assembleTournamentsJSONArray();
    modelJSON["RoundsData"] = assembleRoundsJSONArray();
    modelJSON["SetsData"] = assembeSetsJSONArray();
    modelJSON["ScoresData"] = assembleScoresJSONArray();
    writeJSONToFile(modelJSON,"TournamentModels");
}

LocalTournamentModelsContext::~LocalTournamentModelsContext()
{
    write();
}

AbstractTournamentModelsContext *LocalTournamentModelsContext::createInstance()
{
    return new LocalTournamentModelsContext();
}

AbstractTournamentModelsContext *LocalTournamentModelsContext::setup()
{
    read();
    return this;
}

ITournamentBuilder *LocalTournamentModelsContext::tournamentModelBuilder()
{
    return _tournamentBuilder;
}

AbstractTournamentModelsContext *LocalTournamentModelsContext::setTournamentModelBuilder(ITournamentBuilder *builder)
{
    _tournamentBuilder = builder;
    return this;
}

IRoundBuilder *LocalTournamentModelsContext::roundModelBuilder(){
    return _roundBuilder;
}

AbstractTournamentModelsContext *LocalTournamentModelsContext::setRoundModelBuilder(IRoundBuilder *builder)
{
    _roundBuilder = builder;
    return this;
}

ISetBuilder *LocalTournamentModelsContext::setSetModelBuilder() const
{
    return _setBuilder;
}

AbstractTournamentModelsContext *LocalTournamentModelsContext::setSetModelBuilder(ISetBuilder *builder)
{
    _setBuilder = builder;
    return this;
}

IScoreModelBuilder *LocalTournamentModelsContext::scoreModelBuilder()
{
    return _pointBuilder;
}

AbstractTournamentModelsContext *LocalTournamentModelsContext::setScoreModelBuilder(IScoreModelBuilder *builder)
{
    _pointBuilder = builder;
    return this;
}

void LocalTournamentModelsContext::handleRequestUpdateContext(const QUuid &tournamentID,
                                                              const int &roundIndex,
                                                              const int &setIndex)
{
    updateDataContext(tournamentID,roundIndex,setIndex);
    emit datacontextUpdated();
}

void LocalTournamentModelsContext::handleRequestSetScoreHint(const QUuid &tournament,
                                                             const QUuid &player,
                                                             const int &roundIndex,
                                                             const int &throwIndex,
                                                             const int &hint)
{
    QUuid scoreID;
    try {
        scoreID = playerScore(tournament,
                              player,
                              roundIndex,
                              throwIndex,
                              ModelDisplayHint::allHints);

    }  catch (const char *msg) {
        emit scoreHintNotUpdated(tournament,msg);
        return;
    }
    auto point = scorePointValue(scoreID);
    auto score = scoreValue(scoreID);
    setScoreHint(scoreID,hint);
    emit scoreHintUpdated(player,point,score);
}

void LocalTournamentModelsContext::handleResetTournament(const QUuid &tournament)
{
    removeModelsRelatedToTournament(tournament);
    setTournamentDeterminedWinner(tournament,QUuid());
    emit tournamentResetSuccess();
}

void LocalTournamentModelsContext::assembleAndAddTournament(const QString &title,
                                                            const int &gameMode,
                                                            const int &numberOfThrows,
                                                            const int &winCondition,
                                                            const int &keyPoint,
                                                          const QList<QUuid> &assignedPlayersID)
{
    auto tournamentID = createTournament(title,keyPoint,numberOfThrows,gameMode,winCondition);
    for (auto assignedPlayerID : assignedPlayersID)
        assignPlayerToTournament(tournamentID,assignedPlayerID);
    emit transmitResponse(ModelsContextResponse::TournamentCreatedOK,{});
}

void LocalTournamentModelsContext::handleAssignPlayersToTournament(const QUuid &tournament, const QList<QUuid> &playersID)
{
    for (auto playerID : playersID)
        assignPlayerToTournament(tournament,playerID);

}

void LocalTournamentModelsContext::deleteTournaments(const QVector<int> &indexes)
{
    auto status = true;
    QList<QUuid> tournamentsID;
    for (auto index : indexes) {
        try {
            auto tournamentID = tournamentIDFromIndex(index);
            tournamentsID << tournamentID;
        }  catch (...) {
            status = false;
        }
    }
    for (auto tournamentID : tournamentsID) {
        removeTournament(tournamentID);
    }
    emit tournamentsDeletedSuccess(status);
}

void LocalTournamentModelsContext::handleTransmitPlayerScores(const QUuid &tournament,
                                                              const QList<QPair<QUuid,QString>>&playerPairs)
{
    QVariantList list;
    auto numberOfThrows = tournamentNumberOfThrows(tournament);
    for (auto player : playerPairs) {
        auto roundIndex = 1;
        auto throwIndex = 0;
        auto assignedPlayerID = player.first;
        auto playerName = player.second;
        while (1)
        {
            QUuid scoreID;
            try {
                scoreID = playerScore(tournament,
                                      assignedPlayerID,
                                      roundIndex,
                                      throwIndex++,
                                      DisplayHint);
            }  catch (...) {
                break;
            }
            int score;
            int point;
            int keyCode;
            try {
                point = scorePointValue(scoreID);
                score = scoreValue(scoreID);
                keyCode = scoreKeyCode(scoreID);
            } catch (const char *msg) {
                throw msg;
            }
            QVariantList subList = {playerName,point,score,keyCode};
            list.append(subList);
            if(throwIndex % numberOfThrows == 0)
            {
                throwIndex = 0;
                roundIndex++;
            }
        }
    }
    emit transmitResponse(ModelsContextResponse::EndOfTransmission,{list});
}

void LocalTournamentModelsContext::handleTransmitTournaments()
{
    auto count = tournamentsCount();
    for (int i = 0; i < count; ++i) {
        auto id = tournamentIDFromIndex(i);
        auto title = tournamentTitle(id);
        auto numberOfThrows = tournamentNumberOfThrows(id);
        auto gameMode = tournamentGameMode(id);
        auto keyPoint = tournamentKeyPoint(id);
        auto playersCount = tournamentAssignedPlayers(id).count();
        emit sendTournament(title,numberOfThrows,gameMode,keyPoint,playersCount);
    }
    emit lastTournamentTransmitted();
}

void LocalTournamentModelsContext::handleRequestForTournamentMetaData(const QUuid &tournament)
{
    auto title = tournamentTitle(tournament);
    auto gameMode = tournamentGameMode(tournament);
    auto keyPoint = tournamentKeyPoint(tournament);
    auto playersID = tournamentAssignedPlayers(tournament);
    auto winnerID = tournamentDeterminedWinner(tournament);
    emit sendTournamentMeta(title,gameMode,keyPoint,winnerID,playersID);
}

void LocalTournamentModelsContext::handleRequestTournamentDetails(const int &index)
{
    try {
        auto tournamentID = tournamentIDFromIndex(index);
        auto keyPoint = tournamentKeyPoint(tournamentID);
        auto lastThrowKeyCode = tournamentLastThrowKeyCode(tournamentID);
        auto numberOfThrows = tournamentNumberOfThrows(tournamentID);
        auto gameMode = tournamentGameMode(tournamentID);
        auto assignedPlayersID = tournamentAssignedPlayers(tournamentID);
        auto winnerID = tournamentDeterminedWinner(tournamentID);
        emit sendTournamentDetails(tournamentID,
                                   winnerID,
                                   keyPoint,
                                   lastThrowKeyCode,
                                   numberOfThrows,
                                   gameMode,
                                   assignedPlayersID);
    }  catch (const char *msg) {
        return;
    }
}

void LocalTournamentModelsContext::handleRequestTournamentIndexes(const QUuid &tournament)
{
    auto roundIndex = 1;
    auto setIndex = 0;
    auto throwIndex = 0;
    auto turnIndex = 0;
    auto assignedPlayersID = tournamentAssignedPlayers(tournament);
    auto playersCount = assignedPlayersID.count();
    auto numberOfThrows= tournamentNumberOfThrows(tournament);
    auto totalTurns = 0;
    while(1)
    {
        auto playerId = assignedPlayersID.at(setIndex);
        try {
            playerScore(tournament,playerId,roundIndex,throwIndex,ModelDisplayHint::DisplayHint);
        } catch (...) {
            break;
        }
        if(++throwIndex % numberOfThrows == 0)
        {
            throwIndex = 0;
            setIndex++;
            if(setIndex >= playersCount)
            {
                roundIndex++;
                setIndex = 0;
            }
        }
        turnIndex++;
    }
    if(turnIndex != 0)
        totalTurns = playerScoreCount(ModelDisplayHint::allHints);
    else
        updateDataContext(tournament,1,0);

    QList<int> userScores;
    for (auto playerID : assignedPlayersID) {
        auto s = score(tournament,playerID);
        userScores << s;
    }
    emit sendTournamentIndexes(roundIndex,setIndex,throwIndex,turnIndex,totalTurns,userScores);
}

void LocalTournamentModelsContext::handleRequestAssignedPlayers(const QUuid &tournament)
{
    auto assignedPlayersID = tournamentAssignedPlayers(tournament);
    emit sendAssignedPlayers(assignedPlayersID);
}

void LocalTournamentModelsContext::updateDataContext(const QUuid &tournament,
                                                     const int &roundIndex,
                                                     const int &setIndex)
{
    QUuid round;
    try {
        round = roundID(tournament,roundIndex);
    } catch (...) {
        addRound(tournament,roundIndex);
    }
    QUuid set;
    try {
        set = setID(tournament,roundIndex,setIndex);
    } catch (...) {
        addSet(tournament,roundIndex,setIndex);
    }
}

QUuid LocalTournamentModelsContext::createTournament(const QString &title,
                                                     const int &keyPoint,
                                                     const int &throws,
                                                     const int &gameMode,
                                                     const int &winCondition)
{
    auto tournament = tournamentModelBuilder()->buildModel([this,title,keyPoint,throws,gameMode,winCondition]{
        TournamentParameters params;
        params.title = title;
        params.throws = throws;
        params.keyPoint = keyPoint;
        params.gameMode = gameMode;
        params.winConditionKey = winCondition;
        params.tournamentsCount = this->tournamentsCount();
        return params;
    }(),[]{
        ModelOptions options;
        options.generateUniqueId = true;
        return options;
    }());
    _dbContext->addModel("Tournament",tournament);
    return tournament->id();
}


void LocalTournamentModelsContext::removeTournament(const QUuid &tournament)
{
    /*
     * TODO: Remove all models related to the tournament
     */
    removeModelsRelatedToTournament(tournament);
    removeTournamentModel(tournament);
}

void LocalTournamentModelsContext::removeModelsRelatedToTournament(const QUuid &tournament)
{
    /*
     * Remove models in the following order:
     *  1. Remove ScoreModel's
     *  2. Remove SetModel's
     *  3. Remove RoundModel's
     */
    removeTournamentScores(tournament);
    removeTournamentSets(tournament);
    removeTournamentRounds(tournament);
}

QUuid LocalTournamentModelsContext::tournamentIDFromIndex(const int &index)
{
    try {
        auto tournament = dynamic_cast<const DefaultTournamentInterface*>(modelDBContext()->model("Tournament",index));
        auto id = tournament->id();
        return id;

    }  catch (...) {
        throw "TOURNAMENT_NOT_FOUND";
    }
}

QList<QUuid> LocalTournamentModelsContext::tournaments()
{
    QList<QUuid> resultingList;
    auto tournaments = modelDBContext()->models("Tournament");
    for (auto tournament : tournaments)
    {
        auto id = tournament->id();
        resultingList << id;
    }

    return resultingList;
}

int LocalTournamentModelsContext::tournamentsCount()
{
    auto count = modelDBContext()->countOfModels("Tournament");
    return count;
}

QString LocalTournamentModelsContext::tournamentTitle(const QUuid &tournament)
{
    return getTournamentModelFromID(tournament)->title();
}

int LocalTournamentModelsContext::tournamentNumberOfThrows(const QUuid &tournament)
{
    return getTournamentModelFromID(tournament)->numberOfThrows();
}

QList<QUuid> LocalTournamentModelsContext::tournamentAssignedPlayers(const QUuid &tournament)
{
    QList<QUuid> assignedPlayers;
    try {
        assignedPlayers = getTournamentModelFromID(tournament)->assignedPlayerIdentities();
    } catch (const char *msg) {
        throw  msg;
    }
    return assignedPlayers;
}


int LocalTournamentModelsContext::tournamentGameMode(const QUuid &tournament)
{
    return getTournamentModelFromID(tournament)->gameMode();
}

int LocalTournamentModelsContext::tournamentLastThrowKeyCode(const QUuid &tournament)
{
    auto tournamentModel = getTournamentModelFromID(tournament);
    auto conditionKeyCode = tournamentModel->terminateKeyCondition();
    return conditionKeyCode;
}

int LocalTournamentModelsContext::tournamentKeyPoint(const QUuid &tournament)
{
    auto tournamentModel = getTournamentModelFromID(tournament);
    auto keyPoint = tournamentModel->keyPoint();
    return keyPoint;
}

int LocalTournamentModelsContext::tournamentStatus(const QUuid &tournament)
{
    return getTournamentModelFromID(tournament)->status();
}

QUuid LocalTournamentModelsContext::tournamentDeterminedWinner(const QUuid &tournament)
{
    auto tournamentModel = getTournamentModelFromID(tournament);
    return tournamentModel->winner();
}

void LocalTournamentModelsContext::setTournamentDeterminedWinner(const QUuid &tournament,
                                                                 const QUuid &winner)
{
    auto oldModel = getTournamentModelFromID(tournament);
    auto newModel = tournamentModelBuilder()->buildModel(
                    [oldModel, winner]
                    {
                        TournamentParameters params;
                        params.id = oldModel->id();
                        params.title = oldModel->title();
                        params.status = oldModel->status();
                        params.gameMode = oldModel->gameMode();
                        params.keyPoint = oldModel->keyPoint();
                        params.throws = oldModel->numberOfThrows();
                        params.winner = winner;
                        params.playerIdentities = oldModel->assignedPlayerIdentities();
                        return params;
                    }(),[]
                    {
                        ModelOptions options;
                        options.generateUniqueId = false;
                        return options;
                    }());
    auto index = modelDBContext()->indexOfModel("Tournament",oldModel);
    modelDBContext()->replaceModel("Tournament",index,newModel);
}

void LocalTournamentModelsContext::assignPlayerToTournament(const QUuid &tournament, const QUuid &player)
{
    auto oldModel = getTournamentModelFromID(tournament);
    auto pList = oldModel->assignedPlayerIdentities();
    pList.append(player);
    auto newModel = tournamentModelBuilder()->buildModel(
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
    auto index = modelDBContext()->indexOfModel("Tournament",oldModel);
    modelDBContext()->replaceModel("Tournament",index,newModel);
}

void LocalTournamentModelsContext::tournamentRemovePlayer(const QUuid &tournament, const QUuid &player)
{
    auto oldModel = getTournamentModelFromID(tournament);
    auto pList = oldModel->assignedPlayerIdentities();
    pList.removeOne(player);
    auto newModel = tournamentModelBuilder()->buildModel(
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
    auto index = modelDBContext()->indexOfModel("Tournament",oldModel);
    modelDBContext()->replaceModel("Tournament",index,newModel);
}

QList<QUuid> LocalTournamentModelsContext::roundsID()
{
    QList<QUuid> resultingList;
    auto rounds = modelDBContext()->models("Round");
    for (auto r : rounds)
        resultingList << r->id();

    return resultingList;
}

QList<QUuid> LocalTournamentModelsContext::roundsID(const QUuid &tournament)
{
    QList<QUuid> resultingList;
    auto rounds = modelDBContext()->models("Round");
    for (auto r : rounds){
        if(r->parent() == tournament)
            resultingList << r->id();
    }

    return resultingList;
}

QUuid LocalTournamentModelsContext::roundID(const QUuid &tournament, const int &roundIndex)
{
    auto rounds = modelDBContext()->models("Round");
    for (auto model : rounds)
    {
        auto roundModel = dynamic_cast<const DefaultRoundInterface*>(model);
        if(model->parent() == tournament && roundModel->index() == roundIndex)
            return model->id();
    }

    throw THROW_OBJECT_WITH_INDEX_NOT_FOUND(roundIndex);
}

QUuid LocalTournamentModelsContext::addRound(const QUuid &tournament, const int &index)
{
    auto round = roundModelBuilder()->buildModel(
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
    modelDBContext()->addModel("Round",round);
    return roundId;
}

void LocalTournamentModelsContext::removeEmptyRound(const QUuid &round)
{
    auto roundModel = getRoundModelFromID(round);
    auto children = roundSetsID(round);
    auto childrenCount = children.count();
    if(childrenCount >0)
        return;
    auto index = modelDBContext()->indexOfModel("Round",roundModel);
    modelDBContext()->removeModel("Round",index);
}

void LocalTournamentModelsContext::removeEmptySet(const QUuid &set)
{
    auto setModel = getSetModelFromID(set);
    auto children = setPointsID(set);
    auto childrenCount = children.count();
    if(childrenCount > 0)
        return;
    auto index = modelDBContext()->indexOfModel("Set",setModel);
    modelDBContext()->removeModel("Set",index);
    auto parentRoundID = setModel->parent();
    removeEmptyRound(parentRoundID);

}

int LocalTournamentModelsContext::roundIndex(const QUuid &round)
{
    try {
        return getRoundModelFromID(round)->index();
    } catch (const char *msg) {
        throw msg;
    }
}

QUuid LocalTournamentModelsContext::roundTournament(const QUuid &round)
{
    auto model = getRoundModelFromID(round);
    auto parentID = model->parent();
    return parentID;
}

QList<QUuid> LocalTournamentModelsContext::tournamentSetsID(const QUuid &tournament)
{
    QList<QUuid> resultingList;
    auto sets = modelDBContext()->models("Set");
    for (auto model : sets) {
        auto setID = model->id();
        auto roundModel = getRoundModelFromID(model->parent());
        auto tournamentModel = getTournamentModelFromID(roundModel->parent());
        auto tournamentID = tournamentModel->id();
        if(tournamentID == tournament)
            resultingList << setID;
    }
    return resultingList;
}

QList<QUuid> LocalTournamentModelsContext::roundSetsID(const QUuid &round)
{
    QList<QUuid> resultingList;
    auto sets = modelDBContext()->models("Set");
    for (auto model : sets) {
        auto roundSetID = model->id();
        auto roundModel = getRoundModelFromID(model->parent());
        auto roundID = roundModel->id();
        if(roundID == round)
            resultingList << roundSetID;
    }
    return resultingList;
}

QList<QUuid> LocalTournamentModelsContext::tournamentSetsID(const QUuid &tournament, const int &roundIndex)
{
    QList<QUuid> resultingList;
    auto sets = modelDBContext()->models("Set");
    for (auto model : sets) {
        auto round = getRoundModelFromID(model->parent());
        auto modelRoundIndex = round->index();;
        auto t = getTournamentModelFromID(round->parent());
        auto tournamentID = t->id();
        if(tournamentID == tournament && modelRoundIndex == roundIndex)
            resultingList << model->id();
    }

    return resultingList;
}

QUuid LocalTournamentModelsContext::setID(const QUuid &tournament, const int &roundIndex, const int &setIndex)
{
    auto sets = this->tournamentSetsID(tournament,roundIndex);
    for (auto s : sets) {
        auto index = this->setIndex(s);
        if(index == setIndex)
            return s;
    }
    throw THROW_OBJECT_WITH_INDEX_NOT_FOUND(setIndex);
}

QList<QUuid> LocalTournamentModelsContext::setsID()
{
    QList<QUuid> resultingList;
    auto sets = modelDBContext()->models("Set");
    for (auto set : sets) {
        auto id = set->id();
        resultingList << id;
    }
    return resultingList;
}

QUuid LocalTournamentModelsContext::setRound(const QUuid &set)
{
    try {
        auto setModel = getSetModelFromID(set);
        auto parentID = setModel->parent();
        return parentID;

    } catch (const char *msg) {
        throw msg;
    }
}

int LocalTournamentModelsContext::setIndex(const QUuid &set)
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
    auto model = setSetModelBuilder()->buildModel(
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

    modelDBContext()->addModel("Set",model);

    return model->id();
}

QList<QUuid> LocalTournamentModelsContext::setPointsID(const QUuid &set)
{
    QList<QUuid> resultingList;
    auto scores = modelDBContext()->models("Score");
    for (auto scoreModel : scores) {
        auto pointSetID = scoreModel->parent();
        if(pointSetID == set)
            resultingList << pointSetID;
    }
    return resultingList;
}

QList<QUuid> LocalTournamentModelsContext::scores()
{
    QList<QUuid> resultingList;
    auto scores = modelDBContext()->models("Score");
    for (auto scoreModel : scores) {
        auto scoreID = scoreModel->id();
        resultingList << scoreID;
    }
    return resultingList;
}

QList<QUuid> LocalTournamentModelsContext::scores(const QUuid &tournament)
{
    QList<QUuid> resultingList;
    auto scores = modelDBContext()->models("Score");
    for (auto scoreModel : scores) {
        auto parentSetID = scoreModel->parent();
        auto setModel = getSetModelFromID(parentSetID);
        auto parentRoundID = setModel->parent();
        auto roundModel = getRoundModelFromID(parentRoundID);
        auto parentTournamentID = roundModel->parent();
        auto tournamentModel = getTournamentModelFromID(parentTournamentID);
        auto compareTournamentID = tournamentModel->id();
        if(compareTournamentID == tournament)
            resultingList << scoreModel->id();
    }

    return resultingList;
}

QList<QUuid> LocalTournamentModelsContext::scores(const QUuid &tournament, const QUuid &round)
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

QList<QUuid> LocalTournamentModelsContext::scores(const QUuid &tournament, const QUuid &round, const QUuid &set)
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

QList<QUuid> LocalTournamentModelsContext::scores(const QUuid &tournament, const int &hint)
{
    QList<QUuid> resultingList;
    auto scores = modelDBContext()->models("Score");
    for (auto model : scores) {
        auto scoreModel = dynamic_cast<const DefaultPointInterface*>(model);
        auto modelHInt = scoreModel->hint();
        auto parentSetID = model->parent();
        auto setModel = getSetModelFromID(parentSetID);
        auto parentRoundID = setModel->parent();
        auto roundModel = getRoundModelFromID(parentRoundID);
        auto parentTournamentID = roundModel->parent();
        auto tournamentModel = getTournamentModelFromID(parentTournamentID);
        auto compareTournamentID = tournamentModel->id();
        if(compareTournamentID == tournament && modelHInt == hint)
            resultingList << model->id();
    }
    return resultingList;
}

QUuid LocalTournamentModelsContext::setScoreHint(const QUuid &point, const int &hint)
{
    try {
        auto oldModel = getScoreModelFromID(point);
        auto newModel = scoreModelBuilder()->buildModel([oldModel]{
            PointParameters params;
            params.id = oldModel->id();
            params.pointValue = oldModel->point();
            params.throwIndex = oldModel->throwIndex();
            params.setId = oldModel->parent();
            params.playerId = oldModel->player();
            params.scoreValue = oldModel->score();
            return params;
        }(),[hint]{
            ModelOptions options;
            options.generateUniqueId = false;
            options.modelHint = hint;
            return options;
        }());
        auto index = modelDBContext()->indexOfModel("Score",oldModel);
        modelDBContext()->replaceModel("Score",index,newModel);
        return newModel->id();

    } catch (const char msg) {
        throw msg;
    }
}

QUuid LocalTournamentModelsContext::editScore(const QUuid &pointId, const int &value, const int &score, const int &hint)
{
    auto oldScoreModel = getScoreModelFromID(pointId);

    auto newScoreModel = scoreModelBuilder()->buildModel(
                [oldScoreModel, score, value]
    {
        PointParameters params;
        params.id = oldScoreModel->id();
        params.setId = oldScoreModel->parent();
        params.pointValue = value;
        params.playerId = oldScoreModel->player();
        params.throwIndex = oldScoreModel->throwIndex();
        params.scoreValue = score;
        return params;
    }(),[hint]
    {
        ModelOptions options;
        options.generateUniqueId = false;
        options.modelHint = hint;
        return options;
    }());
    auto index = modelDBContext()->indexOfModel("Score",oldScoreModel);
    modelDBContext()->replaceModel("Score",index,newScoreModel);
    return newScoreModel->id();
}

QUuid LocalTournamentModelsContext::scoreSet(const QUuid &point)
{
    auto scoreModel = getScoreModelFromID(point);
    auto parentSetID = scoreModel->parent();
    return parentSetID;
}

int LocalTournamentModelsContext::scoreThrowIndex(const QUuid &point)
{
    try {
        auto scoreModel = getScoreModelFromID(point);
        auto throwIndex = scoreModel->throwIndex();
        return throwIndex;
    } catch (const char *msg) {
        throw msg;
    }
}

int LocalTournamentModelsContext::scorePointValue(const QUuid &point)
{
    try {
        auto scoreModel = getScoreModelFromID(point);
        auto pointValue = scoreModel->point();
        return pointValue;

    }  catch (const char *msg) {
        throw msg;
    }
}

int LocalTournamentModelsContext::scoreValue(const QUuid &point)
{
    try {
        auto scoreModel = getScoreModelFromID(point);
        auto score = scoreModel->score();
        return score;

    }  catch (const char *msg) {
        throw msg;
    }
}

QUuid LocalTournamentModelsContext::scorePlayer(const QUuid &point)
{
    return getScoreModelFromID(point)->player();
}

int LocalTournamentModelsContext::scoreHint(const QUuid &scoreID)
{
    try {
        auto scoreModel = getScoreModelFromID(scoreID);
        auto hint = scoreModel->hint();
        return hint;
    } catch (const char *msg) {
        throw msg;
    }
}

int LocalTournamentModelsContext::scoreKeyCode(const QUuid &scoreID)
{
    try {
        auto scoreModel = getScoreModelFromID(scoreID);
        auto keyCode = scoreModel->keyCode();
        return keyCode;
    } catch (const char *msg) {
        throw msg;
    }
}

QList<QUuid> LocalTournamentModelsContext::pointModels(const QUuid &player)
{
    QList<QUuid> resultingList;
    auto models = modelDBContext()->models("Score");
    for (auto model : models) {
        auto scoreModel = dynamic_cast<const DefaultPointInterface*>(model);
        auto pointID = model->id();
        if(scoreModel->player() == player)
            resultingList << pointID;
    }
    return resultingList;
}

void LocalTournamentModelsContext::removeTournamentRounds(const QUuid &tournament)
{
    auto models = modelDBContext()->models("Round");
    for (int i = 0; i < models.count(); ++i) {
        auto model = models.at(i);
        if(model->parent() == tournament)
        {
            auto index = modelDBContext()->indexOfModel("Round",model);
            modelDBContext()->removeModel("Round",index);
        }
    }
}

void LocalTournamentModelsContext::removeTournamentSets(const QUuid &tournament)
{
    auto models = modelDBContext()->models("Set");
    for (int i = 0; i < models.count(); ++i) {
        auto model = models.at(i);
        auto roundID = model->parent();
        auto roundModel = getRoundModelFromID(roundID);
        auto tournamentID = roundModel->parent();
        if(tournamentID == tournament)
        {
            auto index = modelDBContext()->indexOfModel("Set",model);
            modelDBContext()->removeModel("Set",index);
        }
    }
}

void LocalTournamentModelsContext::removeTournamentScores(const QUuid &tournament)
{
    auto models = modelDBContext()->models("Score");
    for (int i = 0; i < models.count(); ++i) {
        auto model = models.at(i);
        auto setID = model->parent();
        auto setModel = getSetModelFromID(setID);
        auto roundID = setModel->parent();
        auto roundModel = getRoundModelFromID(roundID);
        auto tournamentID = roundModel->parent();
        if(tournamentID == tournament)
        {
            auto index = modelDBContext()->indexOfModel("Score",model);
            modelDBContext()->removeModel("Score",index);
        }
    }
}

QList<QUuid> LocalTournamentModelsContext::playerScores(const QUuid &tournament, const QUuid &player, const int &hint)
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

bool LocalTournamentModelsContext::removeScore(const QUuid &point)
{
    try {
        auto scoreModel = getScoreModelFromID(point);
        auto index = modelDBContext()->indexOfModel("Score",scoreModel);
        auto result = modelDBContext()->removeModel("Score",index);
        return result;
    } catch (const char *msg) {
        return false;
    }
}

void LocalTournamentModelsContext::removePlayerScoreAndRelatives(const QUuid &point)
{
    try {
        auto scoreModel = getScoreModelFromID(point);
        auto parentSetID = scoreModel->parent();
        auto index = modelDBContext()->indexOfModel("Score",scoreModel);
        auto result = modelDBContext()->removeModel("Score",index);
        if(result)
        {
            removeEmptySet(parentSetID);
        }
    } catch (const char *msg) {
        return;
    }
}

QUuid LocalTournamentModelsContext::playerScore(const QUuid &tournament,
                                                const QUuid &player,
                                                const int &roundIndex,
                                                const int &throwIndex,
                                                const int &hint)
{
    auto tournamentScoreModels = scores(tournament);
    for (auto scoreModelID : tournamentScoreModels) {
        auto scoreModel = getScoreModelFromID(scoreModelID);
        auto modelHint = scoreModel->hint();
        auto playerID = scoreModel->player();
        if(playerID != player)
            continue;
        auto leg = scoreThrowIndex(scoreModelID);
        if(leg != throwIndex)
            continue;
        auto setID = scoreSet(scoreModelID);
        auto round = setRound(setID);
        auto rIndex = this->roundIndex(round);
        if(rIndex != roundIndex)
            continue;
        if(modelHint != hint && hint != allHints)
            continue;
        return scoreModelID;
    }

    throw "Object not found";
}

const DefaultTournamentInterface *LocalTournamentModelsContext::getTournamentModelFromID(const QUuid &id)
{
    auto models = modelDBContext()->models("Tournament");
    for (auto model : models) {
        if(model->id() == id)
            return dynamic_cast<const DefaultTournamentInterface*>(model);
    }

    throw THROW_OBJECT_WITH_ID_NOT_FOUND(id.toString());
}

const DefaultRoundInterface *LocalTournamentModelsContext::getRoundModelFromID(const QUuid &id)
{
    auto rounds = modelDBContext()->models("Round");
    for (auto model : rounds) {
        auto round = dynamic_cast<const DefaultRoundInterface*>(model);
        if(round->id() == id)
            return round;
    }

    throw THROW_OBJECT_WITH_ID_NOT_FOUND(id.toString());
}

const DefaultSetInterface *LocalTournamentModelsContext::getSetModelFromID(const QUuid &id)
{
    auto sets = modelDBContext()->models("Set");
    for (auto set : sets)
    {
        auto modelID = set->id();
        if(modelID == id)
            return dynamic_cast<const DefaultSetInterface*>(set);
    }

    throw THROW_OBJECT_WITH_ID_NOT_FOUND(id.toString());
}

const DefaultPointInterface *LocalTournamentModelsContext::getScoreModelFromID(const QUuid &id)
{
    auto models = modelDBContext()->models("Score");
    for (auto model : models)
    {
        if(model->id() == id)
            return dynamic_cast<const DefaultPointInterface*>(model);
    }

    throw THROW_OBJECT_WITH_ID_NOT_FOUND(id.toString());
}

void LocalTournamentModelsContext::removeInconsistentModels()
{
    removeInconsistentScores();
    removeInconsistentSets();
    removeInconsistentRounds();
}

void LocalTournamentModelsContext::removeInconsistentScores()
{
    QVector<const IScore<QUuid>*> inconsistentModels;
    auto models = modelDBContext()->models("Score");
    for (auto model : models) {
        try {
            auto setID = model->parent();
            auto setModel = getSetModelFromID(setID);
            auto roundID = setModel->parent();
            auto roundModel = getRoundModelFromID(roundID);
            auto tournamentID = roundModel->parent();
            getTournamentModelFromID(tournamentID);
        }  catch (...) {
            auto index = modelDBContext()->indexOfModel("Score",model);
            modelDBContext()->removeModel("Score",index);
        }
    }
}

void LocalTournamentModelsContext::removeInconsistentSets()
{
    QVector<const ISet<QUuid,QList<QUuid>>*> inconsistentModels;
    auto models = modelDBContext()->models("Set");
    for (auto model : models) {
        try {
            auto roundID = model->parent();
            auto roundModel = getRoundModelFromID(roundID);
            auto tournamentID = roundModel->parent();
            getTournamentModelFromID(tournamentID);
        }  catch (...) {
            auto index = modelDBContext()->indexOfModel("Set",model);
            modelDBContext()->removeModel("Set",index);
        }
    }
}

void LocalTournamentModelsContext::removeInconsistentRounds()
{
    QVector<int> inconsistentModelIndexes;
    auto models = modelDBContext()->models("Round");
    for (auto model : models) {
        try {
            auto tournamentID = model->parent();
            getTournamentModelFromID(tournamentID);
        }  catch (...) {
            auto index = modelDBContext()->indexOfModel("Round",model);
            modelDBContext()->removeModel("Round",index);
        }
    }
}

QJsonArray LocalTournamentModelsContext::assembleTournamentsJSONArray()
{
    QJsonArray tournamentsJSON;
    auto tournamentsID = tournaments();
    for (auto tournamentID : tournamentsID) {
        QJsonObject obj;
        auto id = tournamentID;
        obj["ID"] = id.toString();
        obj["Title"] = tournamentTitle(id);
        obj["KeyPoint"] = tournamentKeyPoint(id);
        obj["GameMode"] = tournamentGameMode(id);
        obj["winner"] = tournamentDeterminedWinner(id).toString();
        obj["throws"] = tournamentNumberOfThrows(id);
        auto players = tournamentAssignedPlayers(id);

        QJsonArray playersJSON;
        auto count = players.count();
        for (int j = 0; j < count; ++j) {
            auto playerID = players.at(j).toString();
            QJsonObject playerObj;
            playerObj["ID"] = playerID;
            playersJSON.append(playerObj);
        }
        obj["Players"] = playersJSON;
        tournamentsJSON.append(obj);
    }
    return tournamentsJSON;
}

QJsonArray LocalTournamentModelsContext::assembleRoundsJSONArray()
{
    QJsonArray roundsJSON;
    auto roundsID = this->roundsID();
    for (auto roundID : roundsID) {
        QJsonObject roundJSON;
        roundJSON["ID"] = roundID.toString();
        roundJSON["Index"] = roundIndex(roundID);
        roundJSON["TournamentID"] = roundTournament(roundID).toString();
        roundsJSON.append(roundJSON);
    }
    return roundsJSON;
}

QJsonArray LocalTournamentModelsContext::assembeSetsJSONArray()
{
    QJsonArray setsJSON;
    auto setsID = this->setsID();
    for (auto setID : setsID) {
        QJsonObject setJSON;
        setJSON["ID"] = setID.toString();
        setJSON["Index"] = setIndex(setID);
        setJSON["RoundID"] = setRound(setID).toString();
        setsJSON.append(setJSON);
    }
    return setsJSON;
}

QJsonArray LocalTournamentModelsContext::assembleScoresJSONArray()
{
    QJsonArray scoresJSON;
    auto scoresID = scores();
    for (auto scoreID : scoresID) {
        QJsonObject scoreJSON;
        scoreJSON["ID"] = scoreID.toString();
        scoreJSON["PointValue"] = scorePointValue(scoreID);
        scoreJSON["ScoreValue"] = scoreValue(scoreID);
        scoreJSON["SetID"] = scoreSet(scoreID).toString();
        scoreJSON["Index"] = scoreThrowIndex(scoreID);
        scoreJSON["PlayerID"] = scorePlayer(scoreID).toString();
        scoreJSON["Hint"] = scoreHint(scoreID);
        scoreJSON["KeyCode"] = scoreKeyCode(scoreID);
        scoresJSON.append(scoreJSON);
    }
    return scoresJSON;
}

void LocalTournamentModelsContext::extractTournamentModelsFromJSON(const QJsonArray &arr)
{
    auto tournamentsCount = arr.count();
    for (int i = 0; i < tournamentsCount; ++i) {
        auto tournamentJSON = arr[i].toObject();
        auto stringID = tournamentJSON["ID"].toString();
        auto tournamentID = QUuid::fromString(stringID);
        auto title = tournamentJSON["Title"].toString();
        auto keyPoint = tournamentJSON["KeyPoint"].toInt();
        auto gameMode = tournamentJSON["GameMode"].toInt();
        auto throws = tournamentJSON["Throws"].toInt();
        auto winnerStringID = tournamentJSON["WinnerID"].toString();
        auto winnerID = QUuid::fromString(winnerStringID);
        buildTournament(tournamentID,title,keyPoint,throws,gameMode,winnerID);
        auto playersJSONArray = tournamentJSON["Players"].toArray();
        auto playersJSONCount = playersJSONArray.count();
        for (int j = 0; j < playersJSONCount; ++j) {
            auto assignedPlayerJSON = playersJSONArray[j].toObject();
            auto stringID = assignedPlayerJSON["ID"].toString();
            auto playerID = QUuid::fromString(stringID);
            assignPlayerToTournament(tournamentID,playerID);
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
    auto tournament = tournamentModelBuilder()->buildModel([id,title,keyPoint,throws,gameMode,winner]{
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
    modelDBContext()->addModel("Tournament",tournament);
}

void LocalTournamentModelsContext::buildRound(const QUuid &tournament, const int &index, const QUuid &id)
{
    auto round = roundModelBuilder()->buildModel(
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
    modelDBContext()->addModel("Round",round);
}

void LocalTournamentModelsContext::buildSet(const QUuid &id, const QUuid &round, const int &setIndex)
{
    auto model = setSetModelBuilder()->buildModel(
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
    modelDBContext()->addModel("Set",model);
}

void LocalTournamentModelsContext::buildScoreModel(const QUuid &player,
                                                   const QUuid &set,
                                                   const int &throwIndex,
                                                   const int &point,
                                                   const int &score,
                                                   const int &hint,
                                                   const int &keyCode,
                                                   const bool &generateID,
                                                   const QUuid &id)
{
    auto model = scoreModelBuilder()->buildModel(
                [id,set,throwIndex,point,keyCode,player,score]
    {
        PointParameters params;
        params.id = id;
        params.setId = set;
        params.playerId = player;
        params.pointValue = point;
        params.throwIndex = throwIndex;
        params.scoreValue = score;
        params.keyCode = keyCode;

        return params;
    }(),[generateID,hint]{
        ModelOptions options;
        options.modelHint = hint;
        options.generateUniqueId = generateID;
        return options;
    }());
    modelDBContext()->addModel("Score",model);
}

ImodelsDBContext<IModel<QUuid>, QString> *LocalTournamentModelsContext::modelDBContext() const
{
    return _dbContext;
}

AbstractTournamentModelsContext *LocalTournamentModelsContext::setModelDBContext(ImodelsDBContext<IModel<QUuid>,
                                                                                 QString> *context)
{
    _dbContext = context;
    return this;
}

void LocalTournamentModelsContext::removeTournamentModel(const QUuid &tournament)
{
    auto models = modelDBContext()->models("Tournament");
    for (auto model : models) {
        auto id = model->id();
        if(id == tournament)
        {
            auto index = modelDBContext()->indexOfModel("Tournament",model);
            modelDBContext()->removeModel("Tournament",index);
            return;
        }
    }
}

void LocalTournamentModelsContext::removePointModel(const QUuid &point)
{
    auto models = modelDBContext()->models("Score");
    for (auto model : models) {
        auto id = model->id();
        if(id == point)
        {
            auto index = modelDBContext()->indexOfModel("Score",model);
            modelDBContext()->removeModel("Score",index);
            return;
        }
    }
}

int LocalTournamentModelsContext::playerScoreCount(const int &hint)
{
    auto count = 0;
    auto models = modelDBContext()->models("Score");
    for (auto model : models) {
        auto scoreModel = dynamic_cast<const DefaultPointInterface*>(model);
        if(scoreModel->hint() == hint || hint == allHints)
            count++;
    }
    return count;
}

void LocalTournamentModelsContext::addScore(const QUuid &tournament,
                                            const QUuid &player,
                                            const int &roundIndex,
                                            const int &setIndex,
                                            const int &throwIndex,
                                            const int &point,
                                            const int &score,
                                            const int &keyCode,
                                            const bool &isWinnerDetermined)
{
    auto setID = this->setID(tournament,roundIndex,setIndex);
    buildScoreModel(player,setID,throwIndex,point,score,ModelDisplayHint::DisplayHint,keyCode);
    if(isWinnerDetermined)
        setTournamentDeterminedWinner(tournament,player);
    removeHiddenScores(tournament);
    emit scoreAddedToDataContext(player,point,score);
}

void LocalTournamentModelsContext::removeHiddenScores(const QUuid &tournament)
{
    auto scoresID = scores(tournament,ModelDisplayHint::HiddenHint);
    for (auto scoreID : scoresID)
        removeScore(scoreID);
}

int LocalTournamentModelsContext::score(const QUuid &tournament, const QUuid &player)
{
    int totalScore = tournamentKeyPoint(tournament);
    auto playerScoresID = playerScores(tournament,player,ModelDisplayHint::DisplayHint);
    for (auto scoreID : playerScoresID) {
        auto point = scorePointValue(scoreID);
        totalScore -= point;
    }
    return totalScore;
}

int LocalTournamentModelsContext::score(const QUuid &player)
{
    Q_UNUSED(player);
    return -1;
}

void LocalTournamentModelsContext::extractRoundModelsFromJSON(const QJsonArray &arr)
{
    for (auto JSONValue : arr) {
        auto stringID = JSONValue["ID"].toString();
        auto id = QUuid::fromString(stringID);
        auto index = JSONValue["Index"].toInt();
        auto tournamentStringID = JSONValue["TournamentID"].toString();
        auto tournamentID = QUuid::fromString(tournamentStringID);
        buildRound(tournamentID,index,id);
    }
}

void LocalTournamentModelsContext::extractSetModelsFromJSON(const QJsonArray &arr)
{
    for (auto JSONValue : arr) {
        auto stringID = JSONValue["ID"].toString();
        auto id = QUuid::fromString(stringID);
        auto index = JSONValue["Index"].toInt();
        auto roundStringID = JSONValue["RoundID"].toString();
        auto roundID = QUuid::fromString(roundStringID);
        buildSet(id,roundID,index);
        cout << stringID.toStdString() << endl;
    }
}

void LocalTournamentModelsContext::extractScoreModelsFromJSON(const QJsonArray &arr)
{
    for (auto JSONValue : arr) {
        auto stringID = JSONValue["ID"].toString();
        auto id = QUuid::fromString(stringID);
        auto pointValue = JSONValue["PointValue"].toInt();
        auto scoreValue = JSONValue["ScoreValue"].toInt();
        auto setStringID = JSONValue["SetID"].toString();
        auto setID = QUuid::fromString(setStringID);
        auto playerStringID = JSONValue["PlayerID"].toString();
        auto playerID = QUuid::fromString(playerStringID);
        auto throwIndex = JSONValue["Index"].toInt();
        auto keyCode = JSONValue["KeyCode"].toInt();
        auto scoreHint = JSONValue["Hint"].toInt();
        buildScoreModel(playerID,setID,throwIndex,pointValue,scoreValue,scoreHint,keyCode,false,id);
    }
}

