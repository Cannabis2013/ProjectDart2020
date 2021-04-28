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

LocalTournamentModelsContext *LocalTournamentModelsContext::setTournamentBuilder(TCC::ITournamentModelsBuilder *builder)
{
    _tournamentModelBuilder = builder;
    return this;
}

TCC::ITournamentModelsBuilder *LocalTournamentModelsContext::tournamentBuilder()
{
    return _tournamentModelBuilder;
}

LocalTournamentModelsContext *LocalTournamentModelsContext::setScoreBuilder(TCC::ScoreBuilderInterface *builder)
{
    _scoreModelbuilder = builder;
    return this;
}

TCC::ScoreBuilderInterface *LocalTournamentModelsContext::scoreBuilder()
{
    return _scoreModelbuilder;
}

QUuid LocalTournamentModelsContext::tournamentAssembleAndAddFTP(const QString &title,
                                                                const int& gameMode,
                                                                const int& keyPoint,
                                                                const int& terminalKeyCode,
                                                                const int& displayHint,
                                                                const int& inputHint,
                                                                const int& attempts,
                                                                const QVector<QUuid>& playerIds)
{
    // Build model
    TBC::FTPParameters params;
    params.title = title;
    params.gameMode = gameMode;
    params.keyPoint = keyPoint;
    params.terminalKeyCode = terminalKeyCode;
    params.displayHint = displayHint;
    params.inputHint = inputHint;
    params.attempts = attempts;
    params.playerIdentities = playerIds;
    params.tournamentsCount = this->tournamentsCount();
    TBC::ModelOptions options;
    options.generateUniqueId = true;

    auto tournament = tournamentBuilder()->buildFTPTournament(params,options);
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
        auto model = modelDBContext()->dartsTournamentModelFromIndex(index);
        auto tournament = dynamic_cast<const TCC::TournamentInterface*>(model);
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
    return getTournamentModelFromID<TCC::TournamentInterface>(tournament)->title();
}

int LocalTournamentModelsContext::tournamentAttempts(const QUuid &tournament)
{
    auto model = getTournamentModelFromID<TCC::FTPInterface>(tournament);
    auto numberOfThrows = model->attempts();
    return numberOfThrows;
}

QVector<QUuid> LocalTournamentModelsContext::tournamentAssignedPlayers(const QUuid &tournament)
{
    QVector<QUuid> assignedPlayers;
    const TCC::TournamentInterface* tournamentModel;
    try {
        tournamentModel = getTournamentModelFromID<TCC::TournamentInterface>(tournament);
    } catch (const char *msg) {
        throw  msg;
    }
    assignedPlayers = tournamentModel->assignedPlayerIdentities();
    return assignedPlayers;
}


int LocalTournamentModelsContext::tournamentGameMode(const QUuid &tournament)
{
    return getTournamentModelFromID<TCC::TournamentInterface>(tournament)->gameMode();
}

int LocalTournamentModelsContext::tournamentTerminalKeyCode(const QUuid &tournament)
{
    auto tournamentModel = getTournamentModelFromID<TCC::FTPInterface>(tournament);
    auto conditionKeyCode = tournamentModel->terminalKeyCode();
    return conditionKeyCode;
}

int LocalTournamentModelsContext::tournamentKeyPoint(const QUuid &tournament)
{
    auto tournamentModel = getTournamentModelFromID<TCC::FTPInterface>(tournament);
    auto keyPoint = tournamentModel->keyPoint();
    return keyPoint;
}

int LocalTournamentModelsContext::tournamentTableViewHint(const QUuid &tournament)
{
    auto tournamentModel = getTournamentModelFromID<TCC::FTPInterface>(tournament);
    auto hint = tournamentModel->displayHint();
    return hint;
}

int LocalTournamentModelsContext::tournamentInputMode(const QUuid &tournament)
{
    auto tournamentModel = getTournamentModelFromID<TCC::FTPInterface>(tournament);
    auto inputMode = tournamentModel->inputHint();
    return inputMode;
}

int LocalTournamentModelsContext::tournamentStatus(const QUuid &tournament)
{
    auto model = getTournamentModelFromID<TCC::TournamentInterface>(tournament);
    auto status = model->status();
    return status;
}

QUuid LocalTournamentModelsContext::tournamentWinner(const QUuid &tournament)
{
    auto tournamentModel = getTournamentModelFromID<TCC::TournamentInterface>(tournament);
    return tournamentModel->winnerId();
}

void LocalTournamentModelsContext::tournamentSetWinnerId(const QUuid &tournament,
                                                                 const QUuid &winner)
{
    auto oldModel = getTournamentModelFromID<TCC::TournamentInterface>(tournament);
    TCC::TournamentInterface* newModel = nullptr;
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
                        options.useProvidedId = true;
                        return options;
                    }());
    }
    auto index = modelDBContext()->indexOfTournament(oldModel);
    modelDBContext()->replaceTournament(index,newModel);
}

void LocalTournamentModelsContext::tournamentAssignPlayer(const QUuid &tournament, const QUuid &player)
{
    auto oldModel = getTournamentModelFromID<TCC::TournamentInterface>(tournament);
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

void LocalTournamentModelsContext::tournamentUnAssignPlayer(const QUuid &tournament, const QUuid &player)
{
    auto oldModel = getTournamentModelFromID<TCC::TournamentInterface>(tournament);
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

QList<QUuid> LocalTournamentModelsContext::ftpScoreIds()
{
    QList<QUuid> resultingList;
    auto scores = modelDBContext()->dartsPointModels();
    for (auto scoreModel : scores) {
        auto scoreID = scoreModel->id();
        resultingList << scoreID;
    }
    return resultingList;
}

QList<QUuid> LocalTournamentModelsContext::ftpScoreIds(const QUuid &tournament)
{
    QList<QUuid> resultingList;
    auto scores = modelDBContext()->dartsPointModels();
    for (auto scoreModel : scores) {
        auto compareTournamentID = scoreModel->parent();
        if(compareTournamentID == tournament)
            resultingList << scoreModel->id();
    }

    return resultingList;
}

QList<QUuid> LocalTournamentModelsContext::ftpScoreIds(const QUuid &tournament,
                                                     const int &round)
{
    QList<QUuid> resultingList;
    auto ftpScoreIds = this->ftpScoreIds(tournament);
    for (auto pointID : ftpScoreIds) {
        auto ftpScore = this->getScoreModelFromId<IDartsPointInput<QUuid>>(pointID);
        auto roundIndex = ftpScore->roundIndex();
        if(roundIndex == round)
            resultingList << pointID;
    }
    return resultingList;
}

QList<QUuid> LocalTournamentModelsContext::ftpScoreIds(const QUuid &tournament,
                                                  const int &round,
                                                  const int &set)
{
    QList<QUuid> resultingList;
    auto p = this->ftpScoreIds(tournament,round);
    for (auto scoreModelID : p) {
        auto ftpScore = getScoreModelFromId<IDartsPointInput<QUuid>>(scoreModelID);
        auto setIndex = ftpScore->setIndex();
        if(setIndex == set)
            resultingList << scoreModelID;
    }

    return resultingList;
}

QList<QUuid> LocalTournamentModelsContext::ftpScoreIds(const int &hint, const QUuid &tournament)
{
    QList<QUuid> resultingList;
    auto modelIds = this->ftpScoreIds(tournament);
    for (auto modelId : modelIds) {
        auto ftpScoreModel = getScoreModelFromId<IPlayerInput<QUuid>>(modelId);
        auto scoreModelHint = ftpScoreModel->hint();
        if(scoreModelHint == hint)
            resultingList << modelId;
    }
    return resultingList;
}

QUuid LocalTournamentModelsContext::setDartsPointHint(const QUuid &point,
                                                 const int &hint)
{
    auto oldFtpScoreModel = getScoreModelFromId<IDartsPointInput<QUuid>>(point);
    SBC::DartsPointParameters params;
    params.id = oldFtpScoreModel->id();
    params.tournament = oldFtpScoreModel->parent();
    params.pointValue = oldFtpScoreModel->point();
    params.roundIndex = oldFtpScoreModel->roundIndex();
    params.setIndex = oldFtpScoreModel->setIndex();
    params.attempt = oldFtpScoreModel->attempt();
    params.playerId = oldFtpScoreModel->player();
    params.scoreValue = oldFtpScoreModel->score();
    params.hint = hint;
    SBC::ModelOptions options;
    options.generateUniqueId = false;
    auto index = modelDBContext()->indexOfScoreModel(oldFtpScoreModel);
    auto newModel = scoreBuilder()->buildDartsPoint(params,options);
    auto newFtpScoreModel = dynamic_cast<const IDartsPointInput<QUuid>*>(newModel);
    modelDBContext()->replaceScoreModel(index,newFtpScoreModel);
    return newModel->id();
}

QUuid LocalTournamentModelsContext::editScore(const QUuid &pointId,
                                              const int &value,
                                              const int &score,
                                              const int &hint)
{
    try {
        auto oldFtpScoreModel = getScoreModelFromId<IDartsPointInput<QUuid>>(pointId);
        auto tournamentId = oldFtpScoreModel->parent();
        auto gameMode = tournamentGameMode(tournamentId);
        if(gameMode == GameModes::FirstToPost)
        {
            SBC::DartsPointParameters params;
            params.id = oldFtpScoreModel->id();
            params.roundIndex = oldFtpScoreModel->roundIndex();
            params.setIndex = oldFtpScoreModel->setIndex();
            params.pointValue = value;
            params.playerId = oldFtpScoreModel->player();
            params.attempt = oldFtpScoreModel->attempt();
            params.scoreValue = score;
            params.accumulatedScoreValue = oldFtpScoreModel->accumulatedScore();
            params.hint = hint;
            SBC::ModelOptions options;
            options.generateUniqueId = false;
            auto newScoreModel = scoreBuilder()->buildDartsPoint(params,options);
            auto index = modelDBContext()->indexOfScoreModel(oldFtpScoreModel);
            auto newFtpScoreModel = dynamic_cast<const IDartsPointInput<QUuid>*>(newScoreModel);
            modelDBContext()->replaceScoreModel(index,newFtpScoreModel);
            return newScoreModel->id();
        }
    }  catch (const char msg) {
        throw msg;
    }
    return QUuid();
}

int LocalTournamentModelsContext::ftpScoreRoundIndex(const QUuid &playerScore)
{
    auto ftpScoreModel = getScoreModelFromId<IDartsPointInput<QUuid>>(playerScore);
    auto roundIndex = ftpScoreModel->roundIndex();
    return roundIndex;
}

int LocalTournamentModelsContext::ftpScoreSetIndex(const QUuid &playerScore)
{
    auto ftpScoreModel = getScoreModelFromId<IDartsPointInput<QUuid>>(playerScore);
    auto setIndex = ftpScoreModel->setIndex();
    return setIndex;
}


int LocalTournamentModelsContext::ftpScoreAttemptIndex(const QUuid &point)
{
    try {
        auto ftpScoreModel = getScoreModelFromId<IDartsPointInput<QUuid>>(point);
        auto throwIndex = ftpScoreModel->attempt();
        return throwIndex;
    } catch (const char *msg) {
        throw msg;
    }
}
int LocalTournamentModelsContext::ftpScorePointValue(const QUuid &point)
{
    try {
        auto ftpScoreModel = getScoreModelFromId<IDartsPointInput<QUuid>>(point);
        auto pointValue = ftpScoreModel->point();
        return pointValue;

    }  catch (const char *msg) {
        throw msg;
    }
}

int LocalTournamentModelsContext::ftpScoreValue(const QUuid &point)
{
    try {
        auto ftpScoreModel = getScoreModelFromId<IDartsPointInput<QUuid>>(point);
        auto score = ftpScoreModel->score();
        return score;
    }  catch (const char *msg) {
        throw msg;
    }
}

int LocalTournamentModelsContext::ftpAccumulatedScoreValue(const QUuid &point)
{
    try {
        auto ftpScoreModel = getScoreModelFromId<IDartsPointInput<QUuid>>(point);
        auto accumulatedScore = ftpScoreModel->accumulatedScore();
        return accumulatedScore;
    }  catch (const char *msg) {
        throw msg;
    }
}

QUuid LocalTournamentModelsContext::ftpScoreTournament(const QUuid &playerScore)
{
    auto model = getScoreModelFromId(playerScore);
    auto tournamentID = model->parent();
    return tournamentID;
}

QUuid LocalTournamentModelsContext::scorePlayer(const QUuid &point)
{
    auto ftpScoreModel = getScoreModelFromId<IPlayerInput<QUuid>>(point);
    auto playerID = ftpScoreModel->player();
    return playerID;
}

int LocalTournamentModelsContext::scoreHint(const QUuid &scoreID)
{
    try {
        auto scoreModel = getScoreModelFromId<IPlayerInput<QUuid>>(scoreID);
        auto hint = scoreModel->hint();
        return hint;
    } catch (const char *msg) {
        throw msg;
    }
}

int LocalTournamentModelsContext::scoreKeyCode(const QUuid &scoreID)
{
    try {
        auto ftpScoreModel = getScoreModelFromId<IPlayerInput<QUuid>>(scoreID);
        auto keyCode = ftpScoreModel->modKeyCode();
        return keyCode;
    } catch (const char *msg) {
        throw msg;
    }
}

QList<QUuid> LocalTournamentModelsContext::pointModels(const QUuid &player)
{
    QList<QUuid> resultingList;
    auto models = modelDBContext()->dartsPointModels();
    for (auto model : models) {
        auto scoreModel = dynamic_cast<const IPlayerInput<QUuid>*>(model);
        auto pointID = scoreModel->id();
        if(scoreModel->player() == player)
            resultingList << pointID;
    }
    return resultingList;
}

void LocalTournamentModelsContext::removeTournamentScores(const QUuid &tournament)
{
    auto scoresID = this->ftpScoreIds(tournament);
    for (auto scoreID : scoresID) {
        auto scoreModel = getScoreModelFromId(scoreID);
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
    auto scoreModelIds = ftpScoreIds(tournament);
    for (auto pointID : scoreModelIds) {
        auto model = getScoreModelFromId(pointID);
        auto scoreModel = dynamic_cast<const IPlayerInput<QUuid>*>(model);
        auto modelHint = scoreHint(pointID);
        if(modelHint != hint && hint != allHints)
            continue;
        auto pointPlayer = scoreModel->player();
        if(pointPlayer != player)
            continue;
        resultingList << pointID;
    }
    return resultingList;
}

bool LocalTournamentModelsContext::removeScore(const QUuid &point)
{
    try {
        auto scoreModel = getScoreModelFromId(point);
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
        auto scoreModel = getScoreModelFromId(point);
        auto index = modelDBContext()->indexOfScoreModel(scoreModel);
        modelDBContext()->removeScoreModel(index);
    } catch (const char *msg) {
        return;
    }
}

QUuid LocalTournamentModelsContext::ftpScore(const QUuid &tournament,
                                                const QUuid &player,
                                                const int &round,
                                                const int &throwIndex,
                                                const int &hint)
{
    auto tournamentScoreModels = ftpScoreIds(tournament);
    for (auto scoreModelID : tournamentScoreModels) {
        auto model = getScoreModelFromId(scoreModelID);
        auto scoreModel = dynamic_cast<const IDartsPointInput<QUuid>*>(model);
        auto modelHint = scoreModel->hint();
        auto playerID = scoreModel->player();
        auto leg = ftpScoreAttemptIndex(scoreModelID);
        auto roundIndex = scoreModel->roundIndex();
        if(playerID != player)
            continue;
        if(leg != throwIndex)
            continue;
        if(roundIndex != round)
            continue;
        if(hint != modelHint && hint != allHints)
            continue;
        return scoreModelID;
    }

    throw "Object not found";
}

QUuid LocalTournamentModelsContext::ftpScore(const QUuid &tournament,
                                                const QUuid &player,
                                                const int &round,
                                                const int &attemptIndex)
{
    auto tournamentScoreModels = ftpScoreIds(tournament);
    for (auto scoreModelID : tournamentScoreModels) {
        auto model = getScoreModelFromId(scoreModelID);
        auto scoreModel = dynamic_cast<const IDartsPointInput<QUuid>*>(model);
        auto playerID = scoreModel->player();
        if(playerID != player)
            continue;
        auto leg = ftpScoreAttemptIndex(scoreModelID);
        if(leg != attemptIndex)
            continue;
        auto roundIndex = scoreModel->roundIndex();
        if(roundIndex != round)
            continue;
        return scoreModelID;
    }
    return QUuid();
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
template<typename T>
const T *LocalTournamentModelsContext::getScoreModelFromId(const QUuid &id)
{
    auto models = modelDBContext()->dartsPointModels();
    for (auto model : models)
    {
        if(model->id() == id)
            return dynamic_cast<const T*>(model);
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
            modelDBContext()->removeDartsTournamentModelFromId(index);
            return;
        }
    }
}

void LocalTournamentModelsContext::removePointModel(const QUuid &point)
{
    auto models = modelDBContext()->dartsPointModels();
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
    auto attemptIndex = 0;
    auto assignedPlayersId = tournamentAssignedPlayers(tournament);
    auto playersCount = assignedPlayersId.count();
    auto numberOfAttempts = tournamentAttempts(tournament);
    while(1)
    {
        auto playerId = assignedPlayersId.at(setIndex);
        try {
            ftpScore(tournament,
                        playerId,
                        roundIndex,
                        attemptIndex,
                        ModelDisplayHint::DisplayHint);
        } catch (...) {
            break;
        }
        if(++attemptIndex % numberOfAttempts == 0)
        {
            attemptIndex = 0;
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
        totalTurns = ftpScoresCount(ModelDisplayHint::allHints);

    QVector<int> indexes = {
        totalTurns,
        turnIndex,
        roundIndex,
        setIndex,
        attemptIndex
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

LocalTournamentModelsContext *LocalTournamentModelsContext::setModelDBContext(IModelsDbContext *context)
{
    _dbContext = context;
    return this;
}

IModelsDbContext *LocalTournamentModelsContext::modelDBContext()
{
    return _dbContext;
}

int LocalTournamentModelsContext::ftpScoresCount(const int &hint)
{
    auto count = 0;
    auto models = modelDBContext()->dartsPointModels();
    for (auto model : models) {
        auto scoreModel = dynamic_cast<const IPlayerInput<QUuid>*>(model);
        if(scoreModel->hint() == hint || hint == allHints)
            count++;
    }
    return count;
}

void LocalTournamentModelsContext::addDartsPoint(const QUuid &tournament,
                                               const QUuid &player,
                                               const int &roundIndex,
                                               const int &setIndex,
                                               const int &attemptIndex,
                                               const int &point,
                                               const int &score,
                                               const int &keyCode,
                                               const bool &isWinnerDetermined)
{
    SBC::DartsPointParameters params;
    params.roundIndex = roundIndex;
    params.setIndex = setIndex;
    params.attempt = attemptIndex;
    params.pointValue = point;
    params.scoreValue = score;
    params.keyCode = keyCode;
    params.tournament = tournament;
    params.playerId = player;
    params.hint = ModelDisplayHint::DisplayHint;
    SBC::ModelOptions options;
    options.generateUniqueId = true;
    auto model = scoreBuilder()->buildDartsPoint(params,options);
    if(isWinnerDetermined)
        tournamentSetWinnerId(tournament,player);
    removeHiddenScores(tournament);
    modelDBContext()->addScoreModel(model);
}

void LocalTournamentModelsContext::removeHiddenScores(const QUuid &tournament)
{
    auto scoresID = ftpScoreIds(ModelDisplayHint::HiddenHint,tournament);
    for (auto scoreID : scoresID)
        removeScore(scoreID);
}

int LocalTournamentModelsContext::score(const QUuid &tournament, const QUuid &player)
{
    int totalScore = tournamentKeyPoint(tournament);
    auto playerScoresID = playerScores(tournament,player,ModelDisplayHint::DisplayHint);
    for (auto scoreID : playerScoresID) {
        auto point = ftpScorePointValue(scoreID);
        totalScore -= point;
    }
    return totalScore;
}

int LocalTournamentModelsContext::score(const QUuid &player)
{
    Q_UNUSED(player);
    return -1;
}

