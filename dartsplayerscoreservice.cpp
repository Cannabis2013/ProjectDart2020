#include "dartsplayerscoreservice.h"


DartsPlayerScoreService *DartsPlayerScoreService::createInstance(const int &initialScore,
                                                       const QUuid &winner)
{
    return new DartsPlayerScoreService(initialScore,
                                  winner);
}

void DartsPlayerScoreService::addPlayerEntity(const QUuid& id, const QString& name)
{
    auto tuple = PlayerTuple(id,name,initialScore());
    _playerTuples.append(tuple);
}


int DartsPlayerScoreService::subtractPlayerScore(const QUuid& id, const int& score)
{
    auto tuple = tupleAtId(id);
    auto indexOfTuple = indexOf(tuple);
    auto tupleScore = tuple.score;
    auto newTupleScore = tupleScore - score;
    tuple.score = newTupleScore;
    replaceTupleAt(indexOfTuple,tuple);
    return newTupleScore;
}

int DartsPlayerScoreService::addPlayerScore(const QUuid &id, const int &score)
{
    auto tuple = tupleAtId(id);
    auto indexOfTuple = indexOf(tuple);
    auto tupleScore = tuple.score;
    auto newTupleScore = tupleScore + score;
    tuple.score = newTupleScore;
    replaceTupleAt(indexOfTuple,tuple);
    return newTupleScore;
}

int DartsPlayerScoreService::playerScore(const int &index) const
{
    auto tuple = tupleAtIndex(index);
    auto score = tuple.score;
    return score;
}

int DartsPlayerScoreService::playerScore(const QUuid &id) const
{
    auto tuple = tupleAtId(id);
    auto score = tuple.score;
    return score;
}

void DartsPlayerScoreService::setPlayerScoreByIndex(const int &index, const int &input)
{
    auto tuple = tupleAtIndex(index);
    tuple.score = input;
    replaceTupleAt(index,tuple);

}

void DartsPlayerScoreService::setPlayerScoresByList(const QVector<int> &list)
{
    if(list.count() != playersCount())
        throw INCONSISTENCY_EXCEPTION_MESSAGE;
    for (int i = 0; i < playersCount(); ++i) {
        auto tuple = tupleAtIndex(i);
        tuple.score = list.at(i);
        replaceTupleAt(i,tuple);
    }
}

void DartsPlayerScoreService::setPlayerScoreById(const QUuid &id, const int &input)
{
    auto tuple = tupleAtId(id);
    auto index = indexOf(tuple);
    tuple.score = input;
    replaceTupleAt(index,tuple);

}

QString DartsPlayerScoreService::playerNameByIndex(const int &index) const
{
    auto tuple = tupleAtIndex(index);
    auto name = tuple.name;
    return name;
}

QString DartsPlayerScoreService::playerNameById(const QUuid &id) const
{
    auto tuple = tupleAtId(id);
    auto name = tuple.name;
    return name;
}

QVector<QString> DartsPlayerScoreService::playerNames() const
{
    QVector<QString> resultingList;
    for (int i = 0; i < playersCount(); ++i) {
        auto tuple = _playerTuples.at(i);
        auto userName = tuple.name;
        resultingList << userName;
    }
    return resultingList;
}

QUuid DartsPlayerScoreService::playerIdAtIndex(const int &index) const
{
    auto tuple = tupleAtIndex(index);
    auto id = tuple.id;
    return id;
}

int DartsPlayerScoreService::playersCount() const
{
    return count();
}

QUuid DartsPlayerScoreService::winnerId() const
{
    return _winner;
}

IPlayerScoreService *DartsPlayerScoreService::setWinner(const QUuid &id)
{
    _winner = id;
    return this;
}

QString DartsPlayerScoreService::winnerUserName() const
{
    auto id = winnerId();
    auto userName = playerNameById(id);
    return userName;
}

int DartsPlayerScoreService::initialScore() const
{
    return _initialScore;
}

int DartsPlayerScoreService::calculateAccumulatedScoreCandidate(const int &index, const int &score) const
{
    auto tuple = tupleAtIndex(index);
    auto s = tuple.score;
    auto scoreCandidate = s - score;
    return scoreCandidate;
}

void DartsPlayerScoreService::resetScores()
{
    for (int i = 0; i < playersCount(); ++i) {
        auto tuple = tupleAtIndex(i);
        tuple.score = initialScore();
        _playerTuples.replace(i,tuple);
    }
}

DartsPlayerScoreService::DartsPlayerScoreService(const int &initialScore,
                                       const QUuid &winner)
{
    _initialScore = initialScore;
    _winner = winner;
}

DartsPlayerScoreService::PlayerTuples DartsPlayerScoreService::assembleScoreTubble(const QVector<QUuid> &userIds, const QVector<QString> &userNames, const QVector<int> &userScores)
{
    // First check for consistency
    auto userIdsCount = userIds.count();
    auto userNamesCount = userNames.count();
    auto userScoresCount = userScores.count();
    auto sum = userIdsCount + userNamesCount + userScoresCount;
    if(sum / 3 != userIdsCount)
        throw INCONSISTENCY_EXCEPTION_MESSAGE;
    PlayerTuples tuples;
    for (int i = 0; i < userIdsCount; ++i) {
        auto userId = userIds.at(i);
        auto userName = userNames.at(i);
        auto userScore = userScores.at(i);
        tuples += PlayerTuple(userId,userName,userScore);
    }
    return tuples;
}

PlayerTuple DartsPlayerScoreService::tupleAtIndex(const int &index) const
{
    auto tuple = _playerTuples.at(index);
    return tuple;
}

PlayerTuple DartsPlayerScoreService::tupleAtId(const QUuid &id) const{
    for (int i = 0; i < count(); ++i) {
        auto tuple = _playerTuples.at(i);
        auto _id = tuple.id;
        if(id == _id)
            return tuple;
    }
    return PlayerTuple();
}

PlayerTuple DartsPlayerScoreService::tupleAtId(const PlayerTuples *_tuples, const QUuid &id)
{
    for (const auto &tuple : *_tuples)
    {
        auto playerId = tuple.id;
        if(playerId == id)
            return tuple;
    }
    return PlayerTuple();
}

DartsPlayerScoreService::PlayerTuples DartsPlayerScoreService::createInitializedTuples()
{
    PlayerTuples initializedTuples;
    for (const auto &tuple : qAsConst(_playerTuples))
    {
        PlayerTuple t;
        t.id = tuple.id;
        t.name = tuple.name;
        t.score = initialScore();
        initializedTuples << t;
    }
    return initializedTuples;
}

int DartsPlayerScoreService::indexOf(const PlayerTuple &tuple)
{
    for (int i = 0; i < count(); ++i) {
        auto t = _playerTuples.at(i);
        if(t == tuple)
            return i;
    }
    return -1;
}

void DartsPlayerScoreService::replaceTupleAt(const int &index, const PlayerTuple &tuple)
{
    _playerTuples.replace(index,tuple);
}

int DartsPlayerScoreService::count() const
{
    return _playerTuples.count();
}
