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

typedef UserScoresControllerInterface<QUuid,QString,QVector<int>,QVector<QString>> ScoreControllerInterface;

class FTPScoreController : public ScoreControllerInterface
{
public:
    static FTPScoreController* createInstance(const QVector<QUuid>& userIds,
                                              const QVector<QString>& userNames,
                                              const QVector<int>& userScores,
                                              const QUuid &winner);
    // UserScoresControllerInterface interface
    virtual int scoreAtIndex(const int &index) const override;
    virtual void setScoreAtIndex(const int &index, const int &input) override;
    virtual void setScoreFromList(const QVector<int> &list) override;
    virtual void setScoreAtId(const QUuid &id, const int &input) override;
    virtual QString userNameAtIndex(const int &index) const override;
    virtual QString userNameFromId(const QUuid &id) const override;
    virtual QVector<QString> userNames() const override;
    virtual QUuid userIdAtIndex(const int &index) const override;
    virtual int userScoresCount() const override;
    virtual QUuid winnerId() const override;
    virtual ScoreControllerInterface *setWinner(const QUuid &id) override;
    virtual QString winnerUserName() const override;
private:
    /*
     * Private constructor
     */

    FTPScoreController(const QVector<QUuid>& userIds,
                       const QVector<QString>& userNames,
                       const QVector<int>& userScores,
                       const QUuid& winner);

    PlayerTuples assembleScoreTubble(const QVector<QUuid>& userIds,
                             const QVector<QString>& userNames,
                             const QVector<int>& userScores);

    PlayerTuple tupleAtIndex(const int &index) const;
    PlayerTuple tupleAtId(const QUuid& id) const;

    int indexOf(const PlayerTuple& tuple);

    void replaceTupleAt(const int &index,const PlayerTuple &tuple);
    int count() const;
    PlayerTuples _playerTuples;
    QUuid _winner;
};

#endif // FTPSCORECONTROLLER_H
