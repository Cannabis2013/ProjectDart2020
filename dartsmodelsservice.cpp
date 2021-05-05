#include "dartsmodelsservice.h"

DartsModelsService::~DartsModelsService()
{
}

DartsModelsService *DartsModelsService::createInstance()
{
    return new DartsModelsService();
}

DartsModelsService* DartsModelsService::setup()
{
    return this;
}

QUuid DartsModelsService::addDartsTournamentToDb(const IDartsTournament<QUuid,QString>* tournament)
{
    // Add model to dbcontext
    _tournamentsDbContext->addTournament(tournament);
    // Return model id
    return tournament->id();
}

bool DartsModelsService::removeTournamentsByIndexes(const QVector<int> &indexes)
{
    auto orderedList = indexes;
    // Order list to ensure that elements that corresponds to an index in list gets deleted
    std::sort(orderedList.begin(),orderedList.end());
    for (auto i = orderedList.count() - 1; i >= 0; --i)
        _tournamentsDbContext->removeDartsTournamentModelByIndex(i);
    return true;
}


QUuid DartsModelsService::tournamentIdFromIndex(const int &index)
{
    try {
        auto model = _tournamentsDbContext->dartsTournamentModelFromIndex(index);
        auto tournament = dynamic_cast<const IDartsTournament<QUuid,QString>*>(model);
        auto id = tournament->id();
        return id;
    }  catch (...) {
        throw "TOURNAMENT_NOT_FOUND";
    }
}

QVector<QUuid> DartsModelsService::tournaments()
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

int DartsModelsService::tournamentsCount()
{
    auto tournaments = _tournamentsDbContext->dartsTournaments();
    auto count = tournaments.count();
    return count;
}

QString DartsModelsService::tournamentTitle(const QUuid &tournament)
{
    return getTournamentModelFromId<IDartsTournament<QUuid,QString>>(tournament)->title();
}

int DartsModelsService::tournamentAttempts(const QUuid &tournament)
{
    auto model = getTournamentModelFromId<IDartsTournament<QUuid,QString>>(tournament);
    auto numberOfThrows = model->attempts();
    return numberOfThrows;
}

QVector<QUuid> DartsModelsService::tournamentAssignedPlayers(const QUuid &tournament)
{
    QVector<QUuid> assignedPlayers;
    const IDartsTournament<QUuid,QString>* tournamentModel;
    try {
        tournamentModel = getTournamentModelFromId<IDartsTournament<QUuid,QString>>(tournament);
    } catch (const char *msg) {
        throw  msg;
    }
    assignedPlayers = tournamentModel->assignedPlayerIdentities();
    return assignedPlayers;
}


int DartsModelsService::tournamentGameMode(const QUuid &tournament)
{
    return getTournamentModelFromId<IDartsTournament<QUuid,QString>>(tournament)->gameMode();
}

int DartsModelsService::tournamentTerminalKeyCode(const QUuid &tournament)
{
    auto tournamentModel = getTournamentModelFromId<IDartsTournament<QUuid,QString>>(tournament);
    auto conditionKeyCode = tournamentModel->terminalKeyCode();
    return conditionKeyCode;
}

int DartsModelsService::tournamentKeyPoint(const QUuid &tournament)
{
    auto tournamentModel = getTournamentModelFromId<IDartsTournament<QUuid,QString>>(tournament);
    auto keyPoint = tournamentModel->keyPoint();
    return keyPoint;
}

int DartsModelsService::tournamentTableViewHint(const QUuid &tournament)
{
    auto tournamentModel = getTournamentModelFromId<IDartsTournament<QUuid,QString>>(tournament);
    auto hint = tournamentModel->displayHint();
    return hint;
}

int DartsModelsService::tournamentInputMode(const QUuid &tournament)
{
    auto tournamentModel = getTournamentModelFromId<IDartsTournament<QUuid,QString>>(tournament);
    auto inputMode = tournamentModel->inputHint();
    return inputMode;
}

const IDartsPointInput<QUuid> *DartsModelsService::assembleDartsInputPointFromJson(const QByteArray &json)
{
    auto model = _assembleDartsInputPointFromJson->service(json);
    return model;
}

int DartsModelsService::tournamentStatus(const QUuid &tournament)
{
    auto model = getTournamentModelFromId<IDartsTournament<QUuid,QString>>(tournament);
    auto status = model->status();
    return status;
}

QUuid DartsModelsService::tournamentWinner(const QUuid &tournament)
{
    auto tournamentModel = getTournamentModelFromId<IDartsTournament<QUuid,QString>>(tournament);
    return tournamentModel->winnerId();
}

void DartsModelsService::tournamentSetWinnerId(const QUuid &tournament,
                                               const QUuid &winner)
{
    auto oldModel = getTournamentModelFromId<IDartsTournament<QUuid,QString>>(tournament);
    auto newModel = const_cast<IDartsTournament<QUuid,QString>*>(oldModel);
    newModel->setWinnerId(winner);
    auto index = _tournamentsDbContext->indexOfTournament(oldModel);
    _tournamentsDbContext->replaceTournament(index,newModel);
}

void DartsModelsService::tournamentAssignPlayer(const QUuid &tournament, const QUuid &player)
{
    auto oldModel = getTournamentModelFromId<IDartsTournament<QUuid,QString>>(tournament);
    auto assignedPlayers = oldModel->assignedPlayerIdentities();
    assignedPlayers.append(player);
    auto newModel = const_cast<IDartsTournament<QUuid,QString>*>(oldModel);
    newModel->setAssignedPlayerIdentities(assignedPlayers);
    auto index = _tournamentsDbContext->indexOfTournament(oldModel);
    _tournamentsDbContext->replaceTournament(index,newModel);
}

void DartsModelsService::tournamentAssignPlayers(const QUuid &tournament,
                                                 const QVector<QUuid> &playersIds)
{
    auto oldModel = getTournamentModelFromId<IDartsTournament<QUuid,QString>>(tournament);
    auto newModel = const_cast<IDartsTournament<QUuid,QString>*>(oldModel);
    auto assignedPlayers = newModel->assignedPlayerIdentities();
    assignedPlayers.append(playersIds);
    newModel->setAssignedPlayerIdentities(assignedPlayers);
    auto index = _tournamentsDbContext->indexOfTournament(oldModel);
    _tournamentsDbContext->replaceTournament(index,newModel);
}

void DartsModelsService::tournamentUnAssignPlayer(const QUuid &tournament, const QUuid &player)
{
    auto oldModel = getTournamentModelFromId<IDartsTournament<QUuid,QString>>(tournament);
    auto assignedPlayers = oldModel->assignedPlayerIdentities();
    assignedPlayers.removeOne(player);
    auto newModel = const_cast<IDartsTournament<QUuid,QString>*>(oldModel);
    newModel->setAssignedPlayerIdentities(assignedPlayers);
    auto index = _tournamentsDbContext->indexOfTournament(oldModel);
    _tournamentsDbContext->replaceTournament(index,newModel);
}

const IDartsTournament<QUuid, QString> *DartsModelsService::assembleDartsTournamentFromJson(const QByteArray &json)
{
    auto model = _assembleDartsTournamentFromJson->service(json);
    return model;
}

QList<QUuid> DartsModelsService::dartsPointIds() const
{
    QList<QUuid> resultingList;
    auto scores = _dartsPointsDb->dartsInputModels();
    for (auto scoreModel : scores) {
        auto scoreID = scoreModel->id();
        resultingList << scoreID;
    }
    return resultingList;
}

QList<QUuid> DartsModelsService::dartsPointIds(const QUuid &tournament) const
{
    QList<QUuid> resultingList;
    auto scores = _dartsPointsDb->dartsInputModels();
    for (auto scoreModel : scores) {
        auto playerInput = dynamic_cast<const IPlayerInput<QUuid>*>(scoreModel);
        auto compareTournamentID = playerInput->tournamentId();
        if(compareTournamentID == tournament)
            resultingList << scoreModel->id();
    }

    return resultingList;
}

QList<QUuid> DartsModelsService::dartsPointIds(const QUuid &tournament,
                                                     const int &round)
{
    QList<QUuid> resultingList;
    auto ftpScoreIds = this->dartsPointIds(tournament);
    for (auto pointID : ftpScoreIds) {
        auto ftpScore = this->getPointModelFromId<IDartsPointInput<QUuid>>(pointID);
        auto roundIndex = ftpScore->roundIndex();
        if(roundIndex == round)
            resultingList << pointID;
    }
    return resultingList;
}

QList<QUuid> DartsModelsService::dartsPointIds(const QUuid &tournament,
                                                  const int &round,
                                                  const int &set)
{
    QList<QUuid> resultingList;
    auto p = this->dartsPointIds(tournament,round);
    for (auto scoreModelID : p) {
        auto ftpScore = getPointModelFromId<IDartsPointInput<QUuid>>(scoreModelID);
        auto setIndex = ftpScore->setIndex();
        if(setIndex == set)
            resultingList << scoreModelID;
    }

    return resultingList;
}

QList<QUuid> DartsModelsService::dartsPointIds(const int &hint, const QUuid &tournament)
{
    QList<QUuid> resultingList;
    auto modelIds = this->dartsPointIds(tournament);
    for (auto modelId : modelIds) {
        auto ftpScoreModel = getPointModelFromId<IPlayerInput<QUuid>>(modelId);
        auto scoreModelHint = ftpScoreModel->hint();
        if(scoreModelHint == hint)
            resultingList << modelId;
    }
    return resultingList;
}

QUuid DartsModelsService::setDartsPointHint(const QUuid &point,
                                                 const int &hint)
{
    auto model = getPointModelFromId<IDartsPointInput<QUuid>>(point);
    auto newModel = const_cast<IDartsPointInput<QUuid>*>(model);
    auto index = _dartsPointsDb->indexOfDartsInputModel(model);
    newModel->setDisplayHint(hint);
    _dartsPointsDb->replaceDartsInputModel(index,newModel);
    return newModel->id();
}

int DartsModelsService::dartsPointRoundIndex(const QUuid &playerScore)
{
    auto ftpScoreModel = getPointModelFromId<IDartsPointInput<QUuid>>(playerScore);
    auto roundIndex = ftpScoreModel->roundIndex();
    return roundIndex;
}

int DartsModelsService::dartsPointSetIndex(const QUuid &playerScore)
{
    auto ftpScoreModel = getPointModelFromId<IDartsPointInput<QUuid>>(playerScore);
    auto setIndex = ftpScoreModel->setIndex();
    return setIndex;
}


int DartsModelsService::dartsPointAttemptIndex(const QUuid &point)
{
    try {
        auto ftpScoreModel = getPointModelFromId<IDartsPointInput<QUuid>>(point);
        auto throwIndex = ftpScoreModel->attempt();
        return throwIndex;
    } catch (const char *msg) {
        throw msg;
    }
}
int DartsModelsService::pointValueFromPointId(const QUuid &point) const
{
    try {
        auto ftpScoreModel = getPointModelFromId<IDartsPointInput<QUuid>>(point);
        auto pointValue = ftpScoreModel->point();
        return pointValue;

    }  catch (const char *msg) {
        throw msg;
    }
}

QUuid DartsModelsService::tournamentIdFromPointId(const QUuid &playerScore)
{
    auto model = getPointModelFromId<IPlayerInput<QUuid>>(playerScore);
    auto tournamentID = model->tournamentId();
    return tournamentID;
}

QUuid DartsModelsService::playerIdFromPointId(const QUuid &point) const
{
    auto ftpScoreModel = getPointModelFromId<IPlayerInput<QUuid>>(point);
    auto playerID = ftpScoreModel->playerId();
    return playerID;
}

int DartsModelsService::pointHint(const QUuid &scoreID)
{
    try {
        auto scoreModel = getPointModelFromId<IPlayerInput<QUuid>>(scoreID);
        auto hint = scoreModel->hint();
        return hint;
    } catch (const char *msg) {
        throw msg;
    }
}

int DartsModelsService::pointKeyCode(const QUuid &scoreID) const
{
    try {
        auto ftpScoreModel = getPointModelFromId<IDartsPointInput<QUuid>>(scoreID);
        auto keyCode = ftpScoreModel->modKeyCode();
        return keyCode;
    } catch (const char *msg) {
        throw msg;
    }
}

QList<QUuid> DartsModelsService::pointModels(const QUuid &player)
{
    QList<QUuid> resultingList;
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
        auto scoreModel = getPointModelFromId<IDartsPointInput<QUuid>>(scoreID);
        auto tournamentID = scoreModel->tournamentId();
        if(tournamentID == tournament)
        {
            auto index = _dartsPointsDb->indexOfDartsInputModel(scoreModel);
            _dartsPointsDb->removeDartsInputModelByIndex(index);
        }
    }
}

QList<QUuid> DartsModelsService::pointsByPlayerId(const QUuid &tournament, const QUuid &player, const int &hint)
{
    QList<QUuid> resultingList;
    auto scoreModelIds = dartsPointIds(tournament);
    for (auto pointID : scoreModelIds) {
        auto model = getPointModelFromId(pointID);
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
        auto scoreModel = getPointModelFromId<IDartsPointInput<QUuid>>(point);
        auto index = _dartsPointsDb->indexOfDartsInputModel(scoreModel);
        _dartsPointsDb->removeDartsInputModelByIndex(index);
    } catch (const char *msg) {
        return;
    }
}

QUuid DartsModelsService::getDartsPointId(const QUuid &tournament,
                                                const QUuid &player,
                                                const int &round,
                                                const int &throwIndex,
                                                const int &hint)
{
    auto tournamentScoreModels = dartsPointIds(tournament);
    for (auto scoreModelID : tournamentScoreModels) {
        auto model = getPointModelFromId(scoreModelID);
        auto scoreModel = dynamic_cast<const IDartsPointInput<QUuid>*>(model);
        auto modelHint = scoreModel->hint();
        auto playerID = scoreModel->playerId();
        auto leg = dartsPointAttemptIndex(scoreModelID);
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

QUuid DartsModelsService::getDartsPointId(const QUuid &tournament,
                                   const QUuid &player,
                                   const int &round,
                                   const int &attemptIndex)
{
    auto tournamentScoreModels = dartsPointIds(tournament);
    for (auto scoreModelID : tournamentScoreModels) {
        auto model = getPointModelFromId(scoreModelID);
        auto scoreModel = dynamic_cast<const IDartsPointInput<QUuid>*>(model);
        auto playerID = scoreModel->playerId();
        if(playerID != player)
            continue;
        auto leg = dartsPointAttemptIndex(scoreModelID);
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
const TModelInterface *DartsModelsService::getTournamentModelFromId(const QUuid &id)
{
    auto models = _tournamentsDbContext->dartsTournaments();
    for (auto model : models) {
        if(model->id() == id)
            return dynamic_cast<const TModelInterface*>(model);
    }

    throw THROW_OBJECT_WITH_ID_NOT_FOUND(id.toString());
}
template<typename T>
const T *DartsModelsService::getPointModelFromId(const QUuid &id) const
{
    auto models = _dartsPointsDb->dartsInputModels();
    for (auto model : models)
    {
        if(model->id() == id)
            return dynamic_cast<const T*>(model);
    }

    throw THROW_OBJECT_WITH_ID_NOT_FOUND(id.toString());
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

const QVector<int> DartsModelsService::dartsIndexes(const QUuid &tournament)
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
            getDartsPointId(tournament,
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
        totalTurns = dartsPointsCount(ModelDisplayHint::allHints);

    QVector<int> indexes = {
        totalTurns,
        turnIndex,
        roundIndex,
        setIndex,
        attemptIndex
    };
    return indexes;
}

QVector<int> DartsModelsService::dartsPointValuesByTournamentId(const QUuid &tournament)
{
    QVector<int> userScores;
    auto assignedPlayersID = tournamentAssignedPlayers(tournament);
    for (auto playerID : assignedPlayersID) {
        auto s = point(tournament,playerID);
        userScores << s;
    }
    return userScores;
}

void DartsModelsService::setTournamentsDbContext(IDartsTournamentDb<IDartsTournament<QUuid, QString> > *tournamentsDbContext)
{
    _tournamentsDbContext = tournamentsDbContext;
}

void DartsModelsService::setAssembleDartsInputPointFromJson(IUnaryService<const QByteArray &, const IDartsPointInput<QUuid> *> *assembleDartsInputPointFromJson)
{
    _assembleDartsInputPointFromJson = assembleDartsInputPointFromJson;
}

DartsModelsService* DartsModelsService::setAssembleDartsTournamentFromJson(IUnaryService<const QByteArray &, const IDartsTournament<QUuid, QString> *> *assembleDartsTournamentFromJson)
{
    _assembleDartsTournamentFromJson = assembleDartsTournamentFromJson;
    return this;
}

DartsModelsService* DartsModelsService::setGetOrderedDartsPointsModels(IBinaryService<const QUuid &, const IdartsPointDb<IDartsPointInput<QUuid> > *, QVector<const IDartsPointInput<QUuid> *> > *getOrderedDartsPointsModels)
{
    _getOrderedDartsPointsModels = getOrderedDartsPointsModels;
    return this;
}

int DartsModelsService::dartsPointsCount(const int &hint)
{
    auto count = 0;
    auto models = _dartsPointsDb->dartsInputModels();
    for (auto model : models) {
        auto scoreModel = dynamic_cast<const IPlayerInput<QUuid>*>(model);
        if(scoreModel->hint() == hint || hint == allHints)
            count++;
    }
    return count;
}

void DartsModelsService::addDartsPoint(const IDartsPointInput<QUuid> *model)
{
    _dartsPointsDb->addDartsInputModel(dynamic_cast<const IDartsPointInput<QUuid>*>(model));
}

QVector<const IDartsPointInput<QUuid> *> DartsModelsService::getDartsPointModelsOrdedByIndexes(const QUuid &tournamentId) const
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

int DartsModelsService::point(const QUuid &tournament, const QUuid &player)
{
    int totalScore = tournamentKeyPoint(tournament);
    auto playerScoresID = pointsByPlayerId(tournament,player,ModelDisplayHint::DisplayHint);
    for (auto scoreID : playerScoresID) {
        auto point = pointValueFromPointId(scoreID);
        totalScore -= point;
    }
    return totalScore;
}

int DartsModelsService::point(const QUuid &player)
{
    Q_UNUSED(player);
    return -1;
}



const IDartsScoreInput<QUuid> *DartsModelsService::assembleDartsScoresFromJson(const QByteArray &json)
{
}

void DartsModelsService::addDartsScore(const IDartsScoreInput<QUuid> *)
{
}

QUuid DartsModelsService::getDartsScoreId(const QUuid &tournament,
                                          const QUuid &player,
                                          const int &round,
                                          const int &hint)
{
}

QUuid DartsModelsService::getDartsScoreId(const QUuid &tournament,
                                          const QUuid &player,
                                          const int &round)
{
}

QList<QUuid> DartsModelsService::dartsScoreIds() const
{
}

QList<QUuid> DartsModelsService::dartsScoreIds(const QUuid &tournament) const
{
}

QList<QUuid> DartsModelsService::dartsScoreIds(const QUuid &tournament, const int &roundID)
{
}

QList<QUuid> DartsModelsService::dartsScoreIds(const QUuid &tournament, const int &roundID, const int &setID)
{
}

QList<QUuid> DartsModelsService::dartsScoreIds(const int &hint, const QUuid &tournament)
{
}

QList<QUuid> DartsModelsService::ScoresByPlayerId(const QUuid &tournament, const QUuid &player, const int &hint)
{
}

int DartsModelsService::dartsScoresCount(const int &hint)
{
}

QUuid DartsModelsService::setDartsScoreHint(const QUuid &point, const int &hint)
{
}

int DartsModelsService::dartsScoreRoundIndex(const QUuid &)
{
}

int DartsModelsService::dartsScoreSetIndex(const QUuid &)
{
}

int DartsModelsService::ScoreValueFromScoreId(const QUuid &) const
{
}

QUuid DartsModelsService::tournamentIdFromScoreId(const QUuid &playerScore)
{
}

QUuid DartsModelsService::playerIdFromScoreId(const QUuid &playerScore) const
{
}

int DartsModelsService::ScoreHint(const QUuid &scoreID)
{
}

int DartsModelsService::ScoreKeyCode(const QUuid &) const
{
}

void DartsModelsService::removeScoreById(const QUuid &)
{
}

void DartsModelsService::removeHiddenScores(const QUuid &)
{
}

int DartsModelsService::Score(const QUuid &, const QUuid &)
{
}

int DartsModelsService::Score(const QUuid &player)
{
}

QList<QUuid> DartsModelsService::ScoreModels(const QUuid &player)
{
}

void DartsModelsService::removeScoresByTournamentId(const QUuid &tournament)
{
}

void DartsModelsService::removeScoreModel(const QUuid &playerScore)
{
}


const IDartsTournament<QUuid, QString> *DartsModelsService::getDartsTournamentById(const QUuid& tournamentId) const
{
    auto dartsTournamentModels = _tournamentsDbContext->dartsTournaments();
    for (const auto& dartsTournamentModel : dartsTournamentModels) {
        auto modelId = dartsTournamentModel->id();
        if(modelId == tournamentId)
            return dartsTournamentModel;
    }
    throw "No dartstournamentmodel exists with provided id";
}
