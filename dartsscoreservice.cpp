<<<<<<< Updated upstream:dartsscorecontroller.cpp
#include "dartsscorecontroller.h"


DartsScoreController *DartsScoreController::createInstance(const int &initialScore,
                                                       const QUuid &winner)
{
    return new DartsScoreController(initialScore,
                                  winner);
}

void DartsScoreController::addPlayerEntity(const QUuid& id, const QString& name)
=======
#include "dartsscoreservice.h"


DartsScoreService *DartsScoreService::createInstance(const int &initialScore,
                                                       const QUuid &winner)
{
    return new DartsScoreService(initialScore,
                                  winner);
}

void DartsScoreService::addPlayerEntity(const QUuid& id, const QString& name)
>>>>>>> Stashed changes:dartsscoreservice.cpp
{
    auto tuple = PlayerTuple(id,name,initialScore());
    _playerTuples.append(tuple);
}


<<<<<<< Updated upstream:dartsscorecontroller.cpp
void DartsScoreController::subtractPlayerScore(const QUuid& id, const int& score)
=======
void DartsScoreService::subtractPlayerScore(const QUuid& id, const int& score)
>>>>>>> Stashed changes:dartsscoreservice.cpp
{
    auto tuple = tupleAtId(id);
    auto indexOfTuple = indexOf(tuple);
    auto tupleScore = tuple.third;
    auto newTupleScore = tupleScore - score;
    tuple.third = newTupleScore;
    replaceTupleAt(indexOfTuple,tuple);
}

<<<<<<< Updated upstream:dartsscorecontroller.cpp
void DartsScoreController::addPlayerScore(const QUuid &id, const int &score)
=======
void DartsScoreService::addPlayerScore(const QUuid &id, const int &score)
>>>>>>> Stashed changes:dartsscoreservice.cpp
{
    auto tuple = tupleAtId(id);
    auto indexOfTuple = indexOf(tuple);
    auto tupleScore = tuple.third;
    auto newTupleScore = tupleScore + score;
    tuple.third = newTupleScore;
    replaceTupleAt(indexOfTuple,tuple);
}

<<<<<<< Updated upstream:dartsscorecontroller.cpp
int DartsScoreController::userScore(const int &index) const
=======
int DartsScoreService::userScore(const int &index) const
>>>>>>> Stashed changes:dartsscoreservice.cpp
{
    auto tuple = tupleAtIndex(index);
    auto score = tuple.third;
    return score;
}

<<<<<<< Updated upstream:dartsscorecontroller.cpp
int DartsScoreController::userScore(const QUuid &id) const
=======
int DartsScoreService::userScore(const QUuid &id) const
>>>>>>> Stashed changes:dartsscoreservice.cpp
{
    auto tuple = tupleAtId(id);
    auto score = tuple.third;
    return score;
}

<<<<<<< Updated upstream:dartsscorecontroller.cpp
void DartsScoreController::setUserScoreAtIndex(const int &index, const int &input)
=======
void DartsScoreService::setUserScoreAtIndex(const int &index, const int &input)
>>>>>>> Stashed changes:dartsscoreservice.cpp
{
    auto tuple = tupleAtIndex(index);
    tuple.third = input;
    replaceTupleAt(index,tuple);

}

<<<<<<< Updated upstream:dartsscorecontroller.cpp
void DartsScoreController::setUserScoresFromList(const QVector<int> &list)
=======
void DartsScoreService::setUserScoresFromList(const QVector<int> &list)
>>>>>>> Stashed changes:dartsscoreservice.cpp
{
    if(list.count() != playersCount())
        throw INCONSISTENCY_EXCEPTION_MESSAGE;
    for (int i = 0; i < playersCount(); ++i) {
        auto tuple = tupleAtIndex(i);
        tuple.third = list.at(i);
        replaceTupleAt(i,tuple);
    }
}

<<<<<<< Updated upstream:dartsscorecontroller.cpp
void DartsScoreController::setUserScoreAtId(const QUuid &id, const int &input)
=======
void DartsScoreService::setUserScoreAtId(const QUuid &id, const int &input)
>>>>>>> Stashed changes:dartsscoreservice.cpp
{
    auto tuple = tupleAtId(id);
    auto index = indexOf(tuple);
    tuple.third = input;
    replaceTupleAt(index,tuple);

}

<<<<<<< Updated upstream:dartsscorecontroller.cpp
QString DartsScoreController::userNameAtIndex(const int &index) const
=======
QString DartsScoreService::userNameAtIndex(const int &index) const
>>>>>>> Stashed changes:dartsscoreservice.cpp
{
    auto tuple = tupleAtIndex(index);
    auto name = tuple.second;
    return name;
}

<<<<<<< Updated upstream:dartsscorecontroller.cpp
QString DartsScoreController::userNameFromId(const QUuid &id) const
=======
QString DartsScoreService::userNameFromId(const QUuid &id) const
>>>>>>> Stashed changes:dartsscoreservice.cpp
{
    auto tuple = tupleAtId(id);
    auto name = tuple.second;
    return name;
}

<<<<<<< Updated upstream:dartsscorecontroller.cpp
QVector<QString> DartsScoreController::userNames() const
=======
QVector<QString> DartsScoreService::userNames() const
>>>>>>> Stashed changes:dartsscoreservice.cpp
{
    QVector<QString> resultingList;
    for (int i = 0; i < playersCount(); ++i) {
        auto tuple = _playerTuples.at(i);
        auto userName = tuple.second;
        resultingList << userName;
    }
    return resultingList;
}

<<<<<<< Updated upstream:dartsscorecontroller.cpp
QUuid DartsScoreController::userIdAtIndex(const int &index) const
=======
QUuid DartsScoreService::userIdAtIndex(const int &index) const
>>>>>>> Stashed changes:dartsscoreservice.cpp
{
    auto tuple = tupleAtIndex(index);
    auto id = tuple.first;
    return id;
}

<<<<<<< Updated upstream:dartsscorecontroller.cpp
int DartsScoreController::playersCount() const
=======
int DartsScoreService::playersCount() const
>>>>>>> Stashed changes:dartsscoreservice.cpp
{
    return count();
}

<<<<<<< Updated upstream:dartsscorecontroller.cpp
QUuid DartsScoreController::winnerId() const
=======
QUuid DartsScoreService::winnerId() const
>>>>>>> Stashed changes:dartsscoreservice.cpp
{
    return _winner;
}

<<<<<<< Updated upstream:dartsscorecontroller.cpp
ScoreControllerInterface *DartsScoreController::setWinner(const QUuid &id)
=======
ScoreControllerInterface *DartsScoreService::setWinner(const QUuid &id)
>>>>>>> Stashed changes:dartsscoreservice.cpp
{
    _winner = id;
    return this;
}

<<<<<<< Updated upstream:dartsscorecontroller.cpp
QString DartsScoreController::winnerUserName() const
=======
QString DartsScoreService::winnerUserName() const
>>>>>>> Stashed changes:dartsscoreservice.cpp
{
    auto id = winnerId();
    auto userName = userNameFromId(id);
    return userName;
}

<<<<<<< Updated upstream:dartsscorecontroller.cpp
int DartsScoreController::initialScore() const
=======
int DartsScoreService::initialScore() const
>>>>>>> Stashed changes:dartsscoreservice.cpp
{
    return _initialScore;
}

<<<<<<< Updated upstream:dartsscorecontroller.cpp
int DartsScoreController::calculateAccumulatedScoreCandidate(const int &index, const int &score) const
=======
int DartsScoreService::calculateAccumulatedScoreCandidate(const int &index, const int &score) const
>>>>>>> Stashed changes:dartsscoreservice.cpp
{
    auto tuple = tupleAtIndex(index);
    auto s = tuple.third;
    auto scoreCandidate = s - score;
    return scoreCandidate;
}

<<<<<<< Updated upstream:dartsscorecontroller.cpp
void DartsScoreController::resetScores()
=======
void DartsScoreService::resetScores()
>>>>>>> Stashed changes:dartsscoreservice.cpp
{
    for (int i = 0; i < playersCount(); ++i) {
        auto tuple = tupleAtIndex(i);
        tuple.third = initialScore();
        _playerTuples.replace(i,tuple);
    }
}

<<<<<<< Updated upstream:dartsscorecontroller.cpp
DartsScoreController::DartsScoreController(const int &initialScore,
=======
DartsScoreService::DartsScoreService(const int &initialScore,
>>>>>>> Stashed changes:dartsscoreservice.cpp
                                       const QUuid &winner)
{
    _initialScore = initialScore;
    _winner = winner;
}

<<<<<<< Updated upstream:dartsscorecontroller.cpp
DartsScoreController::DartsScoreController::PlayerTuples DartsScoreController::assembleScoreTubble(const QVector<QUuid> &userIds, const QVector<QString> &userNames, const QVector<int> &userScores)
=======
DartsScoreService::DartsScoreService::PlayerTuples DartsScoreService::assembleScoreTubble(const QVector<QUuid> &userIds, const QVector<QString> &userNames, const QVector<int> &userScores)
>>>>>>> Stashed changes:dartsscoreservice.cpp
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

<<<<<<< Updated upstream:dartsscorecontroller.cpp
DartsScoreController::PlayerTuple DartsScoreController::tupleAtIndex(const int &index) const
=======
DartsScoreService::PlayerTuple DartsScoreService::tupleAtIndex(const int &index) const
>>>>>>> Stashed changes:dartsscoreservice.cpp
{
    auto tuple = _playerTuples.at(index);
    return tuple;
}

<<<<<<< Updated upstream:dartsscorecontroller.cpp
DartsScoreController::PlayerTuple DartsScoreController::tupleAtId(const QUuid &id) const{
=======
DartsScoreService::PlayerTuple DartsScoreService::tupleAtId(const QUuid &id) const{
>>>>>>> Stashed changes:dartsscoreservice.cpp
    for (int i = 0; i < count(); ++i) {
        auto tuple = _playerTuples.at(i);
        auto _id = tuple.first;
        if(id == _id)
            return tuple;
    }
    return PlayerTuple();
}

<<<<<<< Updated upstream:dartsscorecontroller.cpp
DartsScoreController::PlayerTuple DartsScoreController::tupleAtId(const DartsScoreController::PlayerTuples *_tuples, const QUuid &id)
=======
DartsScoreService::PlayerTuple DartsScoreService::tupleAtId(const DartsScoreService::PlayerTuples *_tuples, const QUuid &id)
>>>>>>> Stashed changes:dartsscoreservice.cpp
{
    for (const auto &tuple : *_tuples)
    {
        auto playerId = tuple.first;
        if(playerId == id)
            return tuple;
    }
    return PlayerTuple();
}

<<<<<<< Updated upstream:dartsscorecontroller.cpp
DartsScoreController::PlayerTuples DartsScoreController::createInitializedTuples()
=======
DartsScoreService::PlayerTuples DartsScoreService::createInitializedTuples()
>>>>>>> Stashed changes:dartsscoreservice.cpp
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

<<<<<<< Updated upstream:dartsscorecontroller.cpp
int DartsScoreController::indexOf(const PlayerTuple &tuple)
=======
int DartsScoreService::indexOf(const PlayerTuple &tuple)
>>>>>>> Stashed changes:dartsscoreservice.cpp
{
    for (int i = 0; i < count(); ++i) {
        auto t = _playerTuples.at(i);
        if(t == tuple)
            return i;
    }
    return -1;
}

<<<<<<< Updated upstream:dartsscorecontroller.cpp
void DartsScoreController::replaceTupleAt(const int &index, const PlayerTuple &tuple)
=======
void DartsScoreService::replaceTupleAt(const int &index, const PlayerTuple &tuple)
>>>>>>> Stashed changes:dartsscoreservice.cpp
{
    _playerTuples.replace(index,tuple);
}

<<<<<<< Updated upstream:dartsscorecontroller.cpp
int DartsScoreController::count() const
=======
int DartsScoreService::count() const
>>>>>>> Stashed changes:dartsscoreservice.cpp
{
    return _playerTuples.count();
}
