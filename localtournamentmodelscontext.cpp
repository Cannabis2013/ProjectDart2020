#include "localtournamentmodelscontext.h"

void LocalTournamentModelsContext::read()
{
    QJsonObject JSONObject;
    // Extact content from file
    try {
        JSONObject = readJSONFromFile("TournamentModels");
    } catch (...) {
        return;
    }
    // Assemble json objects from content
    auto tournamentsJSONArray = JSONObject["TournamentsData"].toArray();
    auto scoresJSONArray = JSONObject["ScoresData"].toArray();
    // Exctract models from json objects
    extractTournamentModelsFromJSON(tournamentsJSONArray);
    extractScoreModelsFromJSON(scoresJSONArray);
}

void LocalTournamentModelsContext::write()
{
    /*
     * Persist tournament models
     */
    QJsonObject modelJSON;
    modelJSON["TournamentsData"] = assembleTournamentsJSONArray();
    modelJSON["ScoresData"] = assembleScoresJSONArray();
    writeJSONToFile(modelJSON,"TournamentModels");
}

LocalTournamentModelsContext::~LocalTournamentModelsContext()
{
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

AbstractTournamentModelsContext *LocalTournamentModelsContext::setModelBuilder(DefaultTournamentModelBuilder *builder)
{
    _tournamentModelBuilder = builder;
    return this;
}

DefaultTournamentModelBuilder *LocalTournamentModelsContext::modelBuilder()
{
    return _tournamentModelBuilder;
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
    /*
     * - Remove models associated to the tournament
     * - Add a round model and a set model
     */
    removeModelsRelatedToTournament(tournament);
    setTournamentDeterminedWinner(tournament,QUuid());
    emit tournamentResetSuccess();
}

void LocalTournamentModelsContext::assembleAndAddTournament(const QString &title,
                                                            const QList<int> &data,
                                                            const QList<QUuid> &assignedPlayersID)
{
    auto tournamentID = createTournament(title,
                                         data);
    for (auto assignedPlayerID : assignedPlayersID)
        assignPlayerToTournament(tournamentID,assignedPlayerID);
    write();
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
    write();
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
    auto modelTableViewHint = tournamentTableViewHint(tournament);
    auto playersID = tournamentAssignedPlayers(tournament);
    auto winnerID = tournamentDeterminedWinner(tournament);
    emit sendTournamentMeta(title,gameMode,keyPoint,modelTableViewHint,winnerID,playersID);
}

void LocalTournamentModelsContext::handleRequestTournamentDetails(const int &index)
{
    try {
        auto tournamentID = tournamentIDFromIndex(index);
        auto keyPoint = tournamentKeyPoint(tournamentID);
        auto lastThrowKeyCode = tournamentLastThrowKeyCode(tournamentID);
        auto numberOfThrows = tournamentNumberOfThrows(tournamentID);
        auto gameMode = tournamentGameMode(tournamentID);
        auto inputMode = tournamentInputMode(tournamentID);
        auto assignedPlayersID = tournamentAssignedPlayers(tournamentID);
        auto winnerID = tournamentDeterminedWinner(tournamentID);
        emit sendTournamentDetails(tournamentID,
                                   winnerID,
                                   keyPoint,
                                   inputMode,
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

    QList<int> userScores;
    for (auto playerID : assignedPlayersID) {
        auto s = score(tournament,playerID);
        userScores << s;
    }
    emit sendTournamentIndexes(roundIndex,
                               setIndex,
                               throwIndex,
                               turnIndex,
                               totalTurns,
                               userScores);
}

void LocalTournamentModelsContext::handleRequestAssignedPlayers(const QUuid &tournament)
{
    auto assignedPlayersID = tournamentAssignedPlayers(tournament);
    emit sendAssignedPlayers(assignedPlayersID);
}

QUuid LocalTournamentModelsContext::createTournament(const QString &title,
                                                     const QList<int> &data)
{
    /*
     * Data array allocate each memmory location to the following values:
     *  - [0] = Gamemode
     *  - [1] = Keypoint
     *  - [2] = KeyCode (win condition)
     *  - [3] = TableViewHint
     *  - [4] = InputMode
     *  - [5] = Number of throws
     */
    // Build model
    auto tournament = modelBuilder()->buildTournamentModel([this,title,data]
    {
        TournamentParameters params;
        params.title = title;
        params.gameMode = data[0];
        params.keyPoint = data[1];
        params.winConditionKey = data[2];
        params.modelTableViewHint = data[3];
        params.inputMode = data[4];
        params.throws = data[5];
        params.tournamentsCount = this->tournamentsCount();
        return params;
    }(),[]{
        ModelOptions options;
        options.generateUniqueId = true;
        return options;
    }());
    // Add model to dbcontext
    _dbContext->addModel("Tournament",tournament);
    // Return model id
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
     *  - Remove ScoreModel's
     */
    removeTournamentScores(tournament);
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
    auto model = getTournamentModelFromID(tournament);
    auto numberOfThrows = model->numberOfThrows();
    return numberOfThrows;
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

int LocalTournamentModelsContext::tournamentTableViewHint(const QUuid &tournament)
{
    auto tournamentModel = getTournamentModelFromID(tournament);
    auto hint = tournamentModel->modelTableViewHint();
    return hint;
}

int LocalTournamentModelsContext::tournamentInputMode(const QUuid &tournament)
{
    auto tournamentModel = getTournamentModelFromID(tournament);
    auto inputMode = tournamentModel->inputMode();
    return inputMode;
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
    auto newModel = modelBuilder()->buildTournamentModel(
                    [oldModel, winner]
                    {
                        TournamentParameters params;
                        params.id = oldModel->id();
                        params.title = oldModel->title();
                        params.status = oldModel->status();
                        params.gameMode = oldModel->gameMode();
                        params.keyPoint = oldModel->keyPoint();
                        params.modelTableViewHint = oldModel->modelTableViewHint();
                        params.inputMode = oldModel->inputMode();
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
    auto assignedPlayers = oldModel->assignedPlayerIdentities();
    assignedPlayers.append(player);
    auto newModel = modelBuilder()->buildTournamentModel(
                [oldModel, assignedPlayers]
    {
        TournamentParameters params;
        params.id = oldModel->id();
        params.title = oldModel->title();
        params.status = oldModel->status();
        params.gameMode = oldModel->gameMode();
        params.keyPoint = oldModel->keyPoint();
        params.modelTableViewHint = oldModel->modelTableViewHint();
        params.inputMode = oldModel->inputMode();
        params.throws = oldModel->numberOfThrows();
        params.winner = oldModel->winner();
        params.playerIdentities = assignedPlayers;
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
    auto newModel = modelBuilder()->buildTournamentModel(
                [oldModel, pList]
    {
        TournamentParameters params;
        params.id = oldModel->id();
        params.title = oldModel->title();
        params.status = oldModel->status();
        params.gameMode = oldModel->gameMode();
        params.keyPoint = oldModel->keyPoint();
        params.modelTableViewHint = oldModel->modelTableViewHint();
        params.inputMode = oldModel->inputMode();
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
        auto compareTournamentID = scoreModel->parent();
        if(compareTournamentID == tournament)
            resultingList << scoreModel->id();
    }

    return resultingList;
}

QList<QUuid> LocalTournamentModelsContext::scores(const QUuid &tournament, const int &round)
{
    QList<QUuid> resultingList;
    auto tPoints = this->scores(tournament);
    for (auto pointID : tPoints) {
        auto s = this->getScoreModelFromID(pointID);
        auto roundIndex = s->roundIndex();
        if(roundIndex == round)
            resultingList << pointID;
    }

    return resultingList;
}

QList<QUuid> LocalTournamentModelsContext::scores(const QUuid &tournament,
                                                  const int &round,
                                                  const int &set)
{
    QList<QUuid> resultingList;
    auto p = this->scores(tournament,round);
    for (auto scoreModelID : p) {
        auto scoreModel = getScoreModelFromID(scoreModelID);
        auto setIndex = scoreModel->setIndex();
        if(setIndex == set)
            resultingList << scoreModelID;
    }

    return resultingList;
}

QList<QUuid> LocalTournamentModelsContext::scores(const int &hint, const QUuid &tournament)
{
    QList<QUuid> resultingList;
    auto scores = this->scores(tournament);
    for (auto model : scores) {
        auto scoreModel = getScoreModelFromID(model);
        auto scoreModelHint = scoreModel->hint();
        if(scoreModelHint == hint)
            resultingList << model;
    }
    return resultingList;
}

QUuid LocalTournamentModelsContext::setScoreHint(const QUuid &point,
                                                 const int &hint)
{
    try {
        auto oldModel = getScoreModelFromID(point);
        auto newModel = modelBuilder()->buildScoreModel([oldModel,hint]{
            ScoreParameters params;
            params.id = oldModel->id();
            params.tournament = oldModel->parent();
            params.pointValue = oldModel->point();
            params.roundIndex = oldModel->roundIndex();
            params.setIndex = oldModel->setIndex();
            params.throwIndex = oldModel->throwIndex();
            params.playerId = oldModel->player();
            params.scoreValue = oldModel->score();
            params.hint = hint;
            return params;
        }(),[]{
            ModelOptions options;
            options.generateUniqueId = false;
            return options;
        }());
        auto index = modelDBContext()->indexOfModel("Score",oldModel);
        modelDBContext()->replaceModel("Score",index,newModel);
        return newModel->id();

    } catch (const char msg) {
        throw msg;
    }
}

QUuid LocalTournamentModelsContext::editScore(const QUuid &pointId,
                                              const int &value,
                                              const int &score,
                                              const int &hint)
{
    auto oldScoreModel = getScoreModelFromID(pointId);

    auto newScoreModel = modelBuilder()->buildScoreModel(
                [oldScoreModel, score, value,hint]
    {
        ScoreParameters params;
        params.id = oldScoreModel->id();
        params.roundIndex = oldScoreModel->roundIndex();
        params.setIndex = oldScoreModel->setIndex();
        params.pointValue = value;
        params.playerId = oldScoreModel->player();
        params.throwIndex = oldScoreModel->throwIndex();
        params.scoreValue = score;
        params.hint = hint;
        return params;
    }(),[]
    {
        ModelOptions options;
        options.generateUniqueId = false;
        return options;
    }());
    auto index = modelDBContext()->indexOfModel("Score",oldScoreModel);
    modelDBContext()->replaceModel("Score",index,newScoreModel);
    return newScoreModel->id();
}

int LocalTournamentModelsContext::scoreRoundIndex(const QUuid &playerScore)
{
    auto scoreModel = getScoreModelFromID(playerScore);
    auto roundIndex = scoreModel->roundIndex();
    return roundIndex;
}

int LocalTournamentModelsContext::scoreSetIndex(const QUuid &playerScore)
{
    auto scoreModel = getScoreModelFromID(playerScore);
    auto setIndex = scoreModel->setIndex();
    return setIndex;
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

QUuid LocalTournamentModelsContext::scoreTournament(const QUuid &playerScore)
{
    auto model = getScoreModelFromID(playerScore);
    auto tournamentID = model->parent();
    return tournamentID;
}

QUuid LocalTournamentModelsContext::scorePlayer(const QUuid &point)
{
    auto model = getScoreModelFromID(point);
    auto playerID = model->player();
    return playerID;

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
        auto scoreModel = dynamic_cast<const DefaultScoreInterface*>(model);
        auto pointID = model->id();
        if(scoreModel->player() == player)
            resultingList << pointID;
    }
    return resultingList;
}

void LocalTournamentModelsContext::removeTournamentScores(const QUuid &tournament)
{
    auto scoresID = this->scores(tournament);
    for (auto scoreID : scoresID) {
        auto scoreModel = getScoreModelFromID(scoreID);
        auto tournamentID = scoreModel->parent();
        if(tournamentID == tournament)
        {
            auto index = modelDBContext()->indexOfModel("Score",scoreModel);
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

void LocalTournamentModelsContext::removePlayerScore(const QUuid &point)
{
    try {
        auto scoreModel = getScoreModelFromID(point);
        auto index = modelDBContext()->indexOfModel("Score",scoreModel);
        modelDBContext()->removeModel("Score",index);
    } catch (const char *msg) {
        return;
    }
}

QUuid LocalTournamentModelsContext::playerScore(const QUuid &tournament,
                                                const QUuid &player,
                                                const int &round,
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
        auto roundIndex = scoreModel->roundIndex();
        if(roundIndex != round)
            continue;
        if(hint != modelHint && hint != allHints)
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

const DefaultScoreInterface *LocalTournamentModelsContext::getScoreModelFromID(const QUuid &id)
{
    auto models = modelDBContext()->models("Score");
    for (auto model : models)
    {
        if(model->id() == id)
            return dynamic_cast<const DefaultScoreInterface*>(model);
    }

    throw THROW_OBJECT_WITH_ID_NOT_FOUND(id.toString());
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
        obj["TableViewHint"] = tournamentTableViewHint(id);
        obj["InputMode"] = tournamentInputMode(id);
        obj["Winner"] = tournamentDeterminedWinner(id).toString();
        obj["Throws"] = tournamentNumberOfThrows(id);
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

QJsonArray LocalTournamentModelsContext::assembleScoresJSONArray()
{
    QJsonArray scoresJSON;
    auto scoresID = scores();
    for (auto scoreID : scoresID) {
        QJsonObject scoreJSON;
        scoreJSON["ID"] = scoreID.toString();
        scoreJSON["Tournament"] = scoreTournament(scoreID).toString();
        scoreJSON["PointValue"] = scorePointValue(scoreID);
        scoreJSON["ScoreValue"] = scoreValue(scoreID);
        scoreJSON["RoundIndex"] = scoreRoundIndex(scoreID);
        scoreJSON["SetIndex"] = scoreSetIndex(scoreID);
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
        auto tableViewHint = tournamentJSON["TableViewHint"].toInt();
        auto inputMode = tournamentJSON["InputMode"].toInt();
        auto gameMode = tournamentJSON["GameMode"].toInt();
        auto throws = tournamentJSON["Throws"].toInt();
        auto winnerStringID = tournamentJSON["WinnerID"].toString();
        auto winnerID = QUuid::fromString(winnerStringID);
        buildTournament(tournamentID,title,
                        keyPoint,
                        tableViewHint,
                        inputMode,
                        throws,
                        gameMode,
                        winnerID);
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
                                                   const int &tableViewHint,
                                                   const int &inputMode,
                                                   const int &throws,
                                                   const int &gameMode,
                                                   const QUuid &winner)
{
    auto tournament = modelBuilder()->buildTournamentModel(
                [id,title,keyPoint,tableViewHint,inputMode,throws,gameMode,winner]{
                TournamentParameters params;
                params.id = id;
                params.title = title;
                params.keyPoint = keyPoint;
                params.modelTableViewHint = tableViewHint;
                params.inputMode = inputMode;
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


void LocalTournamentModelsContext::buildScoreModel(const QUuid &tournament,
                                                   const QUuid &player,
                                                   const QList<int> &dataValues,
                                                   const int &hint,
                                                   const bool &generateID,
                                                   const QUuid &id)
{
    /*
     * dataValues location/value table:
     *  - [0] = Round index
     *  - [1] = Set/player index
     *  - [2] = throwindex
     *  - [3] = point value
     *  - [4} = score value
     *  - [5] = keycode
     */

    // Build model
    auto model = modelBuilder()->buildScoreModel(
                [id,tournament,dataValues,player,hint]
    {
        ScoreParameters params;
        params.id = id;
        params.playerId = player;
        params.hint = hint;
        params.tournament = tournament;
        params.roundIndex = dataValues.at(0);
        params.setIndex = dataValues.at(1);
        params.throwIndex = dataValues.at(2);
        params.pointValue = dataValues.at(3);
        params.scoreValue = dataValues.at(4);
        params.keyCode = dataValues.at(5);

        return params;
    }(),[generateID]{
        ModelOptions options;
        options.generateUniqueId = generateID;
        return options;
    }());
    // Add model to db context
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
        auto scoreModel = dynamic_cast<const DefaultScoreInterface*>(model);
        if(scoreModel->hint() == hint || hint == allHints)
            count++;
    }
    return count;
}

void LocalTournamentModelsContext::addScore(const QUuid &tournament,
                                            const QUuid &player,
                                            const QList<int> &dataValues,
                                            const bool &isWinnerDetermined)
{
    buildScoreModel(tournament,
                    player,
                    dataValues,
                    ModelDisplayHint::DisplayHint);
    if(isWinnerDetermined)
        setTournamentDeterminedWinner(tournament,player);
    removeHiddenScores(tournament);
    emit scoreAddedToDataContext(player,dataValues.at(3),dataValues.at(4));
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

void LocalTournamentModelsContext::extractScoreModelsFromJSON(const QJsonArray &arr)
{
    for (auto JSONValue : arr) {
        QList<int> dataValues;
        auto stringID = JSONValue["ID"].toString();
        auto id = QUuid::fromString(stringID);
        auto tournament = JSONValue["Tournament"].toString();
        auto tournamentID = QUuid::fromString(tournament);
        auto playerStringID = JSONValue["PlayerID"].toString();
        auto playerID = QUuid::fromString(playerStringID);
        dataValues.append(JSONValue["RoundIndex"].toInt());
        dataValues.append(JSONValue["SetIndex"].toInt());
        dataValues.append(JSONValue["Index"].toInt());
        dataValues.append(JSONValue["PointValue"].toInt());
        dataValues.append(JSONValue["ScoreValue"].toInt());
        dataValues.append(JSONValue["KeyCode"].toInt());
        auto scoreHint = JSONValue["Hint"].toInt();
        buildScoreModel(tournamentID,
                        playerID,
                        dataValues,
                        scoreHint,
                        false,
                        id);
    }
}

