#include "jsondbcontext.h"

void JsonDbContext::loadIntoMemmory()
{
    QJsonObject JSONObject;
    // Extact content from file
    try {
        JSONObject = readJSONFromFile("Models");
    } catch (...) {
        return;
    }
    // Assemble json objects from content
    auto tournamentsJSONArray = JSONObject["FTPTournaments"].toArray();
    auto scoresJSONArray = JSONObject["FTPScores"].toArray();
    auto playerJSONArray = JSONObject["Players"].toArray();
    // Exctract models from json objects
    extractTournamentModelsFromJSON(tournamentsJSONArray);
    extractScoreModelsFromJSON(scoresJSONArray);
    extractPlayerModelsFromJSON(playerJSONArray);
}

void JsonDbContext::saveState()
{
    /*
     * Persist tournament models
     */
    QJsonObject modelJSON;
    /*
     * Persist 'first to post' tournaments
     */
    modelJSON["FTPTournaments"] = assembleFTPTournamentsJSONArray();
    modelJSON["FTPScores"] = assembleScoresJSONArray();
    modelJSON["Players"] = assemblePlayersJSONArray();
    writeJSONToFile(modelJSON,"Models");
}

void JsonDbContext::addTournament(DbModels::TournamentInterface *model)
{
    _tournamentModels.append(model);
    saveState();
}

QVector<const DbModels::TournamentInterface*> JsonDbContext::tournaments()
{
    return _tournamentModels;
}

void JsonDbContext::removeTournamentModel(const QUuid &id)
{
    for (auto i = _tournamentModels.begin();i != _tournamentModels.end();i++) {
        auto model = *i;
        auto modelId = model->id();
        if(modelId == id)
        {
            _tournamentModels.removeOne(model);
            return;
        }
    }
}

void JsonDbContext::removeTournamentModel(const int &index)
{
    _tournamentModels.removeAt(index);
    saveState();
}

int JsonDbContext::indexOfTournament(const DbModels::TournamentInterface *model)
{
    auto index = _tournamentModels.indexOf(model);
    return index;
}

void JsonDbContext::replaceTournament(const int &index, const DbModels::TournamentInterface *tournament)
{
    _tournamentModels.replace(index,tournament);
    saveState();
}

const DbModels::TournamentInterface *JsonDbContext::tournamentModel(const int &index)
{
    auto model = _tournamentModels.at(index);
    return model;
}

const DbModels::TournamentInterface *JsonDbContext::tournamentModel(const QUuid &id)
{
    for (auto var = _tournamentModels.begin(); var != _tournamentModels.end(); ++var) {
        auto model = *var;
        if(model->id() == id)
            return model;
    }
    return nullptr;
}

void JsonDbContext::addScoreModel(const IScore<QUuid> *model)
{
    _scoreModels.append(model);
    saveState();
}

const IScore<QUuid> *JsonDbContext::scoreModel(const int &index)
{
    auto model = _scoreModels.at(index);
    return model;
}

QVector<const IScore<QUuid> *> JsonDbContext::scoreModels()
{
    return _scoreModels;
}

void JsonDbContext::replaceScoreModel(const int &index, const IScore<QUuid>* score)
{
    _scoreModels.replace(index,score);
}

int JsonDbContext::indexOfScoreModel(const DbModels::ScoreInterface *score)
{
    auto index = _scoreModels.indexOf(score);
    return index;
}

void JsonDbContext::removeScoreModel(const int &index)
{
    _scoreModels.remove(index);
}

QJsonArray JsonDbContext::assembleFTPTournamentsJSONArray()
{
    QJsonArray tournamentsJSON;
    auto tournamentModels = tournaments();
    for (auto i = _tournamentModels.begin();i != _tournamentModels.end();i++) {
        auto model = *i;
        if(model->gameMode() != GameModes::FirstToPost)
            continue;
        QJsonObject obj;
        auto tournament = dynamic_cast<const FTPTournament*>(model);
        auto tournamentId = model->id();
        obj["Id"] = tournamentId.toString();
        obj["Title"] = tournament->title();
        obj["KeyPoint"] = tournament->keyPoint();
        obj["GameMode"] = tournament->gameMode();
        obj["TableViewHint"] = tournament->displayHint();
        obj["InputMode"] = tournament->inputHint();
        obj["Winner"] = tournament->winnerId().toString();
        obj["Attempts"] = tournament->attempts();
        auto players = tournament->assignedPlayerIdentities();

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

QJsonArray JsonDbContext::assembleScoresJSONArray()
{
    QJsonArray scoresJSON;
    auto scoreModels = this->scoreModels();
    for (auto i = _scoreModels.begin();i != _scoreModels.end();i++) {
        auto model = *i;
        auto tournamentId = model->parent();
        auto tournament = tournamentModel(tournamentId);
        auto gameMode = tournament->gameMode();
        auto ftpScoreModel = dynamic_cast<const FTPScore*>(model);
        if(gameMode != GameModes::FirstToPost)
            continue;
        // Check if FTP model
        QJsonObject scoreJSON;
        scoreJSON["Id"] = ftpScoreModel->id().toString();
        scoreJSON["Tournament"] = ftpScoreModel->tournament().toString();
        scoreJSON["PointValue"] = ftpScoreModel->point();
        scoreJSON["ScoreValue"] = ftpScoreModel->score();
        scoreJSON["RoundIndex"] = ftpScoreModel->roundIndex();
        scoreJSON["SetIndex"] = ftpScoreModel->setIndex();
        scoreJSON["Attempt"] = ftpScoreModel->attempt();
        scoreJSON["PlayerId"] = ftpScoreModel->player().toString();
        scoreJSON["Hint"] = ftpScoreModel->hint();
        scoreJSON["KeyCode"] = ftpScoreModel->keyCode();
        scoresJSON.append(scoreJSON);
    }
    return scoresJSON;
}

QJsonArray JsonDbContext::assemblePlayersJSONArray()
{
    QJsonArray playersJSON;
    auto players = playerModels();
    for (auto playerModel : players) {
        QJsonObject playerJSON;
        playerJSON["Id"] = playerModel->id().toString();
        playerJSON["UserName"] = playerModel->playerName();
        playerJSON["Mail"] = playerModel->email();
        playersJSON.append(playerJSON);
    }
    return playersJSON;
}

void JsonDbContext::extractTournamentModelsFromJSON(const QJsonArray &arr)
{
    auto tournamentsCount = arr.count();
    for (int i = 0; i < tournamentsCount; ++i) {
        auto tournamentJSON = arr[i].toObject();
        auto stringID = tournamentJSON["Id"].toString();
        auto tournamentId = QUuid::fromString(stringID);
        auto title = tournamentJSON["Title"].toString();
        auto keyPoint = tournamentJSON["KeyPoint"].toInt();
        auto tableViewHint = tournamentJSON["TableViewHint"].toInt();
        auto inputMode = tournamentJSON["InputMode"].toInt();
        auto gameMode = tournamentJSON["GameMode"].toInt();
        auto attempts = tournamentJSON["Attempts"].toInt();
        auto winnerStringID = tournamentJSON["Winner"].toString();
        auto winnerId = QUuid::fromString(winnerStringID);
        auto playersJSONArray = tournamentJSON["Players"].toArray();
        auto playersJSONCount = playersJSONArray.count();
        QVector<QUuid> assignedPlayerIds;
        for (int j = 0; j < playersJSONCount; ++j) {
            auto assignedPlayerJSON = playersJSONArray[j].toObject();
            auto stringID = assignedPlayerJSON["ID"].toString();
            auto playerId = QUuid::fromString(stringID);
            assignedPlayerIds << playerId;
        }
        auto tournamentModel = FTPTournament::createInstance()
                ->setId(tournamentId)
                ->setTitle(title)
                ->setKeyPoint(keyPoint)
                ->setDisplayHint(tableViewHint)
                ->setInputMode(inputMode)
                ->setGameMode(gameMode)
                ->setAttempts(attempts)
                ->setWinner(winnerId)
                ->setAssignedPlayerIdentities(assignedPlayerIds);
        _tournamentModels.append(tournamentModel);
    }
}

void JsonDbContext::extractScoreModelsFromJSON(const QJsonArray &arr)
{
    for (auto i = arr.begin();i != arr.end();i++) {
        auto JSONValue = *i;
        auto stringID = JSONValue["Id"].toString();
        auto id = QUuid::fromString(stringID);
        auto tournament = JSONValue["Tournament"].toString();
        auto tournamentId = QUuid::fromString(tournament);
        auto playerStringID = JSONValue["PlayerId"].toString();
        auto playerId = QUuid::fromString(playerStringID);
        auto roundIndex = JSONValue["RoundIndex"].toInt();
        auto setIndex = JSONValue["SetIndex"].toInt();
        auto attempt = JSONValue["Attempt"].toInt();
        auto pointValue = JSONValue["PointValue"].toInt();
        auto scoreValue = JSONValue["ScoreValue"].toInt();
        auto keyCode = JSONValue["KeyCode"].toInt();
        auto scoreHint = JSONValue["Hint"].toInt();
        auto scoreModel = FTPScore::createInstance()
                ->setId(id)
                ->setTournament(tournamentId)
                ->setPlayer(playerId)
                ->setRoundIndex(roundIndex)
                ->setSetIndex(setIndex)
                ->setAttempt(attempt)
                ->setPointValue(pointValue)
                ->setScoreValue(scoreValue)
                ->setKeyCode(keyCode)
                ->setDisplayHint(scoreHint);
        _scoreModels.append(scoreModel);
    }
}

void JsonDbContext::extractPlayerModelsFromJSON(const QJsonArray &arr)
{
    for (auto i = arr.begin();i != arr.end();i++) {
        auto JSONValue = *i;
        auto stringID = JSONValue["Id"].toString();
        auto playerId = QUuid::fromString(stringID);
        auto playerName = JSONValue["UserName"].toString();
        auto mail = JSONValue["Mail"].toString();
        auto model = Player::createInstance()
                ->setId(playerId)
                ->setUserName(playerName)
                ->setEmail(mail);
        _playerModels.append(model);
    }
}

QVector<const DbModels::PlayerInterface *> JsonDbContext::playerModels()
{
    return _playerModels;
}

void JsonDbContext::addPlayerModel(const DbModels::PlayerInterface *player)
{
    _playerModels.append(player);
    saveState();
}

void JsonDbContext::removePlayerModel(const QUuid &id)
{
    for (auto playerInterface : _playerModels) {
        if(playerInterface->id() == id)
        {
            _playerModels.removeOne(playerInterface);
            return;
        }
    }
}

void JsonDbContext::removePlayerModel(const int &index)
{
    _playerModels.remove(index);
    saveState();
}

int JsonDbContext::indexOfPlayerModel(const DbModels::PlayerInterface *player)
{
    auto index = _playerModels.indexOf(player);
    return index;
}

void JsonDbContext::replacePlayerModel(const int &index, const DbModels::PlayerInterface *player)
{
    _playerModels.replace(index,player);
    saveState();
}

const DbModels::PlayerInterface *JsonDbContext::playerModel(const int &index)
{
    auto model = _playerModels.at(index);
    return model;
}
