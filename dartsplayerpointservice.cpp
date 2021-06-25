#include "dartsplayerpointservice.h"

using namespace DartsPointControllerContext;

DartsPlayerPointService *DartsPlayerPointService::createInstance(const int &initialScore, const QUuid &winner)
{
    return new DartsPlayerPointService(initialScore,
                                  winner);
}

QUuid DartsPlayerPointService::winnerId() const
{
    return _winner;
}

DartsPlayerPointService *DartsPlayerPointService::setWinner(const QUuid &id)
{
    _winner = id;
    return this;
}

QString DartsPlayerPointService::winnerName() const
{
    auto id = winnerId();
    auto userName = playerName(id);
    return userName;
}

void DartsPlayerPointService::addPlayerEntity(const PlayerModel* model)
{
    auto tuple = PlayerPointContext::PlayerTuple(model->playerId(),model->playerName(),initialScore());
    _playerTuples.append(tuple);
}

void DartsPlayerPointService::addPlayerEntitiesByModels(const QVector<const PlayerModel *> &models)
{
    for (const auto& model : models)
        addPlayerEntity(model);
}

int DartsPlayerPointService::subtractPlayerScore(const PointModel *model)
{
    auto tuple = tupleAtId(model->playerId());
    auto indexOfTuple = indexOf(tuple);
    auto tupleScore = tuple.score;
    auto score = model->score();
    auto newScore = tupleScore - score;
    tuple.score = newScore;
    replaceTupleAt(indexOfTuple,tuple);
    return newScore;
}

void DartsPlayerPointService::subtractPlayerScoresByModels(const QVector<const PointModel *> &models)
{
    for (const auto& model : models)
        subtractPlayerScore(model);
}

int DartsPlayerPointService::addPlayerScore(const PointModel *model)
{
    auto tuple = tupleAtId(model->playerId());
    auto indexOfTuple = indexOf(tuple);
    auto tupleScore = tuple.score;
    auto score = model->score();
    auto newTupleScore = tupleScore + score;
    tuple.score = newTupleScore;
    replaceTupleAt(indexOfTuple,tuple);
    return newTupleScore;
}

int DartsPlayerPointService::playerScore(const int &index) const
{
    auto tuple = tupleAtIndex(index);
    auto score = tuple.score;
    return score;
}

int DartsPlayerPointService::playerScore(const QUuid &id) const
{
    auto tuple = tupleAtId(id);
    auto score = tuple.score;
    return score;
}

void DartsPlayerPointService::setPlayerScoreByIndex(const int &index, const int &input)
{
    auto tuple = tupleAtIndex(index);
    tuple.score = input;
    replaceTupleAt(index,tuple);
}

void DartsPlayerPointService::setPlayerScoresByList(const QVector<int> &list)
{
    if(list.count() != playersCount())
        throw INCONSISTENCY_EXCEPTION_MESSAGE;
    for (int i = 0; i < playersCount(); ++i) {
        auto tuple = tupleAtIndex(i);
        tuple.score = list.at(i);
        replaceTupleAt(i,tuple);
    }
}

void DartsPlayerPointService::setPlayerScoreById(const QUuid &id, const int &input)
{
    auto tuple = tupleAtId(id);
    auto index = indexOf(tuple);
    tuple.score = input;
    replaceTupleAt(index,tuple);
}

QString DartsPlayerPointService::playerName(const int &index) const
{
    auto tuple = tupleAtIndex(index);
    auto name = tuple.name;
    return name;
}

QString DartsPlayerPointService::playerName(const QUuid &id) const
{
    auto tuple = tupleAtId(id);
    auto name = tuple.name;
    return name;
}

QVector<QString> DartsPlayerPointService::playerNames() const
{
    QVector<QString> resultingList;
    for (int i = 0; i < playersCount(); ++i) {
        auto tuple = _playerTuples.at(i);
        auto userName = tuple.name;
        resultingList << userName;
    }
    return resultingList;
}

QUuid DartsPlayerPointService::playerIdAtIndex(const int &index) const
{
    auto tuple = tupleAtIndex(index);
    auto id = tuple.id;
    return id;
}

int DartsPlayerPointService::playersCount() const
{
    return count();
}

int DartsPlayerPointService::initialScore() const
{
    return _initialScore;
}

int DartsPlayerPointService::calculateAccumulatedScoreCandidate(const int &index, const int &score) const
{
    auto tuple = tupleAtIndex(index);
    auto tupleScore = tuple.score;
    auto scoreCandidate = tupleScore - score;
    return scoreCandidate;
}

void DartsPlayerPointService::resetScores()
{
    for (auto &tuple : _playerTuples)
        tuple.score = _initialScore;
}

DartsPlayerPointService::DartsPlayerPointService(const int &initialScore, const QUuid &winner)
{
    _initialScore = initialScore;
    _winner = winner;
}

int DartsPlayerPointService::indexOf(const PlayerPointContext::PlayerTuple &tuple)
{
    for (int i = 0; i < count(); ++i) {
        auto t = _playerTuples.at(i);
        if(t == tuple)
            return i;
    }
    return -1;
}

PlayerPointContext::PlayerTuple DartsPlayerPointService::tupleAtIndex(const int &index) const
{
    auto tuple = _playerTuples.at(index);
    return tuple;
}

PlayerPointContext::PlayerTuple DartsPlayerPointService::tupleAtId(const QUuid &id) const
{
    for (int i = 0; i < count(); ++i) {
        auto tuple = _playerTuples.at(i);
        auto _id = tuple.id;
        if(id == _id)
            return tuple;
    }
    return PlayerPointContext::PlayerTuple();
}

PlayerPointContext::PlayerTuple DartsPlayerPointService::tupleAtId(const DartsPlayerPointService::PlayerTuples *_tuples, const QUuid &id)
{
    for (const auto &tuple : *_tuples)
    {
        auto playerId = tuple.id;
        if(playerId == id)
            return tuple;
    }
    return PlayerPointContext::PlayerTuple();
}

DartsPlayerPointService::PlayerTuples DartsPlayerPointService::createInitializedTuples()
{
    PlayerTuples initializedTuples;
    for (const auto &tuple : qAsConst(_playerTuples))
    {
        PlayerPointContext::PlayerTuple t;
        t.id = tuple.id;
        t.name = tuple.name;
        t.score = initialScore();
        initializedTuples << t;
    }
    return initializedTuples;
}

void DartsPlayerPointService::replaceTupleAt(const int &index, const PlayerPointContext::PlayerTuple &tuple)
{
    _playerTuples.replace(index,tuple);
}

int DartsPlayerPointService::count() const
{
    return _playerTuples.count();
}
