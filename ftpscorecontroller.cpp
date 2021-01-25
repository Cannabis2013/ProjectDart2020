#include "ftpscorecontroller.h"


FTPScoreController *FTPScoreController::createInstance(const QVector<QUuid> &userIds,
                                                       const QVector<QString> &userNames,
                                                       const QVector<int> &userScores,
                                                       const int &initialScore,
                                                       const QUuid &winner)
{
    return new FTPScoreController(userIds,
                                  userNames,
                                  userScores,
                                  initialScore,
                                  winner);
}

int FTPScoreController::userscoreAtIndex(const int &index) const
{
    auto tuple = tupleAtIndex(index);
    auto score = tuple.third;
    return score;
}

void FTPScoreController::setUserScoreAtIndex(const int &index, const int &input)
{
    auto tuple = tupleAtIndex(index);
    tuple.third = input;
    replaceTupleAt(index,tuple);

}

void FTPScoreController::setUserScoresFromList(const QVector<int> &list)
{
    if(list.count() != playersCount())
        throw INCONSISTENCY_EXCEPTION_MESSAGE;
    for (int i = 0; i < playersCount(); ++i) {
        auto tuple = tupleAtIndex(i);
        tuple.third = list.at(i);
        replaceTupleAt(i,tuple);
    }
}

void FTPScoreController::setUserScoreAtId(const QUuid &id, const int &input)
{
    auto tuple = tupleAtId(id);
    auto index = indexOf(tuple);
    tuple.third = input;
    replaceTupleAt(index,tuple);

}

QString FTPScoreController::userNameAtIndex(const int &index) const
{
    auto tuple = tupleAtIndex(index);
    auto name = tuple.second;
    return name;
}

QString FTPScoreController::userNameFromId(const QUuid &id) const
{
    auto tuple = tupleAtId(id);
    auto name = tuple.second;
    return name;
}

QVector<QString> FTPScoreController::userNames() const
{
    QVector<QString> resultingList;
    for (int i = 0; i < playersCount(); ++i) {
        auto tuple = _playerTuples.at(i);
        auto userName = tuple.second;
        resultingList << userName;
    }
    return resultingList;
}

QUuid FTPScoreController::userIdAtIndex(const int &index) const
{
    auto tuple = tupleAtIndex(index);
    auto id = tuple.first;
    return id;
}

int FTPScoreController::playersCount() const
{
    return count();
}

QUuid FTPScoreController::winnerId() const
{
    return _winner;
}

ScoreControllerInterface *FTPScoreController::setWinner(const QUuid &id)
{
    _winner = id;
    return this;
}

QString FTPScoreController::winnerUserName() const
{
    auto id = winnerId();
    auto userName = userNameFromId(id);
    return userName;
}

int FTPScoreController::initialScore() const
{
    return _initialScore;
}

int FTPScoreController::calculateAggregateduserScoreCandidate(const int &index, const int &score) const
{
    auto tuple = tupleAtIndex(index);
    auto s = tuple.third;
    auto scoreCandidate = s - score;
    return scoreCandidate;
}

void FTPScoreController::resetScores()
{
    for (int i = 0; i < playersCount(); ++i) {
        auto tuple = tupleAtIndex(i);
        tuple.third = initialScore();
        _playerTuples.replace(i,tuple);
    }
}

FTPScoreController::FTPScoreController(const QVector<QUuid> &userIds,
                                       const QVector<QString> &userNames,
                                       const QVector<int> &userScores,
                                       const int &initialScore,
                                       const QUuid &winner)
{
    auto assembledTuples = assembleScoreTubble(userIds,userNames,userScores);
    _initialScore = initialScore;
    _playerTuples = assembledTuples;
    _winner = winner;
}

PlayerTuples FTPScoreController::assembleScoreTubble(const QVector<QUuid> &userIds, const QVector<QString> &userNames, const QVector<int> &userScores)
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

PlayerTuple FTPScoreController::tupleAtIndex(const int &index) const
{
    auto tuple = _playerTuples.at(index);
    return tuple;
}

PlayerTuple FTPScoreController::tupleAtId(const QUuid &id) const{
    for (int i = 0; i < count(); ++i) {
        auto tuple = _playerTuples.at(i);
        auto _id = tuple.first;
        if(id == _id)
            return tuple;
    }
    return PlayerTuple();
}

int FTPScoreController::indexOf(const PlayerTuple &tuple)
{
    for (int i = 0; i < count(); ++i) {
        auto t = _playerTuples.at(i);
        if(t == tuple)
            return i;
    }
    return -1;
}

void FTPScoreController::replaceTupleAt(const int &index, const PlayerTuple &tuple)
{
    _playerTuples.replace(index,tuple);
}

int FTPScoreController::count() const
{
    return _playerTuples.count();
}
