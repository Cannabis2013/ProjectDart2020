#include "dartsmodelsservice.h"

DartsModelsService *DartsModelsService::createInstance()
{
    return new DartsModelsService();
}

DartsModelsService* DartsModelsService::setup()
{
    return this;
}

const IDartsTournament *DartsModelsService::getDartsTournamentModelById(const QUuid &tournamentId) const
{
    auto model = getTournamentModelFromId(tournamentId);
    return model;
}

QUuid DartsModelsService::addDartsTournamentToDb(const IDartsTournament* tournament)
{
    // Add model to dbcontext
    _tournamentsDbContext->addTournament(tournament);
    // Return model id
    return tournament->id();
}

bool DartsModelsService::removeTournamentsByIndexes(const QVector<int> &indexes) const
{
    auto orderedList = indexes;
    // Order list to ensure that elements that corresponds to an index in list gets deleted
    std::sort(orderedList.begin(),orderedList.end());
    for (auto i = orderedList.count() - 1; i >= 0; --i)
        _tournamentsDbContext->removeDartsTournamentModelByIndex(i);
    return true;
}


QUuid DartsModelsService::tournamentIdFromIndex(const int &index) const
{
    try {
        auto model = _tournamentsDbContext->dartsTournamentModelFromIndex(index);
        auto tournament = dynamic_cast<const IDartsTournament*>(model);
        auto id = tournament->id();
        return id;
    }  catch (...) {
        throw "TOURNAMENT_NOT_FOUND";
    }
}

QVector<QUuid> DartsModelsService::tournaments() const
{
    QVector<QUuid> resultingList;
    auto tournaments = _tournamentsDbContext->dartsTournaments();
    for (auto tournament : tournaments)
    {
        auto id = tournament->id();
        resultingList << id;
    }

    return resultingList;
}

int DartsModelsService::tournamentsCount() const
{
    auto tournaments = _tournamentsDbContext->dartsTournaments();
    auto count = tournaments.count();
    return count;
}

QString DartsModelsService::tournamentTitle(const QUuid &tournament) const
{
    return getTournamentModelFromId(tournament)->title();
}

int DartsModelsService::tournamentAttempts(const QUuid &tournament) const
{
    auto model = getTournamentModelFromId(tournament);
    auto numberOfThrows = model->attempts();
    return numberOfThrows;
}

QVector<QUuid> DartsModelsService::tournamentAssignedPlayers(const QUuid &tournament) const
{
    QVector<QUuid> assignedPlayers;
    const IDartsTournament* tournamentModel;
    try {
        tournamentModel = getTournamentModelFromId(tournament);
    } catch (const char *msg) {
        throw  msg;
    }
    assignedPlayers = tournamentModel->assignedPlayerIdentities();
    return assignedPlayers;
}


int DartsModelsService::tournamentGameMode(const QUuid &tournament) const
{
    return getTournamentModelFromId(tournament)->gameMode();
}

int DartsModelsService::tournamentTerminalKeyCode(const QUuid &tournament) const
{
    auto tournamentModel = getTournamentModelFromId(tournament);
    auto conditionKeyCode = tournamentModel->terminalKeyCode();
    return conditionKeyCode;
}

int DartsModelsService::tournamentKeyPoint(const QUuid &tournament) const
{
    auto tournamentModel = getTournamentModelFromId(tournament);
    auto keyPoint = tournamentModel->keyPoint();
    return keyPoint;
}

int DartsModelsService::tournamentTableViewHint(const QUuid &tournament) const
{
    auto tournamentModel = getTournamentModelFromId(tournament);
    auto hint = tournamentModel->displayHint();
    return hint;
}

int DartsModelsService::tournamentInputMode(const QUuid &tournament) const
{
    auto tournamentModel = getTournamentModelFromId(tournament);
    auto inputMode = tournamentModel->inputHint();
    return inputMode;
}

int DartsModelsService::tournamentStatus(const QUuid &tournament) const
{
    auto model = getTournamentModelFromId(tournament);
    auto status = model->status();
    return status;
}

QUuid DartsModelsService::tournamentWinnerId(const QUuid &tournament) const
{
    auto tournamentModel = getTournamentModelFromId(tournament);
    return tournamentModel->winnerId();
}

void DartsModelsService::tournamentSetWinnerId(const QUuid &tournament,
                                               const QUuid &winner)
{
    auto oldModel = getTournamentModelFromId(tournament);
    auto newModel = const_cast<IDartsTournament*>(oldModel);
    newModel->setWinnerId(winner);
    auto index = _tournamentsDbContext->indexOfTournament(oldModel);
    _tournamentsDbContext->replaceTournament(index,newModel);
}

void DartsModelsService::tournamentAssignPlayer(const QUuid &tournament, const QUuid &player)
{
    auto oldModel = getTournamentModelFromId(tournament);
    auto assignedPlayers = oldModel->assignedPlayerIdentities();
    assignedPlayers.append(player);
    auto newModel = const_cast<IDartsTournament*>(oldModel);
    newModel->setAssignedPlayerIdentities(assignedPlayers);
    auto index = _tournamentsDbContext->indexOfTournament(oldModel);
    _tournamentsDbContext->replaceTournament(index,newModel);
}

void DartsModelsService::tournamentAssignPlayers(const QUuid &tournament,
                                                 const QVector<QUuid> &playersIds)
{
    auto oldModel = getTournamentModelFromId(tournament);
    auto newModel = const_cast<IDartsTournament*>(oldModel);
    auto assignedPlayers = newModel->assignedPlayerIdentities();
    assignedPlayers.append(playersIds);
    newModel->setAssignedPlayerIdentities(assignedPlayers);
    auto index = _tournamentsDbContext->indexOfTournament(oldModel);
    _tournamentsDbContext->replaceTournament(index,newModel);
}

void DartsModelsService::tournamentUnAssignPlayer(const QUuid &tournament, const QUuid &player)
{
    auto oldModel = getTournamentModelFromId(tournament);
    auto assignedPlayers = oldModel->assignedPlayerIdentities();
    assignedPlayers.removeOne(player);
    auto newModel = const_cast<IDartsTournament*>(oldModel);
    newModel->setAssignedPlayerIdentities(assignedPlayers);
    auto index = _tournamentsDbContext->indexOfTournament(oldModel);
    _tournamentsDbContext->replaceTournament(index,newModel);
}

QVector<QUuid> DartsModelsService::dartsPointIds() const
{
    QVector<QUuid> resultingList;
    auto scores = _dartsPointsDb->dartsInputModels();
    for (auto scoreModel : scores) {
        auto scoreID = scoreModel->id();
        resultingList << scoreID;
    }
    return resultingList;
}

QVector<QUuid> DartsModelsService::dartsPointIds(const QUuid &tournament) const
{
    QVector<QUuid> resultingList;
    auto scores = _dartsPointsDb->dartsInputModels();
    for (auto scoreModel : scores) {
        auto playerInput = dynamic_cast<const IPlayerInput<QUuid>*>(scoreModel);
        auto compareTournamentID = playerInput->tournamentId();
        if(compareTournamentID == tournament)
            resultingList << scoreModel->id();
    }

    return resultingList;
}

QVector<QUuid> DartsModelsService::dartsPointIds(const QUuid &tournament,
                                                     const int &round) const
{
    QVector<QUuid> resultingList;
    auto ftpScoreIds = dartsPointIds(tournament);
    for (auto pointID : ftpScoreIds) {
        auto ftpScore = getPointModelById(pointID);
        auto roundIndex = ftpScore->roundIndex();
        if(roundIndex == round)
            resultingList << pointID;
    }
    return resultingList;
}

QVector<QUuid> DartsModelsService::dartsPointIds(const QUuid &tournament,
                                                  const int &round,
                                                  const int &set)
{
    QVector<QUuid> resultingList;
    auto p = this->dartsPointIds(tournament,round);
    for (auto scoreModelID : p) {
        auto ftpScore = getPointModelById(scoreModelID);
        auto setIndex = ftpScore->setIndex();
        if(setIndex == set)
            resultingList << scoreModelID;
    }

    return resultingList;
}

QVector<QUuid> DartsModelsService::dartsPointIds(const int &hint, const QUuid &tournament)
{
    QVector<QUuid> resultingList;
    auto modelIds = this->dartsPointIds(tournament);
    for (auto modelId : modelIds) {
        auto ftpScoreModel = getPointModelById(modelId);
        auto scoreModelHint = ftpScoreModel->hint();
        if(scoreModelHint == hint)
            resultingList << modelId;
    }
    return resultingList;
}

const IDartsPointInput *DartsModelsService::setDartsPointHint(const QUuid &point,
                                                 const int &hint)
{
    auto model = getPointModelById(point);
    auto newModel = const_cast<IDartsPointInput*>(model);
    auto index = _dartsPointsDb->indexOfDartsInputModel(model);
    newModel->setHint(hint);
    _dartsPointsDb->replaceDartsInputModel(index,newModel);
    return newModel;
}

int DartsModelsService::dartsPointRoundIndex(const QUuid &playerScore) const
{
    auto ftpScoreModel = getPointModelById(playerScore);
    auto roundIndex = ftpScoreModel->roundIndex();
    return roundIndex;
}

int DartsModelsService::dartsPointSetIndex(const QUuid &playerScore) const
{
    auto ftpScoreModel = getPointModelById(playerScore);
    auto setIndex = ftpScoreModel->setIndex();
    return setIndex;
}


int DartsModelsService::dartsPointAttemptIndex(const QUuid &point) const
{
    try {
        auto ftpScoreModel = getPointModelById(point);
        auto throwIndex = ftpScoreModel->attempt();
        return throwIndex;
    } catch (const char *msg) {
        throw msg;
    }
}
int DartsModelsService::pointValueFromPointId(const QUuid &point) const
{
    try {
        auto ftpScoreModel = getPointModelById(point);
        auto pointValue = ftpScoreModel->point();
        return pointValue;

    }  catch (const char *msg) {
        throw msg;
    }
}

QUuid DartsModelsService::tournamentIdFromPointId(const QUuid &playerScore) const
{
    auto model = getPointModelById(playerScore);
    auto tournamentID = model->tournamentId();
    return tournamentID;
}

QUuid DartsModelsService::playerIdFromPointId(const QUuid &point) const
{
    auto ftpScoreModel = getPointModelById(point);
    auto playerID = ftpScoreModel->playerId();
    return playerID;
}

int DartsModelsService::pointHint(const QUuid &scoreID) const
{
    try {
        auto scoreModel = getPointModelById(scoreID);
        auto hint = scoreModel->hint();
        return hint;
    } catch (const char *msg) {
        throw msg;
    }
}

int DartsModelsService::pointKeyCode(const QUuid &scoreID) const
{
    try {
        auto ftpScoreModel = getPointModelById(scoreID);
        auto keyCode = ftpScoreModel->modKeyCode();
        return keyCode;
    } catch (const char *msg) {
        throw msg;
    }
}

QVector<QUuid> DartsModelsService::pointModels(const QUuid &player)
{
    QVector<QUuid> resultingList;
    auto models = _dartsPointsDb->dartsInputModels();
    for (auto model : models) {
        auto scoreModel = dynamic_cast<const IPlayerInput<QUuid>*>(model);
        auto pointID = scoreModel->id();
        if(scoreModel->playerId() == player)
            resultingList << pointID;
    }
    return resultingList;
}

void DartsModelsService::removePointsByTournamentId(const QUuid &tournament)
{
    auto scoresID = this->dartsPointIds(tournament);
    for (auto scoreID : scoresID) {
        auto scoreModel = getPointModelById(scoreID);
        auto tournamentID = scoreModel->tournamentId();
        if(tournamentID == tournament)
        {
            auto index = _dartsPointsDb->indexOfDartsInputModel(scoreModel);
            _dartsPointsDb->removeDartsInputModelByIndex(index);
        }
    }
}

QVector<QUuid> DartsModelsService::pointsByPlayerId(const QUuid &tournament, const QUuid &player, const int &hint) const
{
    QVector<QUuid> resultingList;
    auto scoreModelIds = dartsPointIds(tournament);
    for (auto pointID : scoreModelIds) {
        auto model = getPointModelById(pointID);
        auto pointModel = dynamic_cast<const IPlayerInput<QUuid>*>(model);
        auto modelHint = pointHint(pointID);
        if(modelHint != hint && hint != allHints)
            continue;
        auto pointPlayer = pointModel->playerId();
        if(pointPlayer != player)
            continue;
        resultingList << pointID;
    }
    return resultingList;
}

void DartsModelsService::removePointById(const QUuid &point)
{
    try {
        auto scoreModel = getPointModelById(point);
        auto index = _dartsPointsDb->indexOfDartsInputModel(scoreModel);
        _dartsPointsDb->removeDartsInputModelByIndex(index);
    } catch (const char *msg) {
        return;
    }
}

QUuid DartsModelsService::getDartsPointId(const QUuid &tournament,
                                                const QUuid &player,
                                                const int &round,
                                                const int &attemptIndex,
                                                const int &hint) const
{
    auto tournamentScoreModels = dartsPointIds(tournament);
    for (auto pointModelId : tournamentScoreModels) {
        auto pointModel = getPointModelById(pointModelId);
        auto modelHint = pointModel->hint();
        auto playerId = pointModel->playerId();
        auto attempt = dartsPointAttemptIndex(pointModelId);
        auto roundIndex = pointModel->roundIndex();
        if(playerId != player)
            continue;
        if(attempt != attemptIndex)
            continue;
        if(roundIndex != round)
            continue;
        if(hint != modelHint && hint != allHints)
            continue;
        return pointModelId;
    }
    throw "Object not found";
}

QUuid DartsModelsService::getDartsPointId(const QUuid &tournament,
                                   const QUuid &player,
                                   const int &round,
                                   const int &attemptIndex) const
{
    auto pointIds = dartsPointIds(tournament);
    for (auto pointId : pointIds) {
        auto model = getPointModelById(pointId);
        auto scoreModel = dynamic_cast<const IDartsPointInput*>(model);
        auto playerID = scoreModel->playerId();
        if(playerID != player)
            continue;
        auto leg = dartsPointAttemptIndex(pointId);
        if(leg != attemptIndex)
            continue;
        auto roundIndex = scoreModel->roundIndex();
        if(roundIndex != round)
            continue;
        return pointId;
    }
    throw "No model satisfies parameters";
}
const IDartsTournament *DartsModelsService::getTournamentModelFromId(const QUuid &id) const
{
    auto models = _tournamentsDbContext->dartsTournaments();
    for (auto model : models) {
        if(model->id() == id)
            return model;
    }

    throw THROW_OBJECT_WITH_ID_NOT_FOUND(id.toString());
}

DartsModelsService *DartsModelsService::setGetScoreIndexesByTournamentId(GetScoreIndexesByDartsTournamentService *getScoreIndexesByTournamentId)
{
    _getScoreIndexesByTournamentId = getScoreIndexesByTournamentId;
    return this;
}
const IDartsPointInput *DartsModelsService::getPointModelById(const QUuid &id) const
{
    auto models = _dartsPointsDb->dartsInputModels();
    for (auto model : models)
    {
        if(model->id() == id)
            return model;
    }

    throw THROW_OBJECT_WITH_ID_NOT_FOUND(id.toString());
}

const IDartsScoreInput *DartsModelsService::getScoreModelById(const QUuid &id) const
{
    auto models = _dartsScoresDb->dartsInputModels();
    for (auto model : models)
    {
        if(model->id() == id)
            return model;
    }

    throw THROW_OBJECT_WITH_ID_NOT_FOUND(id.toString());
}

DartsModelsService *DartsModelsService::setGetScoreModelsByHint(GetScoreModelsByHintService *getScoreModelsByHint)
{
    _getScoreModelsByHint = getScoreModelsByHint;
    return this;
}

DartsModelsService *DartsModelsService::setDartsScoreModelHintService(SetDartsModelHint *setScoreModelHintService)
{
    _setScoreModelHintService = setScoreModelHintService;
    return this;
}

DartsModelsService* DartsModelsService::setGetScoreModelsByRoundIndex(GetScoreModelsByRoundIndex *getScoreModelsByRoundIndex)
{
    _getScoreModelsByRoundIndex = getScoreModelsByRoundIndex;
    return this;
}

DartsModelsService* DartsModelsService::setGetScoreModelsByPlayerId(GetScoreModelsByPlayerId *getScoreModelsByPlayerId)
{
    _getScoreModelsByPlayerId = getScoreModelsByPlayerId;
    return this;
}

DartsModelsService* DartsModelsService::setGetScoreModelsByTournamentId(GetScoreModelsByTournamentId *getScoreModelsByTournamentId)
{
    _getScoreModelsByTournamentId = getScoreModelsByTournamentId;
    return this;
}

DartsModelsService *DartsModelsService::setCountScoresByTournamentAndHint(CountScoresByTournamentAndHint *countScoresByTournamentAndHint)
{
    _countScoresByTournamentAndHint = countScoresByTournamentAndHint;
    return this;
}

DartsModelsService *DartsModelsService::setDartsScoresDb(IDartsScoreDb *dartsScoresDb)
{
    _dartsScoresDb = dartsScoresDb;
    return this;
}

DartsModelsService *DartsModelsService::setDartsScoreDb(IDartsScoreDb *dartsScoreDb)
{
    _dartsScoresDb = dartsScoreDb;
    return this;
}

DartsModelsService *DartsModelsService::setGetOrderedDartsScoreModels(GetOrderedDartsScoreService *getOrderedDartsScoreModels)
{
    _getOrderedDartsScoreModels = getOrderedDartsScoreModels;
    return this;
}

void DartsModelsService::removePointModel(const QUuid &point)
{
    auto models = _dartsPointsDb->dartsInputModels();
    for (auto model : models) {
        auto id = model->id();
        if(id == point)
        {
            auto index = _dartsPointsDb->indexOfDartsInputModel(model);
            _dartsPointsDb->removeDartsInputModelByIndex(index);
            return;
        }
    }
}

const IDartsPointIndexes* DartsModelsService::dartsPointIndexes(const QUuid &tournament) const
{
    auto orderedModels = _getOrderedDartsPointsModels->service(tournament,_dartsPointsDb);
    auto model = getTournamentModelFromId(tournament);
    auto count = dartsPointsCount(tournament,ModelDisplayHint::DisplayHint);
    auto indexes = _assembleDartsPointIndexes->service(orderedModels,model,count);
    return indexes;
}

const IDartsPointInput *DartsModelsService::getDartsPointModelById(const QUuid &id) const
{
    auto pointModel = getPointModelById(id);
    return pointModel;
}

QVector<int> DartsModelsService::dartsPointValuesByTournamentId(const QUuid &tournament) const
{
    QVector<int> userScores;
    auto assignedPlayersID = tournamentAssignedPlayers(tournament);
    for (auto playerID : assignedPlayersID) {
        auto s = point(tournament,playerID);
        userScores << s;
    }
    return userScores;
}

DartsModelsService* DartsModelsService::setTournamentsDbContext(IDartsTournamentDb *tournamentsDbContext)
{
    _tournamentsDbContext = tournamentsDbContext;
    return this;
}


DartsModelsService* DartsModelsService::setDartsPointsDb(IDartsPointDb *dartsPointsDb)
{
    _dartsPointsDb = dartsPointsDb;
    return this;
}

DartsModelsService *DartsModelsService::setGetOrderedDartsPointsModels(GetOrderedDartsPointService *getOrderedDartsPointsModels)
{
    _getOrderedDartsPointsModels = getOrderedDartsPointsModels;
    return this;
}

DartsModelsService *DartsModelsService::setAssembleDartsPointIndexes(GetPointIndexesFromDartsTournamentService *getDartsPointIndexes)
{
    _assembleDartsPointIndexes = getDartsPointIndexes;
    return this;
}

int DartsModelsService::dartsPointsCount(const QUuid &tournamentId, const int &hint) const
{
    auto count = 0;
    auto models = _dartsPointsDb->dartsInputModels();
    for (auto model : models) {
        if(model->tournamentId() != tournamentId)
            continue;
        if(model->hint() == hint || hint == allHints)
            count++;
    }
    return count;
}

void DartsModelsService::addDartsPoint(const IDartsPointInput *model)
{
    _dartsPointsDb->addDartsInputModel(dynamic_cast<const IDartsPointInput*>(model));
}

QVector<const IDartsPointInput *> DartsModelsService::getDartsPointModelsOrdedByIndexes(const QUuid &tournamentId) const
{
    auto orderedModels = _getOrderedDartsPointsModels->service(tournamentId,_dartsPointsDb);
    return orderedModels;
}

void DartsModelsService::removeHiddenPoints(const QUuid &tournament)
{
    auto scoresID = dartsPointIds(ModelDisplayHint::HiddenHint,tournament);
    for (auto scoreID : scoresID)
        removePointById(scoreID);
}

int DartsModelsService::point(const QUuid &tournament, const QUuid &playerId) const
{
    int totalScore = tournamentKeyPoint(tournament);
    auto playerScoresID = pointsByPlayerId(tournament,playerId,ModelDisplayHint::DisplayHint);
    for (auto scoreID : playerScoresID) {
        auto point = pointValueFromPointId(scoreID);
        totalScore -= point;
    }
    return totalScore;
}

void DartsModelsService::addDartsScore(const IDartsScoreInput* pointModel)
{
    _dartsScoresDb->addDartsInputModel(pointModel);
}

QUuid DartsModelsService::getDartsScoreId(const QUuid &tournamentId,
                                          const QUuid &playerId,
                                          const int &roundIndex) const
{
    auto scoreModels = _dartsScoresDb->dartsInputModels();
    auto scoreModelsByTournamentId = _getScoreModelsByTournamentId->service(scoreModels,tournamentId);
    auto scoreModelsByPlayerId = _getScoreModelsByPlayerId->service(scoreModelsByTournamentId,playerId);
    auto scoreModelsByRoundIndex = _getScoreModelsByRoundIndex->service(scoreModelsByPlayerId,roundIndex);
    auto scoreModelByRoundIndex = scoreModelsByRoundIndex.first();
    return scoreModelByRoundIndex->id();
}

QVector<QUuid> DartsModelsService::dartsScoreIds() const
{
    QVector<QUuid> ids;
    auto models = _dartsScoresDb->dartsInputModels();
    for (const auto& model : models) {
        auto modelId = model->id();
        ids << modelId;
    }
    return ids;
}

QVector<QUuid> DartsModelsService::dartsScoreIds(const QUuid &tournamentId) const
{
    QVector<QUuid> ids;
    auto models = _dartsScoresDb->dartsInputModels();
    for (const auto& model : models) {
        auto modelId = model->id();
        if(model->tournamentId() == tournamentId)
            ids << modelId;
    }
    return ids;
}

QVector<QUuid> DartsModelsService::dartsScoreIds(const QUuid &tournamentId, const int &roundIndex) const
{
    QVector<QUuid> ids;
    auto models = _dartsScoresDb->dartsInputModels();
    for (const auto& model : models) {
        auto modelId = model->id();
        if(model->tournamentId() != tournamentId)
            continue;
        if(model->roundIndex() == roundIndex)
            ids << modelId;
    }
    return ids;
}

QVector<QUuid> DartsModelsService::dartsScoreIds(const QUuid &tournamentId,
                                                 const int &roundIndex,
                                                 const int &setIndex) const
{
    QVector<QUuid> ids;
    auto models = _dartsScoresDb->dartsInputModels();
    for (const auto& model : models) {
        auto modelId = model->id();
        if(model->tournamentId() != tournamentId)
            continue;
        if(model->roundIndex() != roundIndex)
            continue;;
        if(model->setIndex() == setIndex)
            ids << modelId;
    }
    return ids;
}

QVector<QUuid> DartsModelsService::dartsScoreIds(const int &hint, const QUuid &tournamentId) const
{
    QVector<QUuid> ids;
    auto models = _dartsScoresDb->dartsInputModels();
    for (const auto& model : models) {
        auto modelId = model->id();
        if(model->tournamentId() != tournamentId)
            continue;
        if(model->hint() == hint)
            ids << modelId;
    }
    return ids;
}

QVector<QUuid> DartsModelsService::DartsScoresByPlayerId(const QUuid &tournamentId, const QUuid &playerId, const int &hint) const
{
    QVector<QUuid> ids;
    auto models = _dartsScoresDb->dartsInputModels();
    for (const auto& model : models) {
        auto modelId = model->id();
        if(model->tournamentId() != tournamentId)
            continue;
        if(model->playerId() != playerId)
            continue;
        if(model->hint() == hint)
            ids << modelId;
    }
    return ids;
}

int DartsModelsService::dartsScoresCount(const int &hint) const
{
    auto count = 0;
    auto models = _dartsScoresDb->dartsInputModels();
    for (const auto& model : models) {
        if(model->hint() == hint)
            count++;
    }
    return count;
}

const IDartsScoreInput *DartsModelsService::setDartsScoreHint(const QUuid &scoreId,
                                                              const int &hint)
{
    auto model = getScoreModelById(scoreId);
    auto indexOfModel = _dartsScoresDb->indexOfDartsInputModel(model);
    auto alteredModel = _setScoreModelHintService->service(model,hint);
    _dartsScoresDb->replaceDartsInputModel(indexOfModel,alteredModel);
    return alteredModel;
}

int DartsModelsService::dartsScoreRoundIndex(const QUuid &scoreId) const
{
    auto model = getScoreModelById(scoreId);
    auto roundIndex = model->roundIndex();
    return roundIndex;
}

int DartsModelsService::dartsScoreSetIndex(const QUuid &scoreId) const
{
    auto model = getScoreModelById(scoreId);
    auto setIndex = model->setIndex();
    return setIndex;
}

int DartsModelsService::ScoreValueFromScoreId(const QUuid &scoreId) const
{
    auto model = getScoreModelById(scoreId);
    auto score = model->score();
    return score;
}

QUuid DartsModelsService::tournamentIdFromScoreId(const QUuid &scoreId) const
{
    auto model =getScoreModelById(scoreId);
    auto tournamentId = model->tournamentId();
    return tournamentId;
}

QUuid DartsModelsService::playerIdFromScoreId(const QUuid &scoreId) const
{
    auto model = getScoreModelById(scoreId);
    auto playerId = model->playerId();
    return playerId;
}

int DartsModelsService::dartsScoreHint(const QUuid &scoreId) const
{
    auto model = getScoreModelById(scoreId);
    auto hint = model->hint();
    return hint;
}

void DartsModelsService::removeScoreById(const QUuid &scoreId)
{
    auto model = getScoreModelById(scoreId);
    auto indexOfModel = _dartsScoresDb->indexOfDartsInputModel(model);
    _dartsScoresDb->removeDartsInputModelByIndex(indexOfModel);
}

void DartsModelsService::removeHiddenScores(const QUuid &tournamentId)
{
    auto modelIds = dartsScoreIds(ModelDisplayHint::HiddenHint,tournamentId);
    for (const auto& modelId : modelIds)
        removeScoreById(modelId);
}

int DartsModelsService::dartsScoreId(const QUuid& tournamentId, const QUuid &playerId) const
{
    auto modelIds = dartsScoreIds(tournamentId);
    for (const auto& modelId : modelIds) {
        auto model = getScoreModelById(modelId);
        if(model->playerId() == playerId)
            return model->score();
    }
    return -1;
}

QVector<QUuid> DartsModelsService::scoreModelsByPlayerId(const QUuid &playerId) const
{
    QVector<QUuid> list;
    auto models = _dartsScoresDb->dartsInputModels();
    for (const auto& model : models) {
        auto scorePlayerId = model->playerId();
        if(scorePlayerId == playerId)
            list << model->id();
    }
    return list;
}

void DartsModelsService::removeScoresByTournamentId(const QUuid &tournamentId)
{
    auto modelIds = dartsScoreIds(tournamentId);
    for (const auto& modelId : modelIds) {
        auto model = getScoreModelById(modelId);
        if(model->tournamentId() == tournamentId)
            removeScoreById(model->id());
    }
}

void DartsModelsService::removeScoreModel(const QUuid &scoreId)
{
    auto model =getScoreModelById(scoreId);
    auto indexOfModel = _dartsScoresDb->indexOfDartsInputModel(model);
    _dartsScoresDb->removeDartsInputModelByIndex(indexOfModel);
}


QVector<const IDartsTournament *> DartsModelsService::getDartsTournamentModels() const
{
    auto models = _tournamentsDbContext->dartsTournaments();
    return models;
}

const IDartsScoreIndexes *DartsModelsService::dartsScoreIndexes(const QUuid&tournamentId) const
{
    auto orderedModels = _getOrderedDartsScoreModels->service(tournamentId,_dartsScoresDb);
    auto model = getTournamentModelFromId(tournamentId);
    auto count = _countScoresByTournamentAndHint->service(tournamentId,
                                                          ModelDisplayHint::DisplayHint,
                                                          _dartsScoresDb);
    auto indexes = _getScoreIndexesByTournamentId->service(orderedModels,model,count);
    return indexes;
}


int DartsModelsService::dartsScoreCount(const QUuid &tournamentId, const int &hint) const
{
    auto count = 0;
    auto models = _dartsScoresDb->dartsInputModels();
    for (auto model : models) {
        if(model->tournamentId() != tournamentId)
            continue;
        if(model->hint() == hint || hint == allHints)
            count++;
    }
    return count;
}

QVector<const IDartsScoreInput *> DartsModelsService::dartsScoreModelsByTournamentIdAndHint(const QUuid &tournamentId,
                                                                                            const int& hint) const
{
    auto models = _dartsScoresDb->dartsInputModels();
    auto scoreModelsByTournamentId = _getScoreModelsByTournamentId->service(models,tournamentId);
    auto scoreModelsByHint = _getScoreModelsByHint->service(models,hint);
    return scoreModelsByHint;
}
