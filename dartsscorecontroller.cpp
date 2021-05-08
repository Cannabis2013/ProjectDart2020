#include "dartsscorecontroller.h"


DartsScoreController *DartsScoreController::createInstance(const int &initialScore,
                                                       const QUuid &winner)
{
    return new DartsScoreController(initialScore,
                                  winner);
}

void DartsScoreController::addPlayerEntity(const QUuid& id, const QString& name)
{
    auto tuple = PlayerTuple(id,name,initialScore());
    _playerTuples.append(tuple);
}


void DartsScoreController::subtractPlayerScore(const QUuid& id, const int& score)
{
    auto tuple = tupleAtId(id);
    auto indexOfTuple = indexOf(tuple);
    auto tupleScore = tuple.third;
    auto newTupleScore = tupleScore - score;
    tuple.third = newTupleScore;
    replaceTupleAt(indexOfTuple,tuple);
}

void DartsScoreController::addPlayerScore(const QUuid &id, const int &score)
{
    auto tuple = tupleAtId(id);
    auto indexOfTuple = indexOf(tuple);
    auto tupleScore = tuple.third;
    auto newTupleScore = tupleScore + score;
    tuple.third = newTupleScore;
    replaceTupleAt(indexOfTuple,tuple);
}

int DartsScoreController::userScore(const int &index) const
{
    auto tuple = tupleAtIndex(index);
    auto score = tuple.third;
    return score;
}

int DartsScoreController::userScore(const QUuid &id) const
{
    auto tuple = tupleAtId(id);
    auto score = tuple.third;
    return score;
}

void DartsScoreController::setUserScoreAtIndex(const int &index, const int &input)
{
    auto tuple = tupleAtIndex(index);
    tuple.third = input;
    replaceTupleAt(index,tuple);

}

void DartsScoreController::setUserScoresFromList(const QVector<int> &list)
{
    if(list.count() != playersCount())
        throw INCONSISTENCY_EXCEPTION_MESSAGE;
    for (int i = 0; i < playersCount(); ++i) {
        auto tuple = tupleAtIndex(i);
        tuple.third = list.at(i);
        replaceTupleAt(i,tuple);
    }
}

void DartsScoreController::setUserScoreAtId(const QUuid &id, const int &input)
{
    auto tuple = tupleAtId(id);
    auto index = indexOf(tuple);
    tuple.third = input;
    replaceTupleAt(index,tuple);

}

QString DartsScoreController::userNameAtIndex(const int &index) const
{
    auto tuple = tupleAtIndex(index);
    auto name = tuple.second;
    return name;
}

QString DartsScoreController::userNameFromId(const QUuid &id) const
{
    auto tuple = tupleAtId(id);
    auto name = tuple.second;
    return name;
}

QVector<QString> DartsScoreController::userNames() const
{
    QVector<QString> resultingList;
    for (int i = 0; i < playersCount(); ++i) {
        auto tuple = _playerTuples.at(i);
        auto userName = tuple.second;
        resultingList << userName;
    }
    return resultingList;
}

QUuid DartsScoreController::userIdAtIndex(const int &index) const
{
    auto tuple = tupleAtIndex(index);
    auto id = tuple.first;
    return id;
}

int DartsScoreController::playersCount() const
{
    return count();
}

QUuid DartsScoreController::winnerId() const
{
    return _winner;
}

IScoreController *DartsScoreController::setWinner(const QUuid &id)
{
    _winner = id;
    return this;
}

QString DartsScoreController::winnerUserName() const
{
    auto id = winnerId();
    auto userName = userNameFromId(id);
    return userName;
}

int DartsScoreController::initialScore() const
{
    return _initialScore;
}

int DartsScoreController::calculateAccumulatedScoreCandidate(const int &index, const int &score) const
{
    auto tuple = tupleAtIndex(index);
    auto s = tuple.third;
    auto scoreCandidate = s - score;
    return scoreCandidate;
}

void DartsScoreController::resetScores()
{
    for (int i = 0; i < playersCount(); ++i) {
        auto tuple = tupleAtIndex(i);
        tuple.third = initialScore();
        _playerTuples.replace(i,tuple);
    }
}

DartsScoreController::DartsScoreController(const int &initialScore,
                                       const QUuid &winner)
{
    _initialScore = initialScore;
    _winner = winner;
}

DartsScoreController::DartsScoreController::PlayerTuples DartsScoreController::assembleScoreTubble(const QVector<QUuid> &userIds, const QVector<QString> &userNames, const QVector<int> &userScores)
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

DartsScoreController::PlayerTuple DartsScoreController::tupleAtIndex(const int &index) const
{
    auto tuple = _playerTuples.at(index);
    return tuple;
}

DartsScoreController::PlayerTuple DartsScoreController::tupleAtId(const QUuid &id) const{
    for (int i = 0; i < count(); ++i) {
        auto tuple = _playerTuples.at(i);
        auto _id = tuple.first;
        if(id == _id)
            return tuple;
    }
    return PlayerTuple();
}

DartsScoreController::PlayerTuple DartsScoreController::tupleAtId(const DartsScoreController::PlayerTuples *_tuples, const QUuid &id)
{
    for (const auto &tuple : *_tuples)
    {
        auto playerId = tuple.first;
        if(playerId == id)
            return tuple;
    }
    return PlayerTuple();
}

DartsScoreController::PlayerTuples DartsScoreController::createInitializedTuples()
{
    PlayerTuples initializedTuples;
    for (const auto &tuple : _playerTuples)
    {
        PlayerTuple t;
        t.first = tuple.first;
        t.second = tuple.second;
        t.third = initialScore();
    }
    return initializedTuples;
}

int DartsScoreController::indexOf(const PlayerTuple &tuple)
{
    for (int i = 0; i < count(); ++i) {
        auto t = _playerTuples.at(i);
        if(t == tuple)
            return i;
    }
    return -1;
}

void DartsScoreController::replaceTupleAt(const int &index, const PlayerTuple &tuple)
{
    _playerTuples.replace(index,tuple);
}

int DartsScoreController::count() const
{
    return _playerTuples.count();
}
