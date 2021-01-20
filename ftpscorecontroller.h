#ifndef FTPSCORECONTROLLER_H
#define FTPSCORECONTROLLER_H

#include "userscorescontrollerinterface.h"
#include <qlist.h>

#define INCONSISTENCY_EXCEPTION_MESSAGE "User inconsistency!"

template<class T1, class T2, class T3>
struct Tuple
{
    Tuple(T1 firstArg, T2 secondArg, T3 thirdArg)
    {
        first = firstArg;
        second = secondArg;
        third = thirdArg;
    }
    Tuple(){}

    bool operator==(const Tuple& other){
        if(other.first != this->first)
            return false;
        else if(other.second != this->second)
            return false;
        else if(other.third != this->third)
            return false;
        return true;
    }
    T1 first;
    T2 second;
    T3 third;
};

typedef Tuple<QUuid,QString,int> PlayerTuple;
typedef QList<PlayerTuple> PlayerTuples;
typedef QPair<QUuid,QString> PlayerPair;
typedef QList<PlayerPair> PlayerPairs;

class FTPScoreController : public UserScoresControllerInterface<QUuid,QString,QList<int>>
{
public:
    static FTPScoreController* createInstance(const QList<QUuid>& userIds,
                                              const QList<QString>& userNames,
                                              const QList<int>& userScores,
                                              const QUuid &winner)
    {
        return new FTPScoreController(userIds,userNames,userScores,winner);
    }
    // UserScoresControllerInterface interface
    virtual int scoreAtIndex(const int &index) const override
    {
        auto tuple = tupleAtIndex(index);
        auto score = tuple.third;
        return score;
    }
    virtual void setScoreAtIndex(const int &index, const int &input) override
    {
        auto tuple = tupleAtIndex(index);
        tuple.third = input;
        replaceTupleAt(index,tuple);

    }
    virtual void setScoreFromList(const QList<int> &list) override
    {
        if(list.count() != userScoresCount())
            throw INCONSISTENCY_EXCEPTION_MESSAGE;
        for (int i = 0; i < userScoresCount(); ++i) {
            auto tuple = tupleAtIndex(i);
            tuple.third = list.at(i);
            replaceTupleAt(i,tuple);
        }
    }
    virtual void setScoreAtId(const QUuid &id, const int &input) override
    {
        auto tuple = tupleAtId(id);
        auto index = indexOf(tuple);
        tuple.third = input;
        replaceTupleAt(index,tuple);

    }
    virtual QString userNameAtIndex(const int &index) const override
    {
        auto tuple = tupleAtIndex(index);
        auto name = tuple.second;
        return name;
    }
    virtual QString userNameFromId(const QUuid &id) const override
    {
        auto tuple = tupleAtId(id);
        auto name = tuple.second;
        return name;
    }
    virtual QUuid userIdAtIndex(const int &index) const override
    {
        auto tuple = tupleAtIndex(index);
        auto id = tuple.first;
        return id;
    }
    virtual int userScoresCount() const override
    {
        return count();
    }
    virtual QUuid winner() const override
    {
        return _winner;
    }
    virtual UserScoresControllerInterface *setWinner(const QUuid &id) override
    {
        _winner = id;
        return this;
    }
private:
    /*
     * Private constructor
     */

    FTPScoreController(const QList<QUuid>& userIds,
                       const QList<QString>& userNames,
                       const QList<int>& userScores,
                       const QUuid& winner)
    {
        auto assembledTuples = assembleScoreTubble(userIds,userNames,userScores);
        _playerTuples = assembledTuples;
        setWinner(winner);
    }

    PlayerTuples assembleScoreTubble(const QList<QUuid>& userIds,
                             const QList<QString>& userNames,
                             const QList<int>& userScores)
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

    PlayerTuple tupleAtIndex(const int &index) const
    {
        auto tuple = _playerTuples.at(index);
        return tuple;
    }
    PlayerTuple tupleAtId(const QUuid& id) const{
        for (int i = 0; i < count(); ++i) {
            auto tuple = _playerTuples.at(i);
            auto _id = tuple.first;
            if(id == _id)
                return tuple;
        }
        return PlayerTuple();
    }

    int indexOf(const PlayerTuple& tuple)
    {
        for (int i = 0; i < count(); ++i) {
            auto t = _playerTuples.at(i);
            if(t == tuple)
                return i;
        }
        return -1;
    }

    void replaceTupleAt(const int &index,const PlayerTuple &tuple)
    {
        _playerTuples.replace(index,tuple);
    }
    int count() const
    {
        return _playerTuples.count();
    }
    PlayerTuples _playerTuples;
    QUuid _winner;
};

#endif // FTPSCORECONTROLLER_H
