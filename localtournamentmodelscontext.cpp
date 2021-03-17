#include "localtournamentmodelscontext.h"

LocalTournamentModelsContext::~LocalTournamentModelsContext()
{
}

LocalTournamentModelsContext *LocalTournamentModelsContext::createInstance()
{
    return new LocalTournamentModelsContext();
}

LocalTournamentModelsContext* LocalTournamentModelsContext::setup()
{
    return this;
}

LocalTournamentModelsContext *LocalTournamentModelsContext::setTournamentBuilder(LMC::ITournamentModelsBuilder *builder)
{
    _tournamentModelBuilder = builder;
    return this;
}

LMC::ITournamentModelsBuilder *LocalTournamentModelsContext::tournamentBuilder()
{
    return _tournamentModelBuilder;
}

LocalTournamentModelsContext *LocalTournamentModelsContext::setScoreBuilder(LMC::IScoreModelsBuilder *builder)
{
    _scoreModelbuilder = builder;
    return this;
}

LMC::IScoreModelsBuilder *LocalTournamentModelsContext::scoreBuilder()
{
    return _scoreModelbuilder;
}

QUuid LocalTournamentModelsContext::assembleAndAddFTPTournament(const QString &title,
                                                                const QVector<int> &data,
                                                                const QVector<QUuid>& playerIds)
{
    /*
     * Data array allocate each memmory location to the following values:
     *  - [0] = Gamemode
     *  - [1] = Keypoint
     *  - [2] = KeyCode (win condition)
     *  - [3] = TableViewHint
     *  - [4] = InputMode
     *  - [5] = Number of attempts
     */
    // Build model
    auto tournament = tournamentBuilder()->buildFTPTournament([this,title,data,playerIds]
    {
        TBC::FTPParameters params;
        params.title = title;
        params.gameMode = data[0];
        params.keyPoint = data[1];
        params.winConditionKey = data[2];
        params.modelTableViewHint = data[3];
        params.inputMode = data[4];
        params.attempts = data[5];
        params.playerIdentities = playerIds;
        params.tournamentsCount = this->tournamentsCount();
        return params;
    }(),[]{
        TBC::ModelOptions options;
        options.generateUniqueId = true;
        return options;
    }());
    // Add model to dbcontext
    _dbContext->addTournament(tournament);
    // Persist state change
    modelDBContext()->saveState();
    // Return model id
    return tournament->id();
}


bool LocalTournamentModelsContext::removeTournament(const QUuid &tournament)
{
    /*
     * TODO: Remove all models related to the tournament
     */
    removeTournamentScores(tournament);
    removeTournamentModel(tournament);
    return true;
}

bool LocalTournamentModelsContext::removeTournamentsFromIndexes(const QVector<int> &indexes)
{
    QVector<QUuid> tournamentIds;
    for (auto index : indexes)
        tournamentIds << tournamentIdFromIndex(index);
    for (auto tournamentId : tournamentIds)
        removeTournament(tournamentId);
    return true;
}


QUuid LocalTournamentModelsContext::tournamentIdFromIndex(const int &index)
{
    try {
        auto model = modelDBContext()->tournamentModel(index);
        auto tournament = dynamic_cast<const LMC::TournamentInterface*>(model);
        auto id = tournament->id();
        return id;

    }  catch (...) {
        throw "TOURNAMENT_NOT_FOUND";
    }
}

QVector<QUuid> LocalTournamentModelsContext::tournaments()
{
    QVector<QUuid> resultingList;
    auto tournaments = modelDBContext()->tournaments();
    for (auto tournament : tournaments)
    {
        auto id = tournament->id();
        resultingList << id;
    }

    return resultingList;
}

int LocalTournamentModelsContext::tournamentsCount()
{
    auto tournaments = modelDBContext()->tournaments();
    auto count = tournaments.count();
    return count;
}

QString LocalTournamentModelsContext::tournamentTitle(const QUuid &tournament)
{
    return getTournamentModelFromID<LMC::TournamentInterface>(tournament)->title();
}

int LocalTournamentModelsContext::tournamentAttempts(const QUuid &tournament)
{
    auto model = getTournamentModelFromID<LMC::FTPInterface>(tournament);
    auto numberOfThrows = model->attempts();
    return numberOfThrows;
}

QVector<QUuid> LocalTournamentModelsContext::tournamentAssignedPlayers(const QUuid &tournament)
{
    QVector<QUuid> assignedPlayers;
    try {
        auto tournamentModel = getTournamentModelFromID<LMC::TournamentInterface>(tournament);
        assignedPlayers = tournamentModel->assignedPlayerIdentities();
    } catch (const char *msg) {
        throw  msg;
    }
    return assignedPlayers;
}


int LocalTournamentModelsContext::tournamentGameMode(const QUuid &tournament)
{
    return getTournamentModelFromID<LMC::TournamentInterface>(tournament)->gameMode();
}

int LocalTournamentModelsContext::tournamentLastThrowKeyCode(const QUuid &tournament)
{
    auto tournamentModel = getTournamentModelFromID<LMC::FTPInterface>(tournament);
    auto conditionKeyCode = tournamentModel->terminalKeyCode();
    return conditionKeyCode;
}

int LocalTournamentModelsContext::tournamentKeyPoint(const QUuid &tournament)
{
    auto tournamentModel = getTournamentModelFromID<LMC::FTPInterface>(tournament);
    auto keyPoint = tournamentModel->keyPoint();
    return keyPoint;
}

int LocalTournamentModelsContext::tournamentTableViewHint(const QUuid &tournament)
{
    auto tournamentModel = getTournamentModelFromID<LMC::FTPInterface>(tournament);
    auto hint = tournamentModel->displayHint();
    return hint;
}

int LocalTournamentModelsContext::tournamentInputMode(const QUuid &tournament)
{
    auto tournamentModel = getTournamentModelFromID<LMC::FTPInterface>(tournament);
    auto inputMode = tournamentModel->inputHint();
    return inputMode;
}

int LocalTournamentModelsContext::tournamentStatus(const QUuid &tournament)
{
    auto model = getTournamentModelFromID<LMC::TournamentInterface>(tournament);
    auto status = model->status();
    return status;
}

QUuid LocalTournamentModelsContext::tournamentDeterminedWinner(const QUuid &tournament)
{
    auto tournamentModel = getTournamentModelFromID<LMC::TournamentInterface>(tournament);
    return tournamentModel->winnerId();
}

void LocalTournamentModelsContext::setTournamentDeterminedWinner(const QUuid &tournament,
                                                                 const QUuid &winner)
{
    auto oldModel = getTournamentModelFromID<LMC::TournamentInterface>(tournament);
    LMC::TournamentInterface* newModel = nullptr;
    auto gameMode = tournamentGameMode(tournament);
    if(gameMode == GameModes::FirstToPost)
    {
        newModel = tournamentBuilder()->editFTPTournament(
                    oldModel,
                    [winner,oldModel]
                    {
                        TBC::FTPParameters params;
                        params.gameMode = oldModel->gameMode();
                        params.winner = winner;
                        return params;
                    }(),[]
                    {
                        TBC::ModelOptions options;
                        options.generateUniqueId = false;
                        return options;
                    }());
    }
    auto index = modelDBContext()->indexOfTournament(oldModel);
    modelDBContext()->replaceTournament(index,newModel);
}

void LocalTournamentModelsContext::assignPlayerToTournament(const QUuid &tournament, const QUuid &player)
{
    auto oldModel = getTournamentModelFromID<LMC::TournamentInterface>(tournament);
    auto assignedPlayers = oldModel->assignedPlayerIdentities();
    assignedPlayers.append(player);
    auto newModel = tournamentBuilder()->editFTPTournament(oldModel,
                [assignedPlayers,oldModel]
    {
        TBC::FTPParameters params;
        params.gameMode = oldModel->gameMode();
        params.playerIdentities = assignedPlayers;
        return params;
    }(),[]
    {
        TBC::ModelOptions options;
        options.generateUniqueId = false;
        return options;
    }());
    auto index = modelDBContext()->indexOfTournament(oldModel);
    modelDBContext()->replaceTournament(index,newModel);
}

void LocalTournamentModelsContext::tournamentRemovePlayer(const QUuid &tournament, const QUuid &player)
{
    auto oldModel = getTournamentModelFromID<LMC::TournamentInterface>(tournament);
    auto assignedPlayers = oldModel->assignedPlayerIdentities();
    assignedPlayers.removeOne(player);
    auto newModel = tournamentBuilder()->editFTPTournament(oldModel,
                [assignedPlayers,oldModel]
    {
        TBC::FTPParameters params;
        params.gameMode = oldModel->gameMode();
        params.playerIdentities = assignedPlayers;
        return params;
    }(),[]
    {
        TBC::ModelOptions options;
        options.generateUniqueId = false;
        return options;
    }());
    auto index = modelDBContext()->indexOfTournament(oldModel);
    modelDBContext()->replaceTournament(index,newModel);
}

QList<QUuid> LocalTournamentModelsContext::scores()
{
    QList<QUuid> resultingList;
    auto scores = modelDBContext()->scoreModels();
    for (auto scoreModel : scores) {
        auto scoreID = scoreModel->id();
        resultingList << scoreID;
    }
    return resultingList;
}

QList<QUuid> LocalTournamentModelsContext::scores(const QUuid &tournament)
{
    QList<QUuid> resultingList;
    auto scores = modelDBContext()->scoreModels();
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
        if(oldModel->gameMode() == GameModes::FirstToPost)
        {
            auto newModel = scoreBuilder()->buildFTPScoreModel([oldModel,hint]{
                SBC::FTPScoreParameters params;
                params.id = oldModel->id();
                params.tournament = oldModel->parent();
                params.pointValue = oldModel->point();
                params.roundIndex = oldModel->roundIndex();
                params.setIndex = oldModel->setIndex();
                params.attempt = oldModel->attempt();
                params.playerId = oldModel->player();
                params.scoreValue = oldModel->score();
                params.hint = hint;
                return params;
            }(),[]{
                SBC::ModelOptions options;
                options.generateUniqueId = false;
                return options;
            }());
            auto index = modelDBContext()->indexOfScoreModel(oldModel);
            modelDBContext()->replaceScoreModel(index,newModel);
            return newModel->id();
        }

    } catch (const char msg) {
        throw msg;
    }
    return QUuid();
}

QUuid LocalTournamentModelsContext::editScore(const QUuid &pointId,
                                              const int &value,
                                              const int &score,
                                              const int &hint)
{
    try {
        auto oldScoreModel = getScoreModelFromID(pointId);
        if(oldScoreModel->gameMode() == GameModes::FirstToPost)
        {
            auto newScoreModel = scoreBuilder()->buildFTPScoreModel(
                        [oldScoreModel, score, value,hint]
            {
                SBC::FTPScoreParameters params;
                params.id = oldScoreModel->id();
                params.roundIndex = oldScoreModel->roundIndex();
                params.setIndex = oldScoreModel->setIndex();
                params.pointValue = value;
                params.playerId = oldScoreModel->player();
                params.attempt = oldScoreModel->attempt();
                params.scoreValue = score;
                params.hint = hint;
                return params;
            }(),[]
            {
                SBC::ModelOptions options;
                options.generateUniqueId = false;
                return options;
            }());
            auto index = modelDBContext()->indexOfScoreModel(oldScoreModel);
            modelDBContext()->replaceScoreModel(index,newScoreModel);
            return newScoreModel->id();
        }
    }  catch (const char msg) {
        throw msg;
    }
    return QUuid();
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


int LocalTournamentModelsContext::scoreAttemptIndex(const QUuid &point)
{
    try {
        auto scoreModel = getScoreModelFromID(point);
        auto throwIndex = scoreModel->attempt();
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
    auto models = modelDBContext()->scoreModels();
    for (auto model : models) {
        auto scoreModel = dynamic_cast<const LMC::ScoreInterface*>(model);
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
            auto index = modelDBContext()->indexOfScoreModel(scoreModel);
            modelDBContext()->removeScoreModel(index);
        }
    }
}

QList<QUuid> LocalTournamentModelsContext::playerScores(const QUuid &tournament, const QUuid &player, const int &hint)
{
    QList<QUuid> resultingList;
    auto scoreModelIds = scores(tournament);
    for (auto pointID : scoreModelIds) {
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
        auto index = modelDBContext()->indexOfScoreModel(scoreModel);
        modelDBContext()->removeScoreModel(index);
    }  catch (...) {
        return false;
    }
    return true;
}

void LocalTournamentModelsContext::removePlayerScore(const QUuid &point)
{
    try {
        auto scoreModel = getScoreModelFromID(point);
        auto index = modelDBContext()->indexOfScoreModel(scoreModel);
        modelDBContext()->removeScoreModel(index);
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
        auto leg = scoreAttemptIndex(scoreModelID);
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
template<typename TModelInterface>
const TModelInterface *LocalTournamentModelsContext::getTournamentModelFromID(const QUuid &id)
{
    auto models = modelDBContext()->tournaments();
    for (auto model : models) {
        if(model->id() == id)
            return dynamic_cast<const TModelInterface*>(model);
    }

    throw THROW_OBJECT_WITH_ID_NOT_FOUND(id.toString());
}

const IScore<QUuid> *LocalTournamentModelsContext::getScoreModelFromID(const QUuid &id)
{
    auto models = modelDBContext()->scoreModels();
    for (auto model : models)
    {
        if(model->id() == id)
            return dynamic_cast<const LMC::ScoreInterface*>(model);
    }

    throw THROW_OBJECT_WITH_ID_NOT_FOUND(id.toString());
}

void LocalTournamentModelsContext::removeTournamentModel(const QUuid &tournament)
{
    auto models = modelDBContext()->tournaments();
    for (auto model : models) {
        auto id = model->id();
        if(id == tournament)
        {
            auto index = modelDBContext()->indexOfTournament(model);
            modelDBContext()->removeTournamentModel(index);
            return;
        }
    }
}

void LocalTournamentModelsContext::removePointModel(const QUuid &point)
{
    auto models = modelDBContext()->scoreModels();
    for (auto model : models) {
        auto id = model->id();
        if(id == point)
        {
            auto index = modelDBContext()->indexOfScoreModel(model);
            modelDBContext()->removeScoreModel(index);
            return;
        }
    }
}

const QVector<int> LocalTournamentModelsContext::indexes(const QUuid &tournament)
{
    auto totalTurns = 0;
    auto turnIndex = 0;
    auto roundIndex = 1;
    auto setIndex = 0;
    auto throwIndex = 0;
    auto assignedPlayersID = tournamentAssignedPlayers(tournament);
    auto playersCount = assignedPlayersID.count();
    auto numberOfThrows= tournamentAttempts(tournament);
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

    QVector<int> indexes = {
        totalTurns,
        turnIndex,
        roundIndex,
        setIndex,
        throwIndex
    };
    return indexes;
}

QVector<int> LocalTournamentModelsContext::tournamentUserScores(const QUuid &tournament)
{
    QVector<int> userScores;
    auto assignedPlayersID = tournamentAssignedPlayers(tournament);
    for (auto playerID : assignedPlayersID) {
        auto s = score(tournament,playerID);
        userScores << s;
    }
    return userScores;
}

LocalTournamentModelsContext *LocalTournamentModelsContext::setModelDBContext(ImodelsDBContext *context)
{
    _dbContext = context;
    return this;
}

ImodelsDBContext *LocalTournamentModelsContext::modelDBContext()
{
    return _dbContext;
}

int LocalTournamentModelsContext::playerScoreCount(const int &hint)
{
    auto count = 0;
    auto models = modelDBContext()->scoreModels();
    for (auto model : models) {
        auto scoreModel = dynamic_cast<const LMC::ScoreInterface*>(model);
        if(scoreModel->hint() == hint || hint == allHints)
            count++;
    }
    return count;
}

void LocalTournamentModelsContext::addFTPScore(const QUuid &tournament,
                                            const QUuid &player,
                                            const QVector<int> &dataValues,
                                            const bool &isWinnerDetermined)
{
    /*
     * dataValues memory layout:
     *  - [0] = Round index
     *  - [1] = Set/player index
     *  - [2] = throwindex
     *  - [3] = point value
     *  - [4} = score value
     *  - [5] = keycode
     */
    scoreBuilder()->buildFTPScoreModel([this,tournament,player,dataValues]
    {
        SBC::FTPScoreParameters params;
        params.roundIndex = dataValues[0];
        params.setIndex = dataValues[1];
        params.attempt = dataValues[2];
        params.pointValue = dataValues[3];
        params.scoreValue = dataValues[4];
        params.keyCode = dataValues[5];
        params.tournament = tournament;
        params.playerId = player;
        params.gameMode = tournamentGameMode(tournament);
        return params;
    }(),
    []
    {
        SBC::ModelOptions options;
        options.generateUniqueId = true;
        return options;
    }());

    if(isWinnerDetermined)
        setTournamentDeterminedWinner(tournament,player);
    removeHiddenScores(tournament);
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

